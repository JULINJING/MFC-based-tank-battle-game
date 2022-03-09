#include "pch.h"
#include "Wall.h"
CImage Wall::m_Img;
Wall::Wall()
{
	m_nSpeed = 0;
	m_nArmor = 0;
	m_nDirection = 1;
	m_ptPos.x = -1;
	m_ptPos.y = -1;
	//载入墙图片
  //不同种类墙图片
	//TCHAR cFilePathName[1024];
	//GetModuleFileName(NULL, cFilePathName, 1024);
	//CString str = cFilePathName;
	//int nPos = str.ReverseFind('\\');//反向寻找第一个反斜杠
	//CString strPathName = str.Left(nPos);
	//strPathName = strPathName + L"\\data";

	//CString strImagePathName;
	//strImagePathName = strPathName + L"\\brick.png";
	//m_Img.Load(strImagePathName);
	//strImagePathName = strPathName + L"\\metalWall.png";
	//m_Img[1].Load(strImagePathName);
	//strImagePathName = strPathName + L"\\home.png";
	//m_Img[2].Load(strImagePathName);
	//strImagePathName = strPathName + L"\\tree.png";
	//m_Img[3].Load(strImagePathName);
	if (m_Img.IsNull())
		m_Img.Load(L"D:\\brick.png");
}
void Wall:: SetPosition(int x, int y)
{
	m_ptPos.x = x;
	m_ptPos.y = y;
}
void Wall::Draw(int nflag,CDC* pDC)
{
	if (m_nArmor <= 0)
		return;
	int nsize = m_nSize;
	nflag = m_flag;
	switch (nflag)
	{
	case 1:
		pDC->Rectangle(m_ptPos.x, m_ptPos.y, m_ptPos.x + 2 * nsize, m_ptPos.y + 2 * nsize);
		break;
	case 2:
	{
		CRect rctWall(m_ptPos.x, m_ptPos.y, m_ptPos.x + 2 * nsize, m_ptPos.y + 2 * nsize);
		CImage* pImg = nullptr;
		if (m_Img.IsNull())
			pDC->LineTo(m_ptPos.x, m_ptPos.y);
		if (pImg)
		{
			//pImg->Draw(pDC->GetSafeHdc(), rctWall);
			pImg->TransparentBlt(pDC->GetSafeHdc(), rctWall, RGB(2, 255, 255));
		}
	}
	break;
	default:
		break;
	}
}