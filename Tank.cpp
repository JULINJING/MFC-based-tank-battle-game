#include "pch.h"
#include "Tank.h"
#include "Shell.h"
CImage Tank::m_img[4];
Tank::Tank()
{
	m_nSpeed = 10;
	m_nDirection = 4;
	m_nArmor = 6;
	m_ptPos.x = 30;
	m_ptPos.y = 20;
	m_bFriend = true;

	//载入坦克图片
	  //不同方向坦克图片
	TCHAR cFilePathName[1024];
	GetModuleFileName(NULL, cFilePathName, 1024);
	CString str = cFilePathName;
	int nPos = str.ReverseFind('\\');//反向寻找第一个反斜杠
		CString strPathName = str.Left(nPos);
		strPathName = strPathName + L"\\data";

	CString strImagePathName;
	strImagePathName = strPathName + L"\\tankup.png";
	m_img[0].Load(strImagePathName);
	strImagePathName = strPathName + L"\\tankdown.png";
	m_img[1].Load(strImagePathName);
	strImagePathName = strPathName + L"\\tankleft.png";
	m_img[2].Load(strImagePathName);
	strImagePathName = strPathName + L"\\tankright.png";
	m_img[3].Load(strImagePathName);
}
void Tank::Draw(CDC* pDC)
{
	if (m_nArmor <= 0)
		return;
	CRect rctTank(m_ptPos.x, m_ptPos.y, m_ptPos.x + 2*m_nSize, m_ptPos.y + 2*m_nSize);
	CImage* pImg = nullptr;
	//pDC->Rectangle(m_ptPos.x, m_ptPos.y, m_ptPos.x + 64, m_ptPos.y + 64);
	//pDC->Rectangle(rctTank);
	//pDC->Ellipse(m_ptPos.x+10, m_ptPos.y+10, m_ptPos.x+54, m_ptPos.y+54);
	switch (m_nDirection)
	{
	case 1:
		if (m_img[0].IsNull())
			pDC->LineTo(m_ptPos.x + 32, m_ptPos.y - 16);
		else
			pImg = m_img;
		break;
	case 2:
		if (m_img[1].IsNull())
			pDC->LineTo(m_ptPos.x + 32, m_ptPos.y + 80);
		else
		pImg = m_img + 1;
		break;
	case 3:
		if (m_img[2].IsNull())
			pDC->LineTo(m_ptPos.x -16, m_ptPos.y + 32);
		else
			pImg = m_img + 2;
		break;
	case 4:
		if (m_img[3].IsNull())
			pDC->LineTo(m_ptPos.x + 80, m_ptPos.y + 32);
		else
			pImg = m_img + 3;
		break;
	default:
		break;
	}
	if (pImg)
	{
		//pImg->Draw(pDC->GetSafeHdc(), rctTank);
		pImg->TransparentBlt(pDC->GetSafeHdc(), rctTank, RGB(255, 255, 255));
	}
	//switch (m_nDirection)
	//{
	//case 1:
	//	pDC->Rectangle(m_ptPos.x + 29, m_ptPos.y + 35, m_ptPos.x + 35, m_ptPos.y -10);
	//	break;
	//case 2:
	//	pDC->Rectangle(m_ptPos.x + 29, m_ptPos.y + 29, m_ptPos.x + 35, m_ptPos.y +74);
	//	break;
	//case 3:
	//	pDC->Rectangle(m_ptPos.x + 35, m_ptPos.y + 35, m_ptPos.x -10, m_ptPos.y + 29);
	//	break;
	//case 4:
	//	pDC->Rectangle(m_ptPos.x + 29, m_ptPos.y + 35, m_ptPos.x + 74, m_ptPos.y + 29);
	//	break;
	//default:
	//	break;
	//}
}
void Tank::Move(int nDirection) 
{
	m_nDirection = nDirection;
	switch(nDirection)
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
Shell Tank::Fire()
{
	Shell newShell;
	newShell.m_ptPos = m_ptPos;
	newShell.SetDirection(m_nDirection);
	newShell.SetInitalTime();
	newShell.SetSize(5);
	bool bFriend = true;
	newShell.SetFriend(bFriend);
	return newShell;
}
bool Tank::IsEnableMove(int nDirection)
{
	return true;
}