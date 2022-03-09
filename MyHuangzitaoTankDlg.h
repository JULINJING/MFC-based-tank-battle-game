
// MyHuangzitaoTankDlg.h: 头文件
//

#pragma once
#include "Tank.h"//增加
#include "Shell.h"
#include "Wall.h"
#include "AutoTank.h"
#include "vector""
#include "sapi.h"//发声
#include "mutex"


// CMyHuangzitaoTankDlg 对话框
class CMyHuangzitaoTankDlg : public CDialogEx
{
// 构造
public:
	CMyHuangzitaoTankDlg(CWnd* pParent = nullptr);	// 标准构造函数
	~CMyHuangzitaoTankDlg() { Sleep(1000); };
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MYHUANGZITAOTANK_DIALOG };
#endif
public:
	//CPoint m_tank;//增加
	ISpVoice* m_pVoice;//语音合成
	Tank m_tank;//增加
	std::vector<Shell> m_vecShell;
	std::vector<Wall>m_vecWall;
	std::vector<AutoTank> m_EnemyTank;//敌方坦克,自行实现。受到阻碍后自动改变方向，自行开炮
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);//j增加

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	//多线程相关函数
	static void Judgy(CMyHuangzitaoTankDlg* pThis);//碰撞测试，多线程方式运行
	std::mutex m_mtxJudgy;//碰撞锁

	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedCreatewall();
	afx_msg void OnBnClickedExit();
	afx_msg void OnStnClickedBackground();
	afx_msg void OnBnClickedConfig();
//	afx_msg void OnBnClickedAddshellarmor();
//	afx_msg void OnBnClickedCreateautotank();
	afx_msg void OnMytankBlood();
//	afx_msg void OnBnClickedCreateetank();
	afx_msg void OnBnClickedNine();
	afx_msg void OnBnClickedpause();
};
