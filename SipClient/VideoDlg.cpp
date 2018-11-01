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
    m_stream_buffer = (unsigned char*)malloc(STREAM_BUFFER_SIZE);
}

CVideoDlg::~CVideoDlg()
{
    if (m_stream_buffer)
    {
        free(m_stream_buffer);
    }
}

void CVideoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CVideoDlg, CDialogEx)
END_MESSAGE_MAP()


// CVideoDlg message handlers

void write_media_data_to_file(char* file_name, void* pLog, int nLen)
{
    FILE* m_pLogFile = NULL;
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

void CVideoDlg::PlayThreadProc(void* pParam)
{
    if(pParam)
    {
        CVideoDlg* pThis = (CVideoDlg*)pParam;
        pThis->Play();
    }
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
    m_bplayThreadRuning = false;
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

int CVideoDlg::Play()
{
    CStreamManager* p_stream_manager = CStreamManager::get_instance();

    unsigned char* p_stream_buffer = (unsigned char*)malloc(2 * 1024 * 1024);

    while (m_bplayThreadRuning)
    {
        memset(p_stream_buffer, 0x00, 2 * 1024 * 1024);
        int length = p_stream_manager->read_data(NULL, p_stream_buffer, 100 * 1024);
        if (p_stream_manager)
        {
            if (length> 0)
            {
                write_media_data_to_file("E://buf_mediaplay_stream_dialog.ps", p_stream_buffer, length);
            }
        }
        Sleep(500);
        memset(p_stream_buffer, 0x00, 2 * 1024 * 1024);
    }
    if (p_stream_buffer)
    {
        free(p_stream_buffer);
    }
    return 0;
}
