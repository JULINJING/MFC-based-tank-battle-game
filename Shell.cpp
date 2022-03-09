#include "pch.h"
#include "Shell.h"
Shell::Shell()
{
	m_nSpeed = 1;
	m_nDirection = -1;
	m_nArmor = 1;
	m_ptPos.x = -1;
	m_ptPos.y = -1;
}
void Shell::Draw(CDC*pDC)
{
	if (m_nArmor <= 0)
		return;
	_int64 tmCurrent = GetTickCount64();
	_int64 tmGap = tmCurrent - m_InitalTime;
	switch (m_nDirection)
	{
	case 1:
		m_ptPos.y -= (long)m_nSpeed*tmGap/2.5;
		break;
	case 2:
		m_ptPos.y += (long)m_nSpeed * tmGap/2.5;
		break;
	case 3:
		m_ptPos.x -= (long)m_nSpeed * tmGap/2.5;
		break;
	case 4:
		m_ptPos.x += (long)m_nSpeed * tmGap/2.5;
		break;
	default:
		break;
	}
	if (m_ptPos.x <= -10 || m_ptPos.y <= -10 || m_ptPos.x >= 1290 || m_ptPos.y >= 900)
		m_nArmor = 0;
	pDC->Ellipse(m_ptPos.x + 32-m_nSize, m_ptPos.y + 32-m_nSize, m_ptPos.x + 32+m_nSize, m_ptPos.y + 32+m_nSize);
	m_InitalTime = tmCurrent;
}
void Shell::SetInitalTime()
{
	m_InitalTime = GetTickCount64();
}
_int64 Shell::GetInitalTime()
{
	return m_InitalTime;
}
