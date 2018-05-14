#ifndef __SIPUA_H__
#define __SIPUA_H__

/**
*   描述：
*       实现rfc3261中规定的sipUA   
*
*   description:
*       implement sipUA, which is descripted in rfc3261.
*   author: YangDong
*   date:   2018-05-02
*   email:  heibao111728@126.com
*/

#include <Windows.h>
#include <process.h>
#include <assert.h>
#include "SipStack\include\eXosip2\eXosip.h"

typedef struct _SipSvrInfo
{
    char svrid[30] = { 0 };//sipSvrID
    char svrip[20] = { 0 };//sipSvrIP
    char authPwd[50] = { 0 };//客户端认证密码
    int svrPort; //sipSvr 侦听端口
} ST_SipSvrInfo;

class CSipUA
{
public:
    CSipUA();
    ~CSipUA();

    /**
    *   功能：
    *       初始化osip协议栈、初始化服务器与客户端基本信息
    *       返回值：0，成功；-1，失败
    *   function:
    *       initiation osip stack and init sipsvr and sipua info 
    *       return:0, success; -1, failure
    */
    int Init(char* SipUaId, char* SipUaIp, int SipUaPort,
        char* SipSvrId, char* SipSvrIp, char* authPwd, int sipSvrPort);
    void Clean(void);


    //Main Worker Thread function, handles sip message
    static void ThreadProc(void* pParam);   //线程函数
    int StartProc();
    void StopProc();
    HANDLE m_threadHandle;  //线程句柄
    bool m_bThreadRuning;   //线程运行状态

    //eXosip2 events' handle
    inline int ProceXsipEvt(eXosip_event_t* pSipEvt);

    //rfc3261 define six function : INVITE  ACK  CANCEL  BYE  INFO  OPTIONS
    /**
    *   功能：
    *        注册到sip服务器
    *   参数:
    *       nExpire：0，注销；大于0，超时时间
    *   返回值:
    *       0，成功；非0，失败。
    *   function:
    *       register sipUA to sipSvr
    *   parameter:
    *       nExpire:0,unregister; lower than 0, means overtime
    *   return:
    *       0, success, otherwise failure
    */
    int doRegister(int nExpire);

    int doInvite(char* dstDeviceid, char* sdp);
    int doAck();
    int doCancel();

    /**
    *   功能：
    *       结束呼叫
    *   function:
    *       terminate a call
    */
    int doBye();
    int doInfo();
    int doOptions();

    //INVITE  ACK  CANCEL  BYE  INFO  OPTIONS
    int onInvite();
    int onMessage();

    int paraseMsg(char msg, eXosip_event_t* oSipEvent);

private:
    eXosip_t* m_poSipContent;
    int m_lsnPort;                  //sip消息侦听端口
    char m_pSipUAID[30];    //sipUa_id
    int m_callid;                   //callid
    int m_dialogid;         //dialogid
    char m_pSipUAIP[20];   //sipua_ip
    int m_ExpiresTime;              //注册超时时间

    bool m_bInit;
};

#endif // !__SIPUA_H__

