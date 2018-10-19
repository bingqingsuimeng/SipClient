#ifndef __RTPRECEIVER_H__
#define __RTPRECEIVER_H__

//jrtplib headers 
#include "rtpsession.h"
#include "rtppacket.h"
#include "rtpudpv4transmitter.h"
#include "rtpipv4address.h"
#include "rtpsessionparams.h"
#include "rtperrors.h"
#include "rtpsourcedata.h"

using namespace jrtplib;

//MAX_FRAME_SIZE, 100M，保存获取到的完整视频帧，如果对于特高质量视频帧，可以将该空间扩大
#define MAX_FRAME_SIZE 100 * 1024 * 1024 
#define SDP_SIZE 4 * 1024

typedef struct
{
    //因为字节序不同，所以定义字段的顺序不是按照rfc3550中定义的顺序，这样定义方便存取；
    //because of bit sequence, we define this struct not as order define in rfc3550.
    //LITTLE_ENDIAN
    unsigned short   cc : 4;    // CSRC count
    unsigned short   x  : 1;     // header extension flag
    unsigned short   p  : 1;     // padding flag
    unsigned short   v  : 2;     // packet type
    unsigned short   pt : 7;    // payload type
    unsigned short   m  : 1;     // marker bit
    unsigned short   seq;       // sequence number
    unsigned long    ts;        // timestamp
    unsigned long    ssrc;      // synchronization source
}rtp_hdr_t;

/**
*   依据 GB28181 附录C
*/
enum PAYLOADTYPE
{
    PS      = 96,
    MPEG4   = 97,
    H264    = 98,
    SVAC    = 99
};

class CRtpReceiver
{
public:
    CRtpReceiver(unsigned short rtpPort = 9000);
    ~CRtpReceiver();

    char* getFrame();
    char* getSdpInfo();
    int generateSdpInfo();
    uint16_t getMediaPort();

    /**
    *   功能：
    *       根据 RTP 负载类型选择正确的负载处理函数
    *   function：
    *       choice, depend on RTP payload, right payload process function. 
    */
    int handlePacket(RTPPacket* packet);

    /**
    *   功能：
    *       将接收到的包拼装成完整的一帧数据
    *   function：
    *       assemle packet data to an full Frame
    */
    int handlePsPacket(RTPPacket* packet);
    int handleMPEG4Packet(RTPPacket* packet);
    int handleH264Packet(RTPPacket* packet);
    int deal_ps_packet(unsigned char * packet, int length);
    int find_next_hx_str(unsigned char* source, int source_length, unsigned char* seed, int seed_length, int* offset);

    static void ThreadProc(void* pParam);   //线程函数
    int StartProc();
    void StopProc();
    HANDLE m_threadHandle;  //线程句柄
    bool m_bThreadRuning;   //线程运行状态

    void writeLog(char* file_name, void* pLog, int nLen);

private:
    RTPUDPv4TransmissionParams m_Transparams;
    RTPSessionParams m_Sessparams;
    RTPSession m_RtpSession;
    char m_SdpInfo[SDP_SIZE] = { 0 };
    uint16_t m_mediaPort;
    uint8_t m_pFrame[MAX_FRAME_SIZE];       //存放PS媒体帧缓存
    uint8_t m_pEsFrame[MAX_FRAME_SIZE];       //存放ES媒体帧缓存
    uint8_t* m_pTmpFrame;                   //组装完整的帧堆地址，用于插入仓库。
    int m_offset;                           //位移
    int m_frameSize;                        //完整帧大小
    bool m_isMarkerPacket;                  //完整帧rtp包头标记

    FILE* m_pLogFile;
};

#endif
