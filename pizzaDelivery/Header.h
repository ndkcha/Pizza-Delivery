#include<afxwin.h>
#include "resource.h"

class CMainWin : public CFrameWnd {
public:
	CListBox *pizzaList;


	CMainWin();

	afx_msg void refreshList();
	afx_msg void deleteFromList();

	afx_msg void OnDialog();
	afx_msg void OnExit();

	afx_msg void OnHelpDialog();
	afx_msg void OnAcceleratorqm();

	afx_msg void OnNewDialog();

	DECLARE_MESSAGE_MAP()
};

class CApp : public CWinApp {
public:
	BOOL InitInstance();
};

class CHelpDialog : public CDialog {
public:
	CHelpDialog(LPCTSTR DialogName, CWnd *Owner) :
		CDialog(DialogName, Owner) {}

	DECLARE_MESSAGE_MAP()

	afx_msg void OnCancel();
};

class CNewOrderDialog : public CDialog {
public:
	int pizmarg, topec, topmush, topgc, toprp, topbo, topcc;
	
	CNewOrderDialog(LPCTSTR DialogName, CWnd *Owner) :
		CDialog(DialogName, Owner) {}

	DECLARE_MESSAGE_MAP()

	virtual void DoDataExchange(CDataExchange *pDX);

	afx_msg void OnNewOrderCancel();
	afx_msg void OnOK();
};

class CDeleteDialog : public CDialog {
public:
	CString deleteid;

	CDeleteDialog(LPCTSTR DialogName, CWnd *Owner) :
		CDialog(DialogName, Owner) {}

	DECLARE_MESSAGE_MAP()

	virtual void DoDataExchange(CDataExchange *pDX);

	afx_msg void OnConfirmDelete();
};