#include "pch.h"
#include "AutoTank.h"
#include "Shell.h"
CImage AutoTank::m_Img[4];
AutoTank::AutoTank()
{
	m_nTrueSpeed = 1;
	m_nSpeed = 1;
	m_nDirection = 4;
	m_nArmor = 2;
	m_ptPos.x = 30;
	m_ptPos.y = 20;
	m_bFriend = false;

	//载入坦克图片
	//  不同方向坦克图片
	//TCHAR cFilePathName[1024];
	//GetModuleFileName(NULL, cFilePathName, 1024);
	//CString str = cFilePathName;
	//int nPos = str.ReverseFind('\\');//反向寻找第一个反斜杠
	//CString strPathName = str.Left(nPos);
	//strPathName = strPathName + L"\\data";

	//CString strImagePathName;
	//strImagePathName = strPathName + L"\\othertankup.png";
	//m_Img[0].Load(strImagePathName);
	//strImagePathName = strPathName + L"\\othertankdown.png";
	//m_Img[1].Load(strImagePathName);
	//strImagePathName = strPathName + L"\\othertankleft.png";
	//m_Img[2].Load(strImagePathName);
	//strImagePathName = strPathName + L"\\othertankright.png";
	//m_Img[3].Load(strImagePathName);
}
void AutoTank::Draw(CDC* pDC)
{
	if (m_nArmor <= 0)
		return;
	//CRect rctTank(m_ptPos.x, m_ptPos.y, m_ptPos.x + 2 * m_nSize, m_ptPos.y + 2 * m_nSize);
	//CImage* pImg = nullptr;
	pDC->Rectangle(m_ptPos.x, m_ptPos.y, m_ptPos.x + 2*m_nSize, m_ptPos.y + 2 * m_nSize);
    pDC->Ellipse(m_ptPos.x+10, m_ptPos.y+10, m_ptPos.x+54, m_ptPos.y+54);
	//switch (m_nDirection)
	//{
	//case 1:
	//	if (m_Img[0].IsNull())
	//		pDC->LineTo(m_ptPos.x + 32, m_ptPos.y - 16);
	//	else
	//		pImg = m_Img;
	//	break;
	//case 2:
	//	if (m_Img[1].IsNull())
	//		pDC->LineTo(m_ptPos.x + 32, m_ptPos.y + 80);
	//	else
	//		pImg = m_Img + 1;
	//	break;
	//case 3:
	//	if (m_Img[2].IsNull())
	//		pDC->LineTo(m_ptPos.x - 16, m_ptPos.y + 32);
	//	else
	//		pImg = m_Img + 2;
	//	break;
	//case 4:
	//	if (m_Img[3].IsNull())
	//		pDC->LineTo(m_ptPos.x + 80, m_ptPos.y + 32);
	//	else
	//		pImg = m_Img + 3;
	//	break;
	//default:
	//	break;
	//}
	//if (pImg)
	//{
	//	pImg->TransparentBlt(pDC->GetSafeHdc(), rctTank, RGB(255, 255, 255));
	//}
	switch (m_nDirection)
   {
    case 1:
	   pDC->Rectangle(m_ptPos.x + m_nSize-3, m_ptPos.y + m_nSize+3, m_ptPos.x + m_nSize + 3, m_ptPos.y -m_nSpeed);
	   break;
    case 2:
	   pDC->Rectangle(m_ptPos.x + m_nSize-3, m_ptPos.y + m_nSize - 3, m_ptPos.x + m_nSize + 3, m_ptPos.y + 2*m_nSize+m_nSpeed);
	   break;
    case 3:
	   pDC->Rectangle(m_ptPos.x + m_nSize + 3, m_ptPos.y + m_nSize + 3, m_ptPos.x -m_nSpeed, m_ptPos.y + m_nSize - 3);
	   break;
    case 4:
	   pDC->Rectangle(m_ptPos.x + m_nSize - 3, m_ptPos.y + m_nSize + 3, m_ptPos.x + 2*m_nSize+m_nSpeed, m_ptPos.y + m_nSize - 3);
	   break;
    default:
	   break;
    }
	//_int64 tmCurrent = GetTickCount64();
	//_int64 tmGap = tmCurrent - m_InitalTime;
	//switch (m_nDirection)
	//{
	//case 1:
	//	m_ptPos.y -= (long)m_nTrueSpeed * tmGap / 3.5;
	//	break;
	//case 2:
	//	m_ptPos.y += (long)m_nTrueSpeed * tmGap / 3.5;
	//	break;
	//case 3:
	//	m_ptPos.x -= (long)m_nTrueSpeed * tmGap / 3.5;
	//	break;
	//case 4:
	//	m_ptPos.x += (long)m_nTrueSpeed * tmGap / 3.5;
	//	break;
	//default:
	//	break;
	//}
	//m_InitalTime = tmCurrent;
	if (m_ptPos.x <= -10 ||/* m_ptPos.y <= -10 || m_ptPos.x >= 1290 ||*/ m_ptPos.y >= 900)
		m_nArmor = 0;
}
Shell AutoTank::AutoFire()
{
	Shell newShell;
	newShell.m_ptPos = m_ptPos;
	newShell.SetDirection(m_nDirection);
	newShell.SetInitalTime();
	newShell.SetSize(5);
	newShell.SetArmor(1);
	newShell.SetFriend(false);
	return newShell;
}
void AutoTank::SetInitalTime()
{
	m_InitalTime = GetTickCount64();
}
void AutoTank::ChangeDirection(MyObject& playerTank)
{
	double dx = double(playerTank.m_ptPos.x - m_ptPos.x);
	double dy = double(playerTank.m_ptPos.y - m_ptPos.y);
	m_dDis = sqrt(dx * dx + dy * dy);
	if (fabs(fabs(dx) - fabs(dy)) >= 10 && m_dDis <= 600)
	{
		if (fabs(dx) > fabs(dy))
		{
			if (dx > 0)
				m_nDirection = 4;
			else m_nDirection = 3;
		}
		else if (fabs(dx) < fabs(dy))
		{
			if (dy > 0)
				m_nDirection = 2;
			else m_nDirection = 1;
		}
	}
}
void AutoTank::Move(int nDirection)
{
	m_nDirection = nDirection;
	switch (nDirection)
	{
	case 1:
		m_ptPos.y -= m_nSpeed;
		break;
	case 2:
		m_ptPos.y += m_nSpeed;
		break;
	case 3:
		m_ptPos.x -= m_nSpeed;
		break;
	case 4:
		m_ptPos.x += m_nSpeed;
		break;
	default:
		break;
	}
}