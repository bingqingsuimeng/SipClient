#ifndef __MEDIASESSION_H__
#define __MEDIASESSION_H__

#include "SipClient\RtpReceiver\RtpReceiver.h"

class CMediaSession
{
public:
    CMediaSession();
    ~CMediaSession();

    char* getFrame();
    char* getSdpInfo();

    unsigned short getMediaPort();

    int StartProc();
    void StopProc();

private:
    CRtpReceiver m_rtpReceiver;
};

#endif // !__MEDIASESSION_H__

