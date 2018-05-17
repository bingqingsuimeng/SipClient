#include "RtpReceiver.h"

extern char g_ClientIp[20]; //sip UA IP
extern char g_ClientId[20]; //sip UA Id

CRtpReceiver::CRtpReceiver(unsigned short rtpPort)
    :m_mediaPort(rtpPort)
{
    m_offset = 0;
}

CRtpReceiver::~CRtpReceiver()
{
}

char* CRtpReceiver::getFrame()
{
    return nullptr;
}

char* CRtpReceiver::getSdpInfo()
{
    return m_SdpInfo;
}

int CRtpReceiver::generateSdpInfo()
{
    char pMediaPort[10] = { 0 };
    _itoa_s(m_mediaPort, pMediaPort, 10);

    char pSsrc[50] = { 0 };
    sprintf_s(pSsrc, "%s", "999999");

    sprintf_s(m_SdpInfo, 4 * 1024,
        "v=0\r\n"
        "o=%s 0 0 IN IP4 %s\r\n"
        "s=Play\r\n"
        "c=IN IP4 %s\r\n"
        "t=0 0\r\n"
        "m=video %s RTP/AVP 96 98 97\r\n"
        "a=recvonly\r\n"
        "a=rtpmap:96 PS/90000\r\n"
        "a=rtpmap:98 H264/90000\r\n"
        "a=rtpmap:97 MPEG-4/90000\r\n"
        "y=%s\r\n"
        "f=\r\n",
        g_ClientId,
        g_ClientIp,
        g_ClientIp,
        pMediaPort,
        pSsrc);

    return 0;
}

uint16_t CRtpReceiver::getMediaPort()
{
    return m_mediaPort;
}

int CRtpReceiver::StartProc()
{
    m_threadHandle = (HANDLE)_beginthread(ThreadProc, 0, (void*)this);
    if (0 == m_threadHandle)
    {
        //线程启动失败
        return -1;
    }
    m_bThreadRuning = true;

    //生成sdp信息
    generateSdpInfo();

    return 0;
}

void CRtpReceiver::StopProc()
{
    m_bThreadRuning = false;

    m_RtpSession.BYEDestroy(RTPTime(10, 0), 0, 0);
}

void CRtpReceiver::ThreadProc(void* pParam)
{
    CRtpReceiver* pThis = (CRtpReceiver*)pParam;

    (pThis->m_Sessparams).SetOwnTimestampUnit(1.0 / 8000.0);
    (pThis->m_Sessparams).SetAcceptOwnPackets(true);
    (pThis->m_Transparams).SetPortbase(pThis->m_mediaPort);

    int status, i, num;

    status = (pThis->m_RtpSession).Create((pThis->m_Sessparams), &(pThis->m_Transparams));

    while (pThis->m_bThreadRuning)
    {
        (pThis->m_RtpSession).BeginDataAccess();

        // check incoming packets
        if ((pThis->m_RtpSession).GotoFirstSourceWithData())
        {
            do
            {
                RTPPacket *pack;

                while ((pack = (pThis->m_RtpSession).GetNextPacket()) != NULL)
                {
                    pThis->assemleFrame(pack);
                    // we don't longer need the packet, so
                    // we'll delete it
                    (pThis->m_RtpSession).DeletePacket(pack);
                }
            } while ((pThis->m_RtpSession).GotoNextSourceWithData());
        }
        (pThis->m_RtpSession).EndDataAccess();
        RTPTime::Wait(RTPTime(1, 0));
    }
}

int CRtpReceiver::assemleFrame(RTPPacket* packet)
{
    if (NULL == packet)
    {
        return 0;
    }

    if (packet->HasMarker())   //完数据包, asMarker() Returns true is the marker bit was set
    {
        //memcpy(m_pFrame + m_offset, packet->GetPayloadData(), packet->GetPayloadLength());
        //m_offset = 0;
        writeLog((char*)(packet->GetPayloadData()), packet->GetPayloadLength());

        //接收到完整的一帧，存入视频帧队列，供解码器解析，并将空间释放，供下一帧数据存放。
    }
    else
    {
        //memcpy(m_pFrame + m_offset, packet->GetPayloadData(), packet->GetPayloadLength());
        //m_offset += packet->GetPayloadLength();
        writeLog((char*)(packet->GetPayloadData()), packet->GetPayloadLength());
    }
    return packet->GetPayloadLength();
}

void CRtpReceiver::writeLog(const char* pLog, int nLen)
{
    if (pLog != NULL && nLen > 0)
    {
        if (NULL == m_pLogFile)
        {
            ::fopen_s(&m_pLogFile, "E://mediaplay.ps", "a+");
        }

        if (m_pLogFile != NULL)
        {
            ::fwrite(pLog, nLen, 1, m_pLogFile);
            ::fclose(m_pLogFile);
            m_pLogFile = NULL;
        }
    }
}