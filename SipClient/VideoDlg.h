#pragma once

#include "MediaSession\MediaSession.h"


// CVideoDlg dialog

class CVideoDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CVideoDlg)

public:
	CVideoDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CVideoDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_VIDEODLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
private:
    unsigned char* m_ScrBuf[4] = { 0 };     //video buffer

    CMediaSession* m_pMediaSession;

public:
    static void PlayThreadProc(void* pParam);   //线程函数
    HANDLE m_playThreadHandle;                  //线程句柄
    bool m_bplayThreadRuning;                   //线程运行状态

    bool StartPlay();
    bool StopPlay();
    char* getSdpInfo();
};
