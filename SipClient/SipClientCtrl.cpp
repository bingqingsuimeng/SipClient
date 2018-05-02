// SipClientCtrl.cpp : Implementation of the CSipClientCtrl ActiveX Control class.

#include "stdafx.h"
#include "SipClient.h"
#include "SipClientCtrl.h"
#include "SipClientPropPage.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CSipClientCtrl, COleControl)

// Message map

BEGIN_MESSAGE_MAP(CSipClientCtrl, COleControl)
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()

// Dispatch map

BEGIN_DISPATCH_MAP(CSipClientCtrl, COleControl)
	DISP_FUNCTION_ID(CSipClientCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
END_DISPATCH_MAP()

// Event map

BEGIN_EVENT_MAP(CSipClientCtrl, COleControl)
END_EVENT_MAP()

// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CSipClientCtrl, 1)
	PROPPAGEID(CSipClientPropPage::guid)
END_PROPPAGEIDS(CSipClientCtrl)

// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CSipClientCtrl, "SIPCLIENT.SipClientCtrl.1",
	0xeb9abed1, 0x92e5, 0x4026, 0xa6, 0x68, 0x76, 0x26, 0x7c, 0x52, 0x69, 0xca)

// Type library ID and version

IMPLEMENT_OLETYPELIB(CSipClientCtrl, _tlid, _wVerMajor, _wVerMinor)

// Interface IDs

const IID IID_DSipClient = { 0x52EE339D, 0xE0E1, 0x4DE0, { 0x84, 0x37, 0xE4, 0x76, 0x2B, 0x44, 0x46, 0x53 } };
const IID IID_DSipClientEvents = { 0x48685B74, 0x931D, 0x4E0A, { 0x84, 0x8A, 0x7D, 0xCA, 0xEE, 0x46, 0x35, 0x93 } };

// Control type information

static const DWORD _dwSipClientOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CSipClientCtrl, IDS_SIPCLIENT, _dwSipClientOleMisc)

// CSipClientCtrl::CSipClientCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CSipClientCtrl

BOOL CSipClientCtrl::CSipClientCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO: Verify that your control follows apartment-model threading rules.
	// Refer to MFC TechNote 64 for more information.
	// If your control does not conform to the apartment-model rules, then
	// you must modify the code below, changing the 6th parameter from
	// afxRegApartmentThreading to 0.

	if (bRegister)
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_SIPCLIENT,
			IDB_SIPCLIENT,
			afxRegApartmentThreading,
			_dwSipClientOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}


// CSipClientCtrl::CSipClientCtrl - Constructor

CSipClientCtrl::CSipClientCtrl()
{
	InitializeIIDs(&IID_DSipClient, &IID_DSipClientEvents);
	// TODO: Initialize your control's instance data here.
}

// CSipClientCtrl::~CSipClientCtrl - Destructor

CSipClientCtrl::~CSipClientCtrl()
{
	// TODO: Cleanup your control's instance data here.
}

// CSipClientCtrl::OnDraw - Drawing function

void CSipClientCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& /* rcInvalid */)
{
	if (!pdc)
		return;

	// TODO: Replace the following code with your own drawing code.
    m_hCtlWnd = this->GetSafeHwnd();

    if (m_pVideoDlg == NULL)
    {
        m_pVideoDlg = new CVideoDlg(this);
        m_pVideoDlg->Create(IDD_VIDEODLG, this);

        //初始化后黑屏显示
        //COLORREF color;
        m_pVideoDlg->SetBackgroundColor(0);
    }
    ShowWindow(SW_SHOW);
    m_pVideoDlg->ShowWindow(SW_SHOW);
}

// CSipClientCtrl::DoPropExchange - Persistence support

void CSipClientCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: Call PX_ functions for each persistent custom property.
}


// CSipClientCtrl::OnResetState - Reset control to default state

void CSipClientCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange

	// TODO: Reset any other control state here.
}


// CSipClientCtrl::AboutBox - Display an "About" box to the user

void CSipClientCtrl::AboutBox()
{
	CDialogEx dlgAbout(IDD_ABOUTBOX_SIPCLIENT);
	dlgAbout.DoModal();
}


// CSipClientCtrl message handlers

