
// SystemClockDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SystemClock.h"
#include "SystemClockDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSystemClockDlg dialog



CSystemClockDlg::CSystemClockDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSystemClockDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_bThreadExit = false;
}

CSystemClockDlg::~CSystemClockDlg()
{
	m_bThreadExit = true;
	WaitForSingleObject(m_hThread, INFINITE);
}

void CSystemClockDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CSystemClockDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CSystemClockDlg message handlers

BOOL CSystemClockDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	m_hThread = CreateThread(NULL, 0, DelegateThreadProc, this, 0, NULL);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSystemClockDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
	CClientDC dc(this);
	CFont MyFont;
	int nFontHeight = 160, nFontWidth = 35;
	MyFont.CreateFont(
		nFontHeight,               // nHeight
		nFontWidth,                // nWidth
		0,                         // nEscapement
		0,                         // nOrientation
		FW_HEAVY,                 // nWeight
		FALSE,                     // bItalic
		FALSE,                     // bUnderline
		0,                         // cStrikeOut
		ANSI_CHARSET,              // nCharSet
		OUT_DEFAULT_PRECIS,        // nOutPrecision
		CLIP_DEFAULT_PRECIS,       // nClipPrecision
		DEFAULT_QUALITY,           // nQuality
		DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
		_T("Î¢ÈíÑÅºÚ"));
	dc.SelectObject(&MyFont);
	CRect ClientRect;
	GetClientRect(&ClientRect);
	SetTextAlign(dc.m_hDC, GetTextAlign(dc.m_hDC) | VTA_CENTER);
	SYSTEMTIME sys;
	GetLocalTime(&sys);
	CString systime_str;
	systime_str.Format(L"%02d:%02d:%02d.%03d",
						sys.wHour, sys.wMinute, sys.wSecond, sys.wMilliseconds);
	dc.TextOut(ClientRect.left + (ClientRect.right - ClientRect.left) / 2, 
				ClientRect.top + (ClientRect.bottom - ClientRect.top) / 2-nFontHeight/2, systime_str);
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSystemClockDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CSystemClockDlg::DisplaySystemTime()
{
	while (!m_bThreadExit)
	{
		Invalidate();
		UpdateWindow();
		Sleep(100);
	}
}

BOOL CSystemClockDlg::OnEraseBkgnd(CDC* pDC)
{
	// Disable erase background for avoid flicker
	return TRUE;
	//return CDialogEx::OnEraseBkgnd(pDC);
}

LRESULT CSystemClockDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	return CDialogEx::WindowProc(message, wParam, lParam);
}
