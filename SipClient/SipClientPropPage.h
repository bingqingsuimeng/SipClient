#pragma once

// SipClientPropPage.h : Declaration of the CSipClientPropPage property page class.


// CSipClientPropPage : See SipClientPropPage.cpp for implementation.

class CSipClientPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CSipClientPropPage)
	DECLARE_OLECREATE_EX(CSipClientPropPage)

// Constructor
public:
	CSipClientPropPage();

// Dialog Data
	enum { IDD = IDD_PROPPAGE_SIPCLIENT };

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	DECLARE_MESSAGE_MAP()
};

