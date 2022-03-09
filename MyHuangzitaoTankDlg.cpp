
// MyHuangzitaoTankDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MyHuangzitaoTank.h"
#include "MyHuangzitaoTankDlg.h"
#include "afxdialogex.h"
#include "Windows.h"
#include "thread"
#include "ConfigDlg.h"
#include <mmsystem.h>
#pragma comment(lib, "Winmm.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
static bool end = true;
static bool pause;
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMyHuangzitaoTankDlg 对话框



CMyHuangzitaoTankDlg::CMyHuangzitaoTankDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MYHUANGZITAOTANK_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	srand(time(0));
	m_tank.m_ptPos.x = rand() % 800 + 2 * m_tank.GetSize();
	m_tank.m_ptPos.y = m_tank.m_ptPos.x;//增加 初始化
}

void CMyHuangzitaoTankDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMyHuangzitaoTankDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_KEYDOWN()
	ON_WM_LBUTTONDOWN()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_CreateWall, &CMyHuangzitaoTankDlg::OnBnClickedCreatewall)
	ON_BN_CLICKED(IDC_EXIT, &CMyHuangzitaoTankDlg::OnBnClickedExit)
	ON_STN_CLICKED(IDC_BACKGROUND, &CMyHuangzitaoTankDlg::OnStnClickedBackground)
	ON_BN_CLICKED(IDC_CONFIG, &CMyHuangzitaoTankDlg::OnBnClickedConfig)
	//ON_BN_CLICKED(IDC_AddShellArmor, &CMyHuangzitaoTankDlg::OnBnClickedAddshellarmor)
	//ON_BN_CLICKED(IDC_CreateAutoTank, &CMyHuangzitaoTankDlg::OnBnClickedCreateautotank)
	ON_COMMAND(IDC_Mytank_Blood, &CMyHuangzitaoTankDlg::OnMytankBlood)
	//ON_BN_CLICKED(IDC_CreateETank, &CMyHuangzitaoTankDlg::OnBnClickedCreateetank)
	ON_BN_CLICKED(IDC_NINE, &CMyHuangzitaoTankDlg::OnBnClickedNine)
	ON_BN_CLICKED(IDC_pause, &CMyHuangzitaoTankDlg::OnBnClickedpause)
END_MESSAGE_MAP()


// CMyHuangzitaoTankDlg 消息处理程序

BOOL CMyHuangzitaoTankDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。
	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	int nTimerID1 = 1;
	int nTimerID2 = 2;
	int nTimerID3 = 3;
	SetTimer(nTimerID1,4, NULL);//一号定时器，4ms，全体发送 增加
	SetTimer(nTimerID2, 2, NULL);
	SetTimer(nTimerID3, 2000, NULL);//自动开火


	//敌方坦克
	CPoint gdpt[4];
	gdpt[0].x = 300;
	gdpt[0].y = 200;
	gdpt[1].x = 800;
	gdpt[1].y = 600;
	gdpt[2].x = 400;
	gdpt[2].y = 300;
	gdpt[3].x = 700;
	gdpt[3].y = 300;
	for (int k = 0; k < 4; k++)
	{

		AutoTank autotank;
		autotank.m_ptPos.x = gdpt[k].x;
		autotank.m_ptPos.y = gdpt[k].y;
		autotank.SetDirection(k + 1);
		autotank.SetArmor(2);
		m_EnemyTank.push_back(autotank);
	}
	//随机墙
	srand(time(NULL));//一次
	for (auto& w : m_vecWall)
	{
		if (w.m_ptPos.x >= 2 * w.GetSize() || w.m_ptPos.y >= 2 * w.GetSize() || w.m_ptPos.x <= 20 * w.GetSize() || w.m_ptPos.y <= 13 * w.GetSize())
			m_vecWall.clear();
	}
	CRect rct;
	GetDlgItem(IDC_BACKGROUND)->GetClientRect(rct);
	//墙
	for (int i = 0; i < 68; i++)//横21 竖15
	{
		Wall brick;
		brick.SetArmor(999);
		brick.m_flag = 1;
		if (i <= 14)
			brick.SetPosition(0, 2 * i * brick.GetSize());
		else if (i <= 34)
			brick.SetPosition(2 * (i - 14) * brick.GetSize(), 2 * 14 * brick.GetSize());
		else if (i <= 48)
			brick.SetPosition(2 * 20 * brick.GetSize(), 2 * (48 - i) * brick.GetSize());
		else
			brick.SetPosition(2 * (68 - i) * brick.GetSize(), 0);
		m_vecWall.push_back(brick);
	}
	for (int i = 0; i < 20; i++)
	{
		//随机数
		int nX = rand();//调用n次0~RAND_MAX(为32767)
		int nY = rand();
		CPoint pt;
		pt.x = double(nX) / RAND_MAX * 10 + 1;//1~10随机数
		pt.y = double(nY) / RAND_MAX * 10 + 1;
		//程序窗口
		int nWidth = rct.Width();
		int nHeight = rct.Height();
		//建墙
		Wall w1;
		w1.m_ptPos = pt;
		w1.m_flag = 1;
		//w1.m_Img.Draw((int)pt.x * nWidth / 10 + 2 * i, (int)pt.y * nHeight / 10);
		w1.SetArmor(2);
		w1.SetSize(32);
		if (pt.x * nWidth / 10 + w1.GetSize() <= nWidth)
			w1.SetPosition(pt.x * nWidth / 10 - 2 * w1.GetSize() + 6, pt.y * nHeight / 10);
		else
			w1.SetPosition(pt.x * nWidth / 10 - w1.GetSize(), pt.y * nHeight / 10);
		m_vecWall.push_back(w1);
	}
	m_pVoice = NULL;
	::CoInitialize(NULL);
	HRESULT hr = CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice, (void**)&m_pVoice);
	if (SUCCEEDED(hr))
	{
		m_pVoice->SetVolume((USHORT)100);//设置音量，范围为0~100
		m_pVoice->SetRate(2);//设置速度，范围为-10~10
	}
	else if (m_pVoice)
	{
		m_pVoice->Release();
		m_pVoice = NULL;
		::CoUninitialize();//释放com资源
	}

	if (m_pVoice)
		m_pVoice->Speak(L"游戏开始", SPF_ASYNC, NULL);
	TCHAR cFilePathName[1024];
	GetModuleFileName(NULL, cFilePathName, 1024);
	CString str = cFilePathName;
	int nPos = str.ReverseFind('\\');//反向寻找第一个反斜杠
	CString strPathName = str.Left(nPos);
	strPathName = strPathName + L"\\data";
	CString strImagePathName;
	strImagePathName = strPathName + L"\\BGM.wav";
	PlaySound(strImagePathName, 0, SND_FILENAME | SND_ASYNC);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMyHuangzitaoTankDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMyHuangzitaoTankDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
	//CDC* pDC = GetDC();
	CDC* pdc = GetDC();
	CMemDC dc(*pdc, this);
	CDC* pDC = &dc.GetDC();
	//背景
	CRect rct;
	GetWindowRect(&rct);
	ScreenToClient(&rct);
	pDC->Rectangle(rct);
	//数组
	for (auto& s1 : m_vecShell)
		if (end!=false)
		{
			s1.Draw(pDC);
		}
	for (auto& w : m_vecWall)
	{
		w.Draw(w.m_flag, pDC);
		if (!m_tank.IsOverlap(w))
			//我方坦克
			m_tank.Draw(pDC);
		else
		continue;
		CString str3;
		str3.Format(L"%d  ", m_vecWall.size()-68);
		pDC->TextOutW(100, 520, str3);
	}
	int num=m_EnemyTank.size();
	int _0Armor=0;
	bool win=false;
	for (auto& t : m_EnemyTank)
	{
		int iniArmor = 2;
		t.Draw(pDC);
		CString str1;
		str1.Format(L"%d  ", iniArmor);
		pDC->TextOutW(100, 220, str1);
		if (t.m_nArmor <= 0)
		{
			num -= 1;
			_0Armor += 1;
		}
		CString str2;
		str2.Format(L"%d  ", num);
		pDC->TextOutW(100, 320, str2);
		if (_0Armor == m_EnemyTank.size())
			win = true;
	}
	//提示
	if (win)
	{
		pDC->TextOutW(620, 400, L"Game Over!");
		pDC->TextOutW(620, 550, L"You Win!");
		if (m_pVoice)
			m_pVoice->Speak(L"You have won the game", SPF_ASYNC, NULL);
		end = true;
		//m_vecWall.clear();
	}
	else if (m_EnemyTank.size()!=0 && m_tank.m_nArmor <= 0)
	{
		pDC->TextOutW(620, 400, L"Game Over!");
		pDC->TextOutW(620, 550, L"You Fail!");
		end = false;
	}
	if (pause == true)
	{
		pDC->TextOutW(620, 475, L"游戏暂停");
	}
	//属性
	CString str;
	if (m_tank.m_nArmor >= 0&&m_tank.m_nArmor<=100)
	{
		str.Format(L"%d  ", m_tank.m_nArmor);
		pDC->TextOutW(100, 120, str);
	}
	else
	pDC->TextOutW(100, 120, L"0");
	pDC->TextOutW(100, 420, L"1");
	//ReleaseDC(pdc);
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMyHuangzitaoTankDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMyHuangzitaoTankDlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CDC* pDC = GetDC();
	CString str;
	str.Format(L"%c", nChar);
	CDialogEx::OnKeyDown(nChar, nRepCnt, nFlags);
}


