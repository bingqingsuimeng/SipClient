#include "SipUA.h"

ST_SipSvrInfo g_sipSvrInfo;

CSipUA::CSipUA()
{
    m_poSipContent = NULL;
    m_lsnPort = 6000;
    m_bThreadRuning = false;
    m_callid = -1;
    m_dialogid = -1;
    m_bInit = false;
}

CSipUA::~CSipUA()
{
}


int CSipUA::Init( char* SipUaId, char* SipUaIp, int SipUaPort, 
    char* SipSvrId, char* SipSvrIp, char* authPwd, int sipSvrPort )
{
    assert(SipUaId);
    assert(SipSvrId);
    assert(authPwd);

    if (NULL != SipUaId)
    {
        sprintf_s(m_pSipUAID, "%s", SipUaId);
    }

    if (NULL != SipUaIp)
    {
        sprintf_s(m_pSipUAIP, "%s", SipUaIp);
    }

    m_lsnPort = SipUaPort;

    if (NULL != SipSvrId)
    {
        sprintf_s(g_sipSvrInfo.svrid, "%s", SipSvrId);
    }

    if (NULL != SipSvrIp)
    {
        sprintf_s(g_sipSvrInfo.svrip, "%s", SipSvrIp);
    }

    if (NULL != authPwd)
    {
        sprintf_s(g_sipSvrInfo.authPwd, "%s", authPwd);
    }
    g_sipSvrInfo.svrPort = sipSvrPort;

    eXosip_t* SipContent = eXosip_malloc();

    //初始化eXosip和osip协议栈
    if (0 != eXosip_init(SipContent)) 
    {
        delete SipContent;
        SipContent = NULL;
    }
    else
    {
        //初始化成功
        m_poSipContent = SipContent;
    }
  
    //如果给定的端口不能建立监听则失败，如何确保该端口可用？
    if(OSIP_SUCCESS == 
        eXosip_listen_addr(m_poSipContent,
            IPPROTO_UDP, NULL, m_lsnPort, AF_INET, 0))
    {
        m_bInit = true;
        StartProc();
        return 0;
    }
    else
    {
        return -1;
    }
}

void CSipUA::Clean(void)
{
}

