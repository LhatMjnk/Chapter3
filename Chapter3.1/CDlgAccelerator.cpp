// CDlgAccelerator.cpp : implementation file
//

#include "pch.h"
#include "Chapter3.1.h"
#include "afxdialogex.h"
#include "CDlgAccelerator.h"


// CDlgAccelerator dialog

IMPLEMENT_DYNAMIC(CDlgAccelerator, CDialogEx)

CDlgAccelerator::CDlgAccelerator(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_ACCELERATOR, pParent)
{

}

CDlgAccelerator::~CDlgAccelerator()
{
}

void CDlgAccelerator::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgAccelerator, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CDlgAccelerator message handlers


void CDlgAccelerator::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CDialogEx::OnPaint() for painting messages
	CRect r;
	GetClientRect(&r);
	m_graph.SetDC(&dc);
	m_graph.SetRectControl(r);

	double min_x, min_y, max_y, max_x;
	for (int i = 0; i < m_xE.GetSize(); i++)
	{
		if (i == 0)
		{
			min_x = max_x = m_xE[0].x;
			min_y = max_y = m_xE[0].y;
		}
		min_x = min_x > m_xE[i].x ? m_xE[i].x : min_x;
		max_x = max_x < m_xE[i].x ? m_xE[i].x : max_x;

		min_y = min_y > m_xE[i].y ? m_xE[i].y : min_y;
		max_y = max_y < m_xE[i].y ? m_xE[i].y : max_y;
		min_y = min_y > m_yE[i].y ? m_yE[i].y : min_y;
		max_y = max_y < m_yE[i].y ? m_yE[i].y : max_y;
		min_y = min_y > m_zE[i].y ? m_zE[i].y : min_y;
		max_y = max_y < m_zE[i].y ? m_zE[i].y : max_y;
	}
	m_graph.SetRangeX(min_x, max_x);
	m_graph.SetRangeY(min_y, max_y);


	m_graph.DrawBackGround(RGB(255, 255, 255));
	m_graph.DrawTable();

	m_graph.SetColorGraph(RGB(255, 0, 0)); m_graph.DrawPline(m_xE);
	m_graph.SetColorGraph(RGB(0, 255, 0)); m_graph.DrawPline(m_yE);
	m_graph.SetColorGraph(RGB(0, 0, 255)); m_graph.DrawPline(m_zE);
}