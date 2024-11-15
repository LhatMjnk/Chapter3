// HyperLink.h : header file
//
//
// HyperLink static control. Will open the default browser with the given URL
// when the user clicks on the link.
//
// Copyright Chris Maunder, 1997-1999 (cmaunder@mail.com)
// Feel free to use and distribute. May not be sold for profit. 

// 2/29/00 -- P. Shaffer standard font mod.

#if !defined(AFX_HYPERLINK_H__D1625061_574B_11D1_ABBA_00A0243D1382__INCLUDED_)
#define AFX_HYPERLINK_H__D1625061_574B_11D1_ABBA_00A0243D1382__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CHyperLink window
#define TRANS_BACK -1
//#define	STATIC_USE_SOUND

class TOOLINTER_EXT_CLASS CHyperLink : public CStatic
{
// Construction/destruction
public:
    CHyperLink();
    virtual ~CHyperLink();

public:
    enum UnderLineOptions { ulHover = -1, ulNone = 0, ulAlways = 1};

// Attributes
public:
	void DoneWithMouseClickEvent();
	bool PointInMyClient(const CPoint & p);
	bool m_setULR;
	void SetFontBold(const int & w=-1);
	void SetFontHeight(const int & h=-1);
	int m_fontweight;
	int m_fontheight;
	void SetTransparent(const BOOL & trans = true);
	BOOL m_Transparent;
    void SetURL(CString strURL);
    CString GetURL() const;

    void SetColours(COLORREF crLinkColour, COLORREF crVisitedColour, 
                    COLORREF crHoverColour = -1);
    COLORREF GetLinkColour() const;
    COLORREF GetVisitedColour() const;
    COLORREF GetHoverColour() const;

    void SetVisited(BOOL bVisited = TRUE);
    BOOL GetVisited() const;

    void SetLinkCursor(HCURSOR hCursor);
    HCURSOR GetLinkCursor() const;

    void SetUnderline(int nUnderline = ulHover);
    int  GetUnderline() const;

    void SetAutoSize(BOOL bAutoSize = TRUE);
    BOOL GetAutoSize() const;

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CHyperLink)
	public:
    virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL DestroyWindow();
	protected:
    virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
protected:
    HINSTANCE GotoURL(LPCTSTR url, int showcmd);
    void ReportError(int nError);
    LONG GetRegKey(HKEY key, LPCTSTR subkey, LPTSTR retdata);
    void PositionWindow();
    void SetDefaultCursor();

// Protected attributes
protected:
    COLORREF m_crLinkColour, m_crVisitedColour;     // Hyperlink colours
    COLORREF m_crHoverColour;                       // Hover colour
    BOOL     m_bOverControl;                        // cursor over control?
    BOOL     m_bVisited;                            // Has it been visited?
    int      m_nUnderline;                          // underline hyperlink?
    BOOL     m_bAdjustToFit;                        // Adjust window size to fit text?
    CString  m_strURL;                              // hyperlink URL
    CFont    m_UnderlineFont;                       // Font for underline display
    CFont    m_StdFont;                             // Standard font
    HCURSOR  m_hLinkCursor;                         // Cursor for hyperlink
    CToolTipCtrl m_ToolTip;                         // The tooltip
    UINT     m_nTimerID;

public:
#ifdef	STATIC_USE_SOUND
	DWORD SetSound(LPCTSTR lpszSound, HMODULE hMod = NULL, BOOL bPlayOnClick = FALSE, BOOL bPlayAsync = TRUE);
	void SetPlaySound(const bool & pl);
	bool GetPlaySound();
#endif


protected:
#ifdef	STATIC_USE_SOUND
#pragma pack(1)
	typedef struct _STRUCT_SOUND
	{
		TCHAR		szSound[_MAX_PATH];
		LPCTSTR		lpszSound;
		HMODULE		hMod;
		DWORD		dwFlags;
	} STRUCT_SOUND;
#pragma pack()
	STRUCT_SOUND	m_csSounds[2];	// Index 0 = Over	1 = Clicked
	BOOL	m_bMouseOnButton;	// Is mouse over the button?
	static bool m_button_play_sound;
#endif STATIC_USE_SOUND
	void CancelSound();

//Add for tranparent
    
// Operations
    // Generated message map functions
protected:
    //{{AFX_MSG(CHyperLink)
    afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
    afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
#ifndef _WIN64
	afx_msg void OnTimer(UINT nIDEvent);
#else
    afx_msg void OnTimer(UINT_PTR nIDEvent);
#endif _WIN64
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void OnCancelMode();
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnEnable(BOOL bEnable);
	//}}AFX_MSG
	afx_msg LRESULT OnMouseLeave(WPARAM, LPARAM);
    afx_msg void OnClicked();
    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HYPERLINK_H__D1625061_574B_11D1_ABBA_00A0243D1382__INCLUDED_)
