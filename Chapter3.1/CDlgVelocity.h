#pragma once
#include "afxdialogex.h"


// CDlgVelocity dialog

class CDlgVelocity : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgVelocity)

public:
	CDlgVelocity(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CDlgVelocity();
	CGraph m_graph;

	CPline m_xE, m_yE, m_zE;

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_VELOCITY };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
};
