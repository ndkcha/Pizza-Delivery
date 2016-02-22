#include<afxwin.h>
#include<string.h>
#include"Header.h"
#include"resource.h"
#include "stdafx.h"
#include "afxdialogex.h"

int pizzaType, p_topec, p_topmush = 0, p_topgc = 0, p_toprp = 0, p_topbo = 0, p_topcc = 0, deleteC = 0;
CString deleteS;

CMainWin :: CMainWin() {
	Create(NULL, _T("Pizza Delivery"), WS_OVERLAPPEDWINDOW, rectDefault, NULL, MAKEINTRESOURCE(IDR_MENU1));

	if(!LoadAccelTable(MAKEINTRESOURCE(IDR_ACCELERATOR1)))
		MessageBox(_T("Cannot Load Accelerators"),_T("Error"));

	pizzaList = new CListBox;
	pizzaList->Create(WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL, CRect(10,10,1300,600), this, 2);
}

BOOL CApp :: InitInstance() {



	HICON appIcon = LoadIcon(MAKEINTRESOURCE(IDI_SICON));

	m_pMainWnd = new CMainWin;
	m_pMainWnd->SetIcon(appIcon, FALSE);
	m_pMainWnd->ShowWindow(SW_MAXIMIZE);
	m_pMainWnd->UpdateWindow();

	return TRUE;
}

afx_msg void CMainWin :: refreshList() {
	CString str;

	str = "Order : ";
	switch(pizzaType) {
	case 0:
		str += "Marghrita Pizza";
		break;
	case 1:
		str += "Country Special";
		break;
	case 2:
		str += "Spicy Triple Tango";
		break;
	case 3:
		str += "Peppy Paneer";
		break;
	}
	str += " With ";
	if (p_topec)
		str += "Extra Cheese ";
	if (p_topmush)
		str += "Mushroom ";
	if (p_topgc)
		str += "Golden Corn ";
	if (p_toprp)
		str += "Red Pepper ";
	if (p_topbo)
		str += "Black Olives ";
	if (p_topcc)
		str += "Crisp Capsicum ";
	if (!p_topec && !p_topmush && !p_topgc && !p_toprp && !p_topbo && !p_topcc)
		str += "No Toppings";

	MessageBox(str, _T("Status"),MB_ICONINFORMATION | MB_OK);

	pizzaList->AddString(str);
}

afx_msg void CMainWin :: OnExit() {
	int response;
	response = MessageBox(_T("Want to go ?"),_T("Permission to leave"),MB_YESNO);
	if (response == IDYES)
		SendMessage(WM_CLOSE);
}

afx_msg void CMainWin :: OnNewDialog() {
	CNewOrderDialog newOrderDialog(MAKEINTRESOURCE(IDD_NEWORDER), this);
	newOrderDialog.DoModal();
}

afx_msg void CMainWin :: OnHelpDialog() {
	CHelpDialog helpDialogObj(MAKEINTRESOURCE(IDD_HELP), this);
	helpDialogObj.DoModal();
}
afx_msg void CMainWin :: deleteFromList() {
	CDeleteDialog deleteDialogObj(MAKEINTRESOURCE(IDD_DELDIALOG),this);
	deleteDialogObj.DoModal();

	pizzaList->DeleteString(deleteC);
}

BEGIN_MESSAGE_MAP(CMainWin, CFrameWnd)
	ON_COMMAND(ID_WINDOW_HELP, OnHelpDialog)
	ON_COMMAND(ID_WINDOW_EXIT, OnExit)
	ON_COMMAND(ID_ACCELERATORQM, OnHelpDialog)
	ON_COMMAND(ID_ORDER_NEW, OnNewDialog)
	ON_COMMAND(ID_ACCELERATORCTRLN, OnNewDialog)
	ON_COMMAND(ID_ORDER_REFRESHCART, refreshList)
	ON_COMMAND(ID_ACCELERATORCTRLR, refreshList)
	ON_COMMAND(ID_ACCELERATORDEL, deleteFromList)
END_MESSAGE_MAP()

afx_msg void CHelpDialog :: OnCancel() {
	EndDialog(0);
}

BEGIN_MESSAGE_MAP(CHelpDialog, CDialog)
	ON_COMMAND(IDC_HELPD_EXIT, OnCancel)
END_MESSAGE_MAP()

afx_msg void CNewOrderDialog :: OnNewOrderCancel() {
	int response;

	response = MessageBox(_T("Are You Sure You Want To Exit ?"),_T("Not Hungry ?"),MB_YESNO);
	if (response == IDYES)
		EndDialog(0);
}

afx_msg void CNewOrderDialog :: OnOK() {
	CDialog::OnOK();

	pizzaType = pizmarg;
	p_topec = topec;
	p_topmush = topmush;
	p_topgc = topgc;
	p_toprp = toprp;
	p_topbo = topbo;
	p_topcc = topcc;

	EndDialog(IDOK);
}

void CNewOrderDialog :: DoDataExchange(CDataExchange *pDX) {
	CDialog :: DoDataExchange(pDX);

	DDX_Check(pDX, IDC_CHEESE_NO, topec);
	DDX_Check(pDX, IDC_MUSHROOM_NO, topmush);
	DDX_Check(pDX, IDC_GCORN_NO, topgc);
	DDX_Check(pDX, IDC_RPEPPER_NO, toprp);
	DDX_Check(pDX, IDC_BOLIVES_NO, topbo);
	DDX_Check(pDX, IDC_CCAP_NO, topcc);
	DDX_Radio(pDX, IDC_PIZMARG_NO, pizmarg);
}

BEGIN_MESSAGE_MAP(CNewOrderDialog, CDialog)
	ON_COMMAND(IDC_NO_CANCEL, OnNewOrderCancel)
	ON_COMMAND(ID_NEWOOK, OnOK)
END_MESSAGE_MAP()

void CDeleteDialog :: DoDataExchange(CDataExchange *pDX) {
	CDialog :: DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_DELRECORD, deleteid);
}

void CDeleteDialog :: OnConfirmDelete() {
	deleteS = deleteid.GetString();
	EndDialog(0);
}

BEGIN_MESSAGE_MAP(CDeleteDialog, CDialog)
	ON_COMMAND(IDC_CONFIRM_DELETE, OnConfirmDelete)
END_MESSAGE_MAP()
CApp app;