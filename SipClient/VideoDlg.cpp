// VideoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SipClient.h"
#include "VideoDlg.h"
#include "afxdialogex.h"


// CVideoDlg dialog

int get_network_stream(void *opaque, uint8_t *buf, int buf_size)
{
    CStreamManager* p_stream_manager = CStreamManager::get_instance();
    int length = 0;

    if (p_stream_manager)
    {
        length = p_stream_manager->read_data(NULL, buf, buf_size);
        if (length == buf_size)
        {
            return length;
            printf("success");
        }
    }
}

IMPLEMENT_DYNAMIC(CVideoDlg, CDialogEx)

CVideoDlg::CVideoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_VIDEODLG, pParent)
{
    m_pMediaSession = NULL;
    m_stream_buffer = (unsigned char*)malloc(STREAM_BUFFER_SIZE);
    
    CDemuxer::setup_callback_function(get_network_stream);
    m_pDemux = new CDemuxer();
}

CVideoDlg::~CVideoDlg()
{
    if (m_stream_buffer)
    {
        free(m_stream_buffer);
    }

    if (m_pDemux)
    {
        delete m_pDemux;
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
    m_pDemux->set_output_es_video_file("E://dialog_mediaplay.h264");

    while (m_bplayThreadRuning)
    {

        if (m_pDemux)
        {
            m_pDemux->demux_ps_to_es_network();
        }
    }
    return 0;
}
