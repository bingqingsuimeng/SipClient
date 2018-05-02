// SipClient.cpp : Implementation of CSipClientApp and DLL registration.

#include "stdafx.h"
#include "SipClient.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CSipClientApp theApp;

const GUID CDECL _tlid = { 0x3A0B614D, 0xD070, 0x4C67, { 0x8E, 0x7B, 0xDD, 0x20, 0x5, 0xE0, 0xA, 0xEC } };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;



// CSipClientApp::InitInstance - DLL initialization

BOOL CSipClientApp::InitInstance()
{
	BOOL bInit = COleControlModule::InitInstance();

	if (bInit)
	{
		// TODO: Add your own module initialization code here.
	}

	return bInit;
}



// CSipClientApp::ExitInstance - DLL termination

int CSipClientApp::ExitInstance()
{
	// TODO: Add your own module termination code here.

	return COleControlModule::ExitInstance();
}



// DllRegisterServer - Adds entries to the system registry

STDAPI DllRegisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(TRUE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}



// DllUnregisterServer - Removes entries from the system registry

STDAPI DllUnregisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(FALSE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}
