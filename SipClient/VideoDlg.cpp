// VideoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SipClient.h"
#include "VideoDlg.h"
#include "afxdialogex.h"


// CVideoDlg dialog

IMPLEMENT_DYNAMIC(CVideoDlg, CDialogEx)

CVideoDlg::CVideoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_VIDEODLG, pParent)
{
    m_pMediaSession = NULL;
}

CVideoDlg::~CVideoDlg()
{
}

void CVideoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CVideoDlg, CDialogEx)
END_MESSAGE_MAP()


// CVideoDlg message handlers

void CVideoDlg::PlayThreadProc(void* pParam)
{
    CVideoDlg* pThis = (CVideoDlg*)pParam;
}

bool CVideoDlg::StartPlay()
{
    m_pMediaSession = new CMediaSession();
    m_pMediaSession->StartProc();

    m_playThreadHandle = (HANDLE)_beginthread(PlayThreadProc, 0, (void*)this);
    if (0 == m_playThreadHandle)
    {
        //Ïß³ÌÆô¶¯Ê§°Ü
        return false;
    }
    m_bplayThreadRuning = true;
    return true;
}


bool CVideoDlg::StopPlay()
{
    return false;
}


char* CVideoDlg::getSdpInfo()
{
    if (NULL != m_pMediaSession)
    {
        return m_pMediaSession->getSdpInfo();
    }
    else
    {
        return nullptr;
    }
}