void CSipUA::ThreadProc(void* pParam)
{
    CSipUA* pThis = (CSipUA*)pParam;

    eXosip_event_t* pWaiteEvent = NULL;
    osip_message_t* pReg = NULL;        //注册命令响应消息
    osip_message_t* pAnswer = NULL;     //请求的确认型应答
    osip_message_t* pAck = NULL;

    eXosip_t* peXospContent = pThis->m_poSipContent;

    while ( pThis->m_bThreadRuning )
    {
        int nKeepLiveSpace = 0;

        pWaiteEvent = eXosip_event_wait(peXospContent, 0, 50);  //侦听消息的到来

        eXosip_lock(peXospContent);
        eXosip_default_action(peXospContent, pWaiteEvent);
        eXosip_automatic_refresh(peXospContent);        //刷新 REGISTER 和 SUBSCRIBE
        eXosip_unlock(peXospContent);

        if (NULL == pWaiteEvent)    //没有收到消息
        {
            continue;
        }

        //收到MESSAGE消息,处理消息
        switch (pWaiteEvent->type)
        {
        case EXOSIP_MESSAGE_NEW:
        {
            //if (MSG_IS_MESSAGE(pWaiteEvent->request))
            //{
            //    GB28181_MsgAnswer(peXospContent, pWaiteEvent, pAnswer, 200);
            //    const char* pXmlMsg = GB28181_paraseMsgBody(peXosipCtx, pWaiteEvent);

            //    if ("DeviceControl" == GB28181_GetXmlNodeValue(pXmlMsg, "CmdType"))
            //    {
            //        pThis->m_GB28181_eXosip_callback.gb28181_eXosip_getDeviceControlMsgResult(pXmlMsg);
            //    }
            //    else if ("Catalog" == GB28181_GetXmlNodeValue(pXmlMsg, "CmdType"))
            //    {
            //        pThis->m_GB28181_eXosip_callback.gb28181_eXosip_getDeviceCatalog(pXmlMsg);
            //    }
            //    else if ("DeviceInfo" == GB28181_GetXmlNodeValue(pXmlMsg, "CmdType"))
            //    {
            //        if ("OK" == GB28181_GetXmlNodeValue(pXmlMsg, "Result"))
            //        {
            //            pThis->m_GB28181_eXosip_callback.gb28181_eXosip_getDeviceInfo(pXmlMsg);
            //        }
            //    }
            //    else if ("DeviceStatus" == GB28181_GetXmlNodeValue(pXmlMsg, "CmdType"))
            //    {
            //        if ("OK" == GB28181_GetXmlNodeValue(pXmlMsg, "Result"))
            //        {
            //            pThis->m_GB28181_eXosip_callback.gb_eXosip_getDeviceStatus(pXmlMsg);
            //        }
            //    }
            //    else if ("PersetQuery" == GB28181_GetXmlNodeValue(pXmlMsg, "CmdType"))
            //    {
            //        pThis->m_GB28181_eXosip_callback.gb28181_eXosip_getPtzPresets(pXmlMsg);
            //    }
            //    else if ("RecordInfo" == GB28181_GetXmlNodeValue(pXmlMsg, "CmdType"))
            //    {
            //        printf("@kevin,GB28181: 检索录像文件成功\n\n");
            //        printf("%s\n", pXmlMsg);
            //        char * ptemp_str = new char[strlen(pXmlMsg) + 1];
            //        ptemp_str[strlen(pXmlMsg)] = '\0';
            //        //strcpy(ptemp_str,pXmlMsg);
            //        sprintf(ptemp_str, "%s", pXmlMsg);
            //        //::CopyMemory(ptemp_str, pXmlMsg, strlen(pXmlMsg));
            //        printf("ptemp_str\n%s\n", ptemp_str);
            //        ::PostMessage(ghwnd, WM_SUBTHREAD_RESULT_MESSAGE, 0, (LPARAM)ptemp_str);
            //        //pThis->m_GB28181_eXosip_callback.gb28181_RecordInfo_Query_Result(pXmlMsg);
            //    }
            //}

            //break;
        }
        case EXOSIP_REGISTRATION_FAILURE:
        {
            if ((NULL != pWaiteEvent->response) && (401 == pWaiteEvent->response->status_code))
            {
                pReg = NULL;

                //发送携带认证信息的注册请求
                eXosip_clear_authentication_info(peXospContent);//清除认证信息
                eXosip_add_authentication_info(peXospContent, 
                    pThis->m_pSipUAID,
                    pThis->m_pSipUAID,
                    g_sipSvrInfo.authPwd,
                    "MD5", 
                    NULL);  //添加主叫用户的认证信息
                eXosip_register_build_register(peXospContent, pWaiteEvent->rid, pThis->m_ExpiresTime, &pReg);

                eXosip_lock(peXospContent);
                int nRet = eXosip_register_send_register(peXospContent, pWaiteEvent->rid, pReg);
                eXosip_unlock(peXospContent);
                if (0 != nRet)
                {
                    //成功发送带认证的register消息
                }
            }
            else//真正的注册失败
            {
                //注册失败
            }
            break;
        }
        case EXOSIP_REGISTRATION_SUCCESS:
        {
            int nRegister_id = pWaiteEvent->rid; //保存注册成功的注册ID
            break;
        }
        case EXOSIP_MESSAGE_ANSWERED://收到200ok状态消息
        {
            int a = 5;
            break;
        }

        case EXOSIP_CALL_INVITE://INVITE
        {
            int a = 5;
            break;
        }
        case EXOSIP_CALL_ANSWERED: //announce start of call
        {
            pThis->m_callid = pWaiteEvent->cid;
            pThis->m_dialogid = pWaiteEvent->did;

            break;
        }
        case EXOSIP_CALL_ACK://ACK
        {
            //实时视音频点播
            //历史视音频回放
            //视音频文件下载

            break;
        }
        case EXOSIP_CALL_CLOSED://BEY
        {
            //实时视音频点播
            //历史视音频回放
            //视音频文件下载
            break;
        }
        case EXOSIP_CALL_MESSAGE_NEW://MESSAGE:INFO
        {
            break;
        }
        case EXOSIP_CALL_MESSAGE_ANSWERED:
        {
            //历史视音频回放*/
            //文件结束时发送MESSAGE(File to end)的应答
            break;
        }
        case EXOSIP_NOTIFICATION_ANSWERED:
        {
            break;
        }
        default:
        {
            break;
        }
        }

        eXosip_event_free(pWaiteEvent);
        pWaiteEvent = NULL;
        //Sleep(1 * 1000);
    }

    //return 0;
}

