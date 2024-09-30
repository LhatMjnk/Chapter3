#pragma once
#include "afxdialogex.h"


// CDlgAccelerator dialog

class CDlgAccelerator : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgAccelerator)

public:
	CDlgAccelerator(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CDlgAccelerator();
	CGraph m_graph;

	CPline m_xE, m_yE, m_zE;

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_ACCELERATOR };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
};