BOOL CMyHuangzitaoTankDlg::PreTranslateMessage(MSG* pMsg)//虚函数
{
	// TODO: 在此添加专用代码和/或调用基类
	if (end != false)
	{
		CPoint tmp = m_tank.m_ptPos;
		if (pMsg->message == WM_KEYDOWN)
		{
			if (pMsg->wParam == VK_UP)
			{
				if (m_tank.IsEnableMove(1))
					m_tank.Move(1);
			}
			else if (pMsg->wParam == VK_DOWN)
			{
				if (m_tank.IsEnableMove(2))
					m_tank.Move(2);
			}
			else if (pMsg->wParam == VK_LEFT)
			{
				if (m_tank.IsEnableMove(3))
					m_tank.Move(3);
			}
			else if (pMsg->wParam == VK_RIGHT)
			{
				if (m_tank.IsEnableMove(4))
					m_tank.Move(4);
			}
			for (auto& w : m_vecWall)
			{
				if (w.GetArmor() > 0 && m_tank.IsOverlap(w))
				{
					m_tank.m_ptPos = tmp;
					break;
				}
			}
			if (m_tank.m_ptPos.x <= -10 || m_tank.m_ptPos.y <= -10 || m_tank.m_ptPos.x >= 1290 || m_tank.m_ptPos.y >= 900)
				m_tank.m_ptPos = tmp;
			Invalidate();
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


void CMyHuangzitaoTankDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	static __int64 tmLast = 0;
	__int64 tmCurrent = GetTickCount64();
	if (tmCurrent - tmLast > 500)//炮管冷却，开炮间隔时间要大于0.5秒
	{
		if (m_pVoice)
	       m_pVoice->Speak(L"Fire", SPF_ASYNC, NULL);
		TCHAR cFilePathName[1024];
		GetModuleFileName(NULL, cFilePathName, 1024);
		CString str = cFilePathName;
		int nPos = str.ReverseFind('\\');//反向寻找第一个反斜杠
		CString strPathName = str.Left(nPos);
		strPathName = strPathName + L"\\data";
		CString strImagePathName;
		strImagePathName = strPathName + L"\\Win.wav";
		PlaySound(strImagePathName, 0, SND_FILENAME | SND_ASYNC);
		if (m_EnemyTank.size() != 0 && m_tank.m_nArmor != 0)
		{
			Shell shell = m_tank.Fire();
			m_vecShell.push_back(shell);
		}
		tmLast = tmCurrent;
	}
	Invalidate();
	CDialogEx::OnLButtonDown(nFlags, point);
}


void CMyHuangzitaoTankDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	switch (nIDEvent)
	{
	case 1:
		Invalidate(TRUE);
		break;
	case 2://碰撞测试
	{
		m_mtxJudgy.try_lock();
		std::thread Overlay(Judgy, this);
		Overlay.detach();
		m_mtxJudgy.unlock();
	}
	break;
	case 3://自动开火
	{
		for (int i = 0; i < 4; i++)
		{
			if (end != false&&m_EnemyTank[i].m_nArmor>0)
			{
				Shell shell = m_EnemyTank[i].AutoFire();
				m_vecShell.push_back(shell);
			}
		}
	}
	break;
	default:
		break;
	}
	CDialogEx::OnTimer(nIDEvent);
}
void CMyHuangzitaoTankDlg::Judgy(CMyHuangzitaoTankDlg* pThis)//)
{
	int i, j;
	std::vector<Shell>& vecShell = pThis->m_vecShell;
	std::vector<Wall>& vecWall = pThis->m_vecWall;
	std::vector<AutoTank>& vecEnemyTank = pThis->m_EnemyTank;
	Tank& MyTank = pThis->m_tank;

	TCHAR cFilePathName[1024];
	GetModuleFileName(NULL, cFilePathName, 1024);
	CString str = cFilePathName;
	int nPos = str.ReverseFind('\\');//反向寻找第一个反斜杠
	CString strPathName = str.Left(nPos);
	strPathName = strPathName + L"\\data";
	CString strImagePathName1;
	strImagePathName1 = strPathName + L"\\explode.wav";
	CString strImagePathName2;
	strImagePathName2 = strPathName + L"\\BGM.wav";
	CString strImagePathName3;
	strImagePathName3 = strPathName + L"\\GameOver.wav";
	//炮弹与其他炮弹、我方坦克、墙壁、敌方坦克间的碰撞测试
	for (i = 0; i < vecShell.size(); i++)
	{
		//炮弹与其它炮弹碰撞
		if (vecShell[i].m_nArmor <= 0)
			continue;
		for (j = i + 1; j < vecShell.size(); j++)
		{
			//友军无伤害，无效炮弹无伤害
			if (vecShell[j].m_nArmor <= 0 || vecShell[i].GetFriend() == vecShell[j].GetFriend())
				continue;
			if (vecShell[i].IsOverlap(vecShell[j]))
				vecShell[i].m_nArmor = vecShell[j].m_nArmor = 0;
		}
		//炮弹与墙碰撞
		if (vecShell[i].m_nArmor <= 0)
			continue;
		for (j = 0; j < vecWall.size(); j++)
		{
			if (vecWall[j].m_nArmor > 0 && vecShell[i].IsOverlap(vecWall[j]))
			{
				vecWall[j].m_nArmor -= vecShell[i].m_nArmor;
				vecShell[i].m_nArmor = 0;
			}
		}
		//炮弹与我方坦克碰撞,要判断敌友, m_bFriend
		if (vecShell[i].m_nArmor <= 0)
			continue;
		if (MyTank.m_nArmor > 0 && vecShell[i].IsOverlap(MyTank) && vecShell[i].GetFriend() != MyTank.GetFriend())
		{
			MyTank.m_nArmor -= vecShell[i].m_nArmor;
			vecShell[i].m_nArmor = 0;
			PlaySound(strImagePathName1, 0, SND_FILENAME | SND_ASYNC);
		if (vecEnemyTank.size() != 0 && MyTank.m_nArmor <= 0)
		{
			PlaySound(strImagePathName3, 0, SND_FILENAME | SND_ASYNC);
		}
		}

		//炮弹与敌方坦克碰撞,要判断敌友, m_bFriend
		if (vecShell[i].m_nArmor <= 0)
			continue;
		for (int k = 0; k < vecEnemyTank.size(); k++)
		{
			if (vecEnemyTank[k].m_nArmor >= 0 
				&& vecShell[i].IsOverlap(vecEnemyTank[k])
				&& vecShell[i].GetFriend() != vecEnemyTank[k].GetFriend())
			{
				vecEnemyTank[k].m_nArmor -= vecShell[i].m_nArmor;
				vecShell[i].m_nArmor = 0;
			}
		}
	}

//敌方坦克与墙壁、我方坦克、敌方坦克的碰撞测试及自动追踪我方坦克
    for (i=0; i<vecEnemyTank.size(); i++)
{
	//自动追踪
		if (!vecEnemyTank[i].m_nArmor)
			continue;
		vecEnemyTank[i].pre_pt = vecEnemyTank[i].m_ptPos;
		if (end != false)
		{
			vecEnemyTank[i].ChangeDirection(MyTank);
			if (vecEnemyTank[i].m_dDis <= 1000)
				vecEnemyTank[i].Move(vecEnemyTank[i].GetDirection());
		}
    //敌方坦克与墙碰撞
	for (j=0;j<vecWall.size();j++)
	{
		if (vecWall[j].GetArmor() > 0 && vecWall[j].IsOverLapRect_(vecWall[j], vecEnemyTank[i]))
		{
			if (!vecEnemyTank[i].m_nArmor)
				continue;
			vecEnemyTank[i].m_ptPos =vecEnemyTank[i].pre_pt;
			int d = vecEnemyTank[i].GetDirection();
			if (end != false)
			switch (d) 
			{
			case 1:
				d = 4;
				break;
			case 2:
				d = 3;
				break;
			case 3:
				d = 1;
				break;
			case 4:
				d = 2; 
				break;
			}
			vecEnemyTank[i].SetDirection(d);
			//m_FoeTank.WhichDirection();
		}
	}
	//敌方坦克与我方坦克碰撞
	if (vecEnemyTank[i].m_nArmor >= 0 
		&& vecEnemyTank[i].IsOverlap(MyTank) 
		&& vecEnemyTank[i].GetFriend() != MyTank.GetFriend())
	{
		int temp;
		temp = MyTank.m_nArmor;
	    MyTank.m_nArmor-=vecEnemyTank[i].m_nArmor;
		vecEnemyTank[i].m_nArmor -= temp;
		if (vecEnemyTank.size() != 0 && MyTank.m_nArmor <= 0)
		{
			PlaySound(strImagePathName3, 0, SND_FILENAME | SND_ASYNC);
		}
	}
	//敌方坦克与敌方坦克碰撞
	if (vecEnemyTank[i].m_nArmor <= 0)
		continue;
	for (j = i + 1; j < vecEnemyTank.size(); j++)
	{
		//友军无伤害，无效炮弹无伤害
		if (vecEnemyTank[i].GetFriend() == vecEnemyTank[j].GetFriend() 
			&& vecEnemyTank[i].IsOverLapRect_(vecEnemyTank[i], vecEnemyTank[j]))
		{
			if (!vecEnemyTank[i].m_nArmor)
				continue;
			vecEnemyTank[i].m_ptPos = vecEnemyTank[i].pre_pt;
		}
	}
}

//删除amr小于等于0的炮弹
for (i=vecShell.size()-1; i>=0; i--)
{
	if (vecShell[i].m_nArmor <= 0)
		vecShell.erase(vecShell.begin()+i);
}
//删除arm小于等于0的墙
for (i=vecWall.size()-1; i>=0; i--)
{
	if (vecWall[i].m_nArmor <= 0)
		vecWall.erase(vecWall.begin() + i);
}
//删除arm小于等于0的坦克
//for (i = vecEnemyTank.size() - 1; i >= 0; i--)
//{
//	if (vecEnemyTank[i].m_nArmor <= 0)
//		vecEnemyTank.erase(vecEnemyTank.begin() + i);
//}
//......
}


void CMyHuangzitaoTankDlg::OnBnClickedCreatewall()
{
	// TODO: 在此添加控件通知处理程序代码
	m_tank.m_nArmor += 1;
	Invalidate(TRUE);
}


void CMyHuangzitaoTankDlg::OnBnClickedExit()
{
	// TODO: 在此添加控件通知处理程序代码
	exit(0);
}


void CMyHuangzitaoTankDlg::OnStnClickedBackground()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CMyHuangzitaoTankDlg::OnBnClickedConfig()
{
	ConfigDlg dlg;
	dlg.DoModal();
	// TODO: 在此添加控件通知处理程序代码
}

BOOL CMyHuangzitaoTankDlg::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
	return CDialogEx::OnEraseBkgnd(pDC);
}


