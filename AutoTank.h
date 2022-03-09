#pragma once
#include "MyObject.h"
class AutoTank : public MyObject
{
public:
	AutoTank();
	~AutoTank() {};

	void Draw(CDC* pDC);
	Shell AutoFire();
	void SetInitalTime();
	void ChangeDirection(MyObject& playerTank);
	void Move(int nDirection);
public:
	static CImage m_Img[4];
	_int64 m_InitalTime;
	int m_nTrueSpeed;
	CPoint pre_pt;
	double m_dDis;
};