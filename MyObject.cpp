#include "pch.h"
#include "MyObject.h"
#include "math.h"

void MyObject::Draw(CDC *pDC)
{
	pDC->Ellipse(m_ptPos.x - m_nSize, m_ptPos.y - m_nSize, m_ptPos.x + m_nSize, m_ptPos.y + m_nSize);
}
bool MyObject:: IsOverlap(MyObject& obj) 
{
	double dx = m_ptPos.x - obj.m_ptPos.x;
	double dy = m_ptPos.y - obj.m_ptPos.y;
	double dDis = sqrt(dx * dx + dy * dy);
	if (obj.GetSize() + m_nSize >= dDis)
		return true;
	else
		return false;
}
bool MyObject::IsFriend(MyObject& OBJ)
{
	return true;
}
void MyObject:: SetSize(int nSize)
{
	if (nSize < 4)
		m_nSize = 4;
	else
		m_nSize = nSize;
	//m_nSize=(nSize<10)?10:nSize;
}
int MyObject::GetSize()
{
	return m_nSize;
}
void MyObject::SetDirection(int nDir)
{
	if (nDir < 1 || nDir>4)
		m_nDirection = 1;
	else
		m_nDirection = nDir;
	//m_nDirection=(nDir<1||nDir>4)?1:nDir;
}
int MyObject::GetDirection()
{
	return m_nDirection;
}
void MyObject::SetArmor(int nArmor)
{
	if (nArmor > 0)
		m_nArmor = nArmor;
	else
		m_nArmor = 1;
}
int MyObject :: GetArmor()
{
	return m_nArmor;
}
void MyObject::SetSpeed(int nSpeed)
{
	m_nSpeed = nSpeed;
}
int MyObject::GetSpeed()
{
	return m_nSpeed;
}
void MyObject::SetFriend(bool bFriend)
{
	m_bFriend = bFriend;
}
bool MyObject::GetFriend()
{
	return m_bFriend;
}