#include "RtpReceiver.h"
#include "DataRepository\include\DataRepository.h"

extern char g_ClientIp[20]; //sip UA IP
extern char g_ClientId[20]; //sip UA Id

//存放PS包的数据仓库，每一数据项存储一帧完整的PS包
extern CDataRepository<unsigned char*> g_PsPacketRepo;

//存放ES包的数据仓库，每一数据项存储一帧完整的ES包
extern CDataRepository<unsigned char*> g_EsPacketRepo;

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

    RTPUDPv4TransmissionParams Transparams;
    RTPSessionParams Sessparams;

    Sessparams.SetOwnTimestampUnit(1.0 / 8000.0);
    Sessparams.SetAcceptOwnPackets(true);

    Transparams.SetPortbase(pThis->m_mediaPort);

    int status, i, num;

    status = (pThis->m_RtpSession).Create(Sessparams, &Transparams);

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
                    //pThis->assemleFrame(pack);
                    pThis->handlePacket(pack);
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

int CRtpReceiver::handlePacket(RTPPacket* packet)
{
    int packetSize = 0;
    uint8_t packetPayloadType;

    if (NULL == packet)
    {
        return 0;
    }

    packetSize = packet->GetPacketLength();
    packetPayloadType = packet->GetPayloadType();

    //按负载类型处理负载数据
    switch (packetPayloadType)
    {
    case PS: //96
    {
        handlePsPacket( packet );
        break;
    }
    case MPEG4: //97
    {
        break;
    }
    case H264: //98
    {
        break;
    }
    case SVAC: //99
    {
        break;
    }
    default:
    {
        break;
    }
    }
}


int CRtpReceiver::handlePsPacket(RTPPacket* packet)
{
    

    if (NULL == packet)
    {
        return 0;
    }

    if (packet->HasMarker())   //完数据包, asMarker() Returns true is the marker bit was set
    {
        //接收到完整的一帧，存入视频帧队列，供解码器解析，并将空间释放，供下一帧数据存放。
        memcpy(m_pFrame + m_offset, packet->GetPayloadData(), packet->GetPayloadLength());
        m_frameSize = m_offset + packet->GetPayloadLength();
        m_pTmpFrame = new uint8_t(m_frameSize);

        g_PsPacketRepo.putData(m_pTmpFrame);    //入PS包仓库
        //memcpy(m_pTmpFrame, m_pFrame, m_frameSize);

        write_media_data_to_file("E://buf_mediaplay.ps", m_pFrame, m_frameSize);
        //write_media_data_to_file("E://src_mediaplay.ps", packet->GetPayloadData(), packet->GetPayloadLength());

        //deal_ps_packet(m_pFrame, m_frameSize);
        m_ps_demuxer.setup_dst_es_video_file("E://buf_mediaplay.h264");
        m_ps_demuxer.deal_ps_packet(m_pFrame, m_frameSize);

        m_frameSize = 0;
        m_offset = 0;
    }
    else
    {
        memcpy(m_pFrame + m_offset, packet->GetPayloadData(), packet->GetPayloadLength());
        m_offset += packet->GetPayloadLength();
        //write_media_data_to_file("E://src_mediaplay.ps", packet->GetPayloadData(), packet->GetPayloadLength());
    }
    return packet->GetPayloadLength();
}

int CRtpReceiver::handleMPEG4Packet(RTPPacket* packet)
{
    return 0;
}

int CRtpReceiver::handleH264Packet(RTPPacket* packet)
{
    return 0;
}

void CRtpReceiver::write_media_data_to_file(char* file_name, void* pLog, int nLen)
{
    if (pLog != NULL && nLen > 0)
    {
        if (NULL == m_pLogFile && strlen(file_name) > 0)
        {
            ::fopen_s(&m_pLogFile, file_name, "ab+");
        }

        if (m_pLogFile != NULL)
        {
            ::fwrite(pLog, nLen, 1, m_pLogFile);
            ::fclose(m_pLogFile);
            m_pLogFile = NULL;
        }
    }
}