//void CMyHuangzitaoTankDlg::OnBnClickedAddshellarmor()
//{
//	// TODO: 在此添加控件通知处理程序代码
//	int x=1;
//	m_tank.SetArmor(x);
//	x++;
//}


//void CMyHuangzitaoTankDlg::OnBnClickedCreateautotank()
//{
//	// TODO: 在此添加控件通知处理程序代码
//		//自动坦克
//	CPoint gdpt[3];
//	gdpt[0].x = 300;
//	gdpt[0].y = 200;
//	gdpt[1].x = 800;
//	gdpt[1].y = 600;
//	gdpt[2].x = 400;
//	gdpt[2].y = 300;
//	AutoTank autotank;
//	autotank.m_ptPos = gdpt[0];
//	m_EnemyTank.push_back(autotank);
//	//for (int k = 0; k < 3; k++)
//	//{
//	//	AutoETank autotank;
//	//	autotank.m_ptPos = gdpt[k];
//	//	autotank.SetArmor(1);
//	//	autotank.SetSize(32);
//	//	autotank.SetDirection(k + 1);
//	//	autotank.SetSpeed(10);
//	//	autotank.SetFriend(false);
//	///*	Shell Eshell=autotank.Fire();
//	//	_int64 tmCurrent = GetTickCount64();
//	//	_int64 tmGap = tmCurrent - Eshell.m_InitalTime;
//	//	if(tmGap>1)
//	//	m_vecShell.push_back(Eshell);*/
//	//	m_EnemyTank.push_back(autotank);
//	//}
//	Invalidate();
//}


