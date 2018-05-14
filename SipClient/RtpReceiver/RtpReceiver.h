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

typedef struct
{
    //LITTLE_ENDIAN
    unsigned short   v : 2;     // packet type
    unsigned short   p : 1;     // padding flag
    unsigned short   x : 1;     // header extension flag
    unsigned short   cc : 4;    // CSRC count
    unsigned short   m : 1;     // marker bit 
    unsigned short   pt : 7;    // payload type
    unsigned short   seq;       // sequence number
    unsigned long    ts;        // timestamp
    unsigned long    ssrc;      //synchronization source
}rtp_hdr_t;

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
    *       将接收到的包拼装成完整的一帧数据
    *   function：
    *       assemle packet data to an full Frame
    */
    int assemleFrame(RTPPacket* packet);

    static void ThreadProc(void* pParam);   //线程函数
    int StartProc();
    void StopProc();
    HANDLE m_threadHandle;  //线程句柄
    bool m_bThreadRuning;   //线程运行状态

    void writeLog(const char* pLog, int nLen);

private:
    RTPUDPv4TransmissionParams m_Transparams;
    RTPSessionParams m_Sessparams;
    RTPSession m_RtpSession;
    char m_SdpInfo[4 * 1024] = { 0 };
    uint16_t m_mediaPort;
    uint8_t m_pFrame[100 * 1024];   //保存获取到的完整视频帧，如果对于特高质量视频帧，可以将该空间扩大
    int m_offset;                   //位移
    bool m_isMarkerPacket;              //完整帧rtp包头标记

    FILE* m_pLogFile;
};

#endif
