
// Chapter3.1View.h : interface of the CChapter31View class
//

#pragma once
#include "CRobot3DOF.h"


class CChapter31View : public CView
{
protected: // create from serialization only
	CChapter31View() noexcept;
	DECLARE_DYNCREATE(CChapter31View)

// Attributes
public:
	CChapter31Doc* GetDocument() const;
	CRobot3DOF m_robot;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CChapter31View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnDemorobotChangedirectory();
	afx_msg void OnDemorobotPremeter();
	afx_msg void OnDemorobotVelocity();
	afx_msg void OnDemorobotAcceleration();
	afx_msg void OnDemorobotTrajectory();
	afx_msg void OnUpdateDemorobotPremeter(CCmdUI* pCmdUI);
};

#ifndef _DEBUG  // debug version in Chapter3.1View.cpp
inline CChapter31Doc* CChapter31View::GetDocument() const
   { return reinterpret_cast<CChapter31Doc*>(m_pDocument); }
#endif

