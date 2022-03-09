// ConfigDlg.cpp: 实现文件
//

#include "pch.h"
#include "MyHuangzitaoTank.h"
#include "ConfigDlg.h"
#include "afxdialogex.h"


// ConfigDlg 对话框

IMPLEMENT_DYNAMIC(ConfigDlg, CDialogEx)

ConfigDlg::ConfigDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_CONFIG, pParent)
{

}

ConfigDlg::~ConfigDlg()
{
}

void ConfigDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ConfigDlg, CDialogEx)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &ConfigDlg::OnLvnItemchangedList1)
	ON_NOTIFY(MCN_SELCHANGE, IDC_MONTHCALENDAR1, &ConfigDlg::OnMcnSelchangeMonthcalendar1)
	//ON_BN_CLICKED(IDC_AddShellArmor, &ConfigDlg::OnBnClickedAddshellarmor)
END_MESSAGE_MAP()


// ConfigDlg 消息处理程序


void ConfigDlg::OnLvnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}


void ConfigDlg::OnMcnSelchangeMonthcalendar1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMSELCHANGE pSelChange = reinterpret_cast<LPNMSELCHANGE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}


//void ConfigDlg::OnBnClickedAddshellarmor()
//{
//	// TODO: 在此添加控件通知处理程序代码
//}
