
// Chapter3.1View.cpp : implementation of the CChapter31View class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Chapter3.1.h"
#endif

#include "Chapter3.1Doc.h"
#include "Chapter3.1View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChapter31View

IMPLEMENT_DYNCREATE(CChapter31View, CView)

BEGIN_MESSAGE_MAP(CChapter31View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_DEMOROBOT_PREMETER, &CChapter31View::OnDemorobotPremeter)
	ON_COMMAND(ID_DEMOROBOT_VELOCITY, &CChapter31View::OnDemorobotVelocity)
	ON_COMMAND(ID_DEMOROBOT_ACCELERATION, &CChapter31View::OnDemorobotAcceleration)
	ON_COMMAND(ID_DEMOROBOT_TRAJECTORY, &CChapter31View::OnDemorobotTrajectory)
	ON_UPDATE_COMMAND_UI(ID_DEMOROBOT_PREMETER, &CChapter31View::OnUpdateDemorobotPremeter)
END_MESSAGE_MAP()

// CChapter31View construction/destruction

CChapter31View::CChapter31View() noexcept
{
	// TODO: add construction code here

}

CChapter31View::~CChapter31View()
{
}

BOOL CChapter31View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CChapter31View drawing

void CChapter31View::OnDraw(CDC* pDC)
{
	CChapter31Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
	
		return;
	// TODO: add draw code for native data here
}


// CChapter31View printing

BOOL CChapter31View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CChapter31View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CChapter31View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CChapter31View diagnostics

#ifdef _DEBUG
void CChapter31View::AssertValid() const
{
	CView::AssertValid();
}

void CChapter31View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CChapter31Doc* CChapter31View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CChapter31Doc)));
	return (CChapter31Doc*)m_pDocument;
}
#endif //_DEBUG


// CChapter31View message handlers
#include "CDlgTrajectory.h"
#include "CDlgParameter.h"
#include "CDlgVelocity.h"
#include "CDlgAccelerator.h"

//void CChapter31View::OnDemorobotChangedirectory()
//{
	// TODO: Add your command handler code here
//}


void CChapter31View::OnDemorobotPremeter()
{
	// TODO: Add your command handler code here
	CDlgParameter dlg;
	//dlg.m_xE.RemoveAll();
	//dlg.m_yE.RemoveAll();
	//dlg.m_zE.RemoveAll();

	for (int i = 0; i < m_robot.m_xE.GetSize(); i++)
	{
		dlg.m_xE.Add(CPoint2d(i, Rad2Deg(NormalAngleRad(m_robot.m_qtheta1[i]))));
		dlg.m_yE.Add(CPoint2d(i, Rad2Deg(NormalAngleRad(m_robot.m_qtheta2[i]))));
		dlg.m_zE.Add(CPoint2d(i, Rad2Deg(NormalAngleRad(m_robot.m_qtheta3[i]))));

	}

	dlg.DoModal();
}


void CChapter31View::OnDemorobotVelocity()
{
	// TODO: Add your command handler code here
	CDlgVelocity dlg;
	dlg.m_xE.RemoveAll();
	dlg.m_yE.RemoveAll();
	dlg.m_zE.RemoveAll();

	for (int i = 0; i < m_robot.m_xE.GetSize(); i++)
	{
		dlg.m_xE.Add(CPoint2d(i, Rad2Deg(NormalAngleRad(m_robot.m_vtheta1[i]))));
		dlg.m_yE.Add(CPoint2d(i, Rad2Deg(NormalAngleRad(m_robot.m_vtheta2[i]))));
		dlg.m_zE.Add(CPoint2d(i, Rad2Deg(NormalAngleRad(m_robot.m_vtheta3[i]))));

	}

	dlg.DoModal();
}


void CChapter31View::OnDemorobotAcceleration()
{
	// TODO: Add your command handler code here
	CDlgAccelerator dlg;
	dlg.m_xE.RemoveAll();
	dlg.m_yE.RemoveAll();
	dlg.m_zE.RemoveAll();

	for (int i = 0; i < m_robot.m_xE.GetSize(); i++)
	{
		dlg.m_xE.Add(CPoint2d(i, Rad2Deg(NormalAngleRad(m_robot.m_atheta1[i]))));
		dlg.m_yE.Add(CPoint2d(i, Rad2Deg(NormalAngleRad(m_robot.m_atheta2[i]))));
		dlg.m_zE.Add(CPoint2d(i, Rad2Deg(NormalAngleRad(m_robot.m_atheta3[i]))));
	}

	dlg.DoModal();
}


void CChapter31View::OnDemorobotTrajectory()
{
	// TODO: Add your command handler code here
	CDlgTrajectory dlg;
	dlg.m_xE.RemoveAll();
	dlg.m_yE.RemoveAll();
	dlg.m_zE.RemoveAll();
	for (int i = 0; i < m_robot.m_xE.GetSize(); i++)
	{
		dlg.m_xE.Add(CPoint2d(i, m_robot.m_xE[i]));
		dlg.m_yE.Add(CPoint2d(i, m_robot.m_yE[i]));
		dlg.m_zE.Add(CPoint2d(i, m_robot.m_zE[i]));

	}

	dlg.DoModal();
}

void CChapter31View::OnUpdateDemorobotPremeter(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
}
