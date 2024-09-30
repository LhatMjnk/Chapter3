#pragma once
#include "afxdialogex.h"


// CDlgParameter dialog

class CDlgParameter : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgParameter)

public:
	CDlgParameter(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CDlgParameter();
	CGraph m_graph;

	CPline m_xE, m_yE, m_zE;

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_PARAMETER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
};
