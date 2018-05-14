#pragma once

// SipClientCtrl.h : Declaration of the CSipClientCtrl ActiveX Control class.


// CSipClientCtrl : See SipClientCtrl.cpp for implementation.
#include "VideoDlg.h"
#include "SipUA\SipUA.h"

HWND g_hCtlWnd;
char g_ClientIp[20] = { 0 }; //sip UA IP
char g_ClientId[25] = { 0 }; //sip UA Id

class CSipClientCtrl : public COleControl
{
	DECLARE_DYNCREATE(CSipClientCtrl)

// Constructor
public:
	CSipClientCtrl();
private:
    CVideoDlg* m_pVideoDlg; // ”∆µœ‘ æ¥∞ø⁄
    CSipUA* m_pSipUA;

// Overrides
public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();

// Implementation
protected:
	~CSipClientCtrl();

	DECLARE_OLECREATE_EX(CSipClientCtrl)    // Class factory and guid
	DECLARE_OLETYPELIB(CSipClientCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CSipClientCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CSipClientCtrl)		// Type name and misc status

// Message maps
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// Event maps
	DECLARE_EVENT_MAP()

// Dispatch and event IDs
public:
	enum {
        dispiddoBye = 4L,
        dispiddoInvite = 3L,
        dispiddoRegister = 2L,
        dispidMediaInit = 1L,
    };
protected:
    
    LONG MediaInit(LPCTSTR clientId, LPCTSTR clientIp, USHORT clientPort, LPCTSTR svrId, LPCTSTR svrIp, USHORT svrPort, LPCTSTR authPwd);
    LONG doRegister(SHORT expire);
    LONG doInvite(LPCTSTR deviceId);
    LONG doBye();
};

