#include "MediaSession.h"

CMediaSession::CMediaSession()
{
}

CMediaSession::~CMediaSession()
{}


char* CMediaSession::getFrame()
{
    return 0;
}

char* CMediaSession::getSdpInfo()
{
    return m_rtpReceiver.getSdpInfo();
}

int CMediaSession::StartProc()
{
    
    return m_rtpReceiver.StartProc();
}

void CMediaSession::StopProc()
{
    return m_rtpReceiver.StopProc();
}

unsigned short CMediaSession::getMediaPort()
{
    return m_rtpReceiver.getMediaPort();
}
