#pragma once
#include "afxdialogex.h"


// CDlgTrajectory dialog

class CDlgTrajectory : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgTrajectory)

public:
	CDlgTrajectory(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CDlgTrajectory();
	CGraph m_graph;

	CPline m_xE, m_yE, m_zE;

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_TRAJECTORY };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
};
