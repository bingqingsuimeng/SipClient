#pragma once


// CVideoDlg dialog

class CVideoDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CVideoDlg)

public:
	CVideoDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CVideoDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_VIDEODLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