void CMyHuangzitaoTankDlg::OnMytankBlood()
{
	// TODO: 在此添加命令处理程序代码
}


//void CMyHuangzitaoTankDlg::OnBnClickedCreateetank()
//{
//	// TODO: 在此添加控件通知处理程序代码
//	CPoint gdpt[3];
//	gdpt[0].x = 300;
//	gdpt[0].y = 200;
//	gdpt[1].x = 800;
//	gdpt[1].y = 600;
//	gdpt[2].x = 400;
//	gdpt[2].y = 300;
//	for (int k = 0; k < 3; k++)
//	{
//		AutoETank autotank;
//		autotank.m_ptPos = gdpt[k];
//		autotank.SetArmor(1);
//		autotank.SetSize(32);
//		autotank.SetDirection(k + 1);
//		autotank.SetSpeed(10);
//		autotank.SetFriend(false);
//		/*	Shell Eshell=autotank.Fire();
//			_int64 tmCurrent = GetTickCount64();
//			_int64 tmGap = tmCurrent - Eshell.m_InitalTime;
//			if(tmGap>1)
//			m_vecShell.push_back(Eshell);*/
//		m_EnemyTank.push_back(autotank);
//	}
//	Invalidate();
//}


void CMyHuangzitaoTankDlg::OnBnClickedNine()
{
	// TODO: 在此添加控件通知处理程序代码
	for (int j = 0; j < 8; j++)
	{
		Wall brick;
		brick.SetArmor(3);
		brick.m_flag = 1;
		if (j <= 2)
			brick.SetPosition(2 * (9 + j) * brick.GetSize(), 2 * 6 * brick.GetSize());//中11,8
		else if (j <= 4)
			brick.SetPosition(2 * 11 * brick.GetSize(), 2 * (j + 4) * brick.GetSize());
		else if (j <= 6)
			brick.SetPosition(2 * (j + 4) * brick.GetSize(), 2 * 8 * brick.GetSize());
		else
			brick.SetPosition(2 * 9 * brick.GetSize(), 2 * j * brick.GetSize());
		m_vecWall.push_back(brick);
	}
}

static int jsq = 0;//计数
void CMyHuangzitaoTankDlg::OnBnClickedpause()
{
	// TODO: 在此添加控件通知处理程序代码
	jsq++;
	if (jsq % 2 == 1)
	{
		end = false;
		pause = true;
	}
	else
	{
		end = true;
		pause = false;
	}
}