int CSipUA::StartProc()
{
    m_threadHandle = (HANDLE)_beginthread(ThreadProc, 0, (void*)this);
    if (0 == m_threadHandle)
    {
        //线程启动失败
        return -1;
    }
    m_bThreadRuning = true;
    return 0;
}

void CSipUA::StopProc()
{
    m_bThreadRuning = false;
}

//eXosip2 events' handle
int CSipUA::ProceXsipEvt(eXosip_event_t* pSipEvt)
{
    return 0;
}

int CSipUA::doRegister(int nExpire)
{
    int nRet = -1;

    do
    {
        char from[100] = { 0 };     //from : sip:主叫用户名@被叫IP地址, 
        char proxy[100] = { 0 };    //to : sip:被叫IP地址:被叫IP端口,  
        char svrPort[10] = { 0 };   //sip服务器端口

        _itoa_s(g_sipSvrInfo.svrPort, svrPort, 10, 10);

        memset(from, 0, 100);
        memset(proxy, 0, 100);
        sprintf_s(from, _countof(from), "sip:%s@%s", m_pSipUAID, g_sipSvrInfo.svrip);
        sprintf_s(proxy, _countof(proxy), "sip:%s@%s:%s", m_pSipUAID, g_sipSvrInfo.svrip, svrPort);

        osip_message_t* reg = NULL;

        int nRegisterId = eXosip_register_build_initial_register(m_poSipContent, from, proxy, NULL, nExpire, &reg);

        if ( 0 > nRegisterId )
        {
            nRet = -3;
            break;
        }

        eXosip_lock(m_poSipContent);
        int nTmpRet = eXosip_register_send_register(m_poSipContent, nRegisterId, reg);
        eXosip_unlock(m_poSipContent);

        if (0 != nTmpRet)
        {
            nRet = -4;
            break;
        }

        m_ExpiresTime = nExpire;
        nRet = 0;

    } while (0);

    return nRet;
}

int CSipUA::doInvite(char* dstDeviceid, char* sdp)
{
    int nRet = -1;

    osip_message_t* invite = NULL;
    char pFrom[100] = { 0 };
    char pTo[100] = { 0 };
    char pRoute[100] = { 0 };
    char pSubject[100] = { 0 };
    char svrPort[10] = { 0 };

    _itoa_s(g_sipSvrInfo.svrPort, svrPort, 10, 10);

    sprintf_s(pFrom, 100, "sip:%s@%s", m_pSipUAID, g_sipSvrInfo.svrid);
    sprintf_s(pTo, 100, "sip:%s@%s", dstDeviceid, g_sipSvrInfo.svrid);
    sprintf_s(pRoute, 100, "sip:%s@%s:%s;lr", g_sipSvrInfo.svrid, g_sipSvrInfo.svrip, svrPort);
    sprintf_s(pSubject, 100, "%s: 1, %s:", dstDeviceid, m_pSipUAID);

    do
    {
        if (!m_bInit)
        {
            break;
        }

        if (eXosip_call_build_initial_invite(m_poSipContent, &invite, pTo, pFrom, pRoute, pSubject) != OSIP_SUCCESS)
        {
            break;
        }

        osip_message_set_expires(invite, "3600");

        osip_message_set_body(invite, sdp, strlen(sdp));
        osip_message_set_content_type(invite, "application/sdp");

        eXosip_lock(m_poSipContent);
        nRet = eXosip_call_send_initial_invite(m_poSipContent, invite);     //SIP INVITE message to send
        eXosip_unlock(m_poSipContent);

    } while (0);

    return nRet;
}

int CSipUA::onInvite()
{
    return 0;
}

int CSipUA::onMessage()
{
    return 0;
}

int CSipUA::doAck()
{
    return 0;
}

int CSipUA::doCancel()
{
    return 0;
}

int CSipUA::doBye()
{
    int nRet = -1;
    do
    {
        eXosip_lock(m_poSipContent);
        int nTerminateRet = eXosip_call_terminate(m_poSipContent, m_callid, m_dialogid);
        eXosip_unlock(m_poSipContent);

        if (nTerminateRet != OSIP_SUCCESS)
        {
            break;
        }

        nRet = 0;

    } while (0);

    return nRet;
}

int CSipUA::doInfo()
{
    return 0;
}

int CSipUA::doOptions()
{
    return 0;
}

int CSipUA::paraseMsg(char msg, eXosip_event_t* oSipEvent)
{
    int nRet = -1;

    return nRet;
}