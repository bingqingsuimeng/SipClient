

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Mon Oct 29 16:46:26 2018
 */
/* Compiler settings for SipClient.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 8.00.0603 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__


#ifndef __SipClientidl_h__
#define __SipClientidl_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef ___DSipClient_FWD_DEFINED__
#define ___DSipClient_FWD_DEFINED__
typedef interface _DSipClient _DSipClient;

#endif 	/* ___DSipClient_FWD_DEFINED__ */


#ifndef ___DSipClientEvents_FWD_DEFINED__
#define ___DSipClientEvents_FWD_DEFINED__
typedef interface _DSipClientEvents _DSipClientEvents;

#endif 	/* ___DSipClientEvents_FWD_DEFINED__ */


#ifndef __SipClient_FWD_DEFINED__
#define __SipClient_FWD_DEFINED__

#ifdef __cplusplus
typedef class SipClient SipClient;
#else
typedef struct SipClient SipClient;
#endif /* __cplusplus */

#endif 	/* __SipClient_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 


/* interface __MIDL_itf_SipClient_0000_0000 */
/* [local] */ 

#pragma once
#pragma region Desktop Family
#pragma endregion


extern RPC_IF_HANDLE __MIDL_itf_SipClient_0000_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_SipClient_0000_0000_v0_0_s_ifspec;


#ifndef __SipClientLib_LIBRARY_DEFINED__
#define __SipClientLib_LIBRARY_DEFINED__

/* library SipClientLib */
/* [control][version][uuid] */ 


EXTERN_C const IID LIBID_SipClientLib;

#ifndef ___DSipClient_DISPINTERFACE_DEFINED__
#define ___DSipClient_DISPINTERFACE_DEFINED__

/* dispinterface _DSipClient */
/* [uuid] */ 


EXTERN_C const IID DIID__DSipClient;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("52EE339D-E0E1-4DE0-8437-E4762B444653")
    _DSipClient : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DSipClientVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DSipClient * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DSipClient * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DSipClient * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DSipClient * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DSipClient * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DSipClient * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DSipClient * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } _DSipClientVtbl;

    interface _DSipClient
    {
        CONST_VTBL struct _DSipClientVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DSipClient_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _DSipClient_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _DSipClient_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _DSipClient_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _DSipClient_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _DSipClient_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _DSipClient_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DSipClient_DISPINTERFACE_DEFINED__ */


#ifndef ___DSipClientEvents_DISPINTERFACE_DEFINED__
#define ___DSipClientEvents_DISPINTERFACE_DEFINED__

/* dispinterface _DSipClientEvents */
/* [uuid] */ 


EXTERN_C const IID DIID__DSipClientEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("48685B74-931D-4E0A-848A-7DCAEE463593")
    _DSipClientEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DSipClientEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DSipClientEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DSipClientEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DSipClientEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DSipClientEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DSipClientEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DSipClientEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DSipClientEvents * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } _DSipClientEventsVtbl;

    interface _DSipClientEvents
    {
        CONST_VTBL struct _DSipClientEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DSipClientEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _DSipClientEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _DSipClientEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _DSipClientEvents_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _DSipClientEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _DSipClientEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _DSipClientEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DSipClientEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_SipClient;

#ifdef __cplusplus

class DECLSPEC_UUID("EB9ABED1-92E5-4026-A668-76267C5269CA")
SipClient;
#endif
#endif /* __SipClientLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


