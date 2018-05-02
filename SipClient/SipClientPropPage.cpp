// SipClientPropPage.cpp : Implementation of the CSipClientPropPage property page class.

#include "stdafx.h"
#include "SipClient.h"
#include "SipClientPropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CSipClientPropPage, COlePropertyPage)

// Message map

BEGIN_MESSAGE_MAP(CSipClientPropPage, COlePropertyPage)
END_MESSAGE_MAP()

// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CSipClientPropPage, "SIPCLIENT.SipClientPropPage.1",
	0xe592f1be, 0xff3b, 0x4299, 0x98, 0xed, 0xde, 0xb6, 0xa1, 0x1, 0xde, 0x2)

// CSipClientPropPage::CSipClientPropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CSipClientPropPage

BOOL CSipClientPropPage::CSipClientPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_SIPCLIENT_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}

// CSipClientPropPage::CSipClientPropPage - Constructor

CSipClientPropPage::CSipClientPropPage() :
	COlePropertyPage(IDD, IDS_SIPCLIENT_PPG_CAPTION)
{
}

// CSipClientPropPage::DoDataExchange - Moves data between page and properties

void CSipClientPropPage::DoDataExchange(CDataExchange* pDX)
{
	DDP_PostProcessing(pDX);
}

// CSipClientPropPage message handlers
