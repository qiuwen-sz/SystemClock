
// SystemClockDlg.h : header file
//

#pragma once


// CSystemClockDlg dialog
class CSystemClockDlg : public CDialogEx
{
// Construction
public:
	CSystemClockDlg(CWnd* pParent = NULL);	// standard constructor
	~CSystemClockDlg();

// Dialog Data
	enum { IDD = IDD_SYSTEMCLOCK_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

private:
	HANDLE m_hThread;
	static DWORD WINAPI DelegateThreadProc(LPVOID lpParameter)
	{
		((CSystemClockDlg *)lpParameter)->DisplaySystemTime();
		return 0;
	}
	void DisplaySystemTime();
	bool m_bThreadExit;
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
};
