#pragma once
#include "MyObject.h"
class Wall : public MyObject
{
public:
	Wall() ;
	~Wall() {};

	void Draw(int nflag,CDC* pDC);
	void SetPosition(int x, int y);
public:
	static CImage m_Img;
	int m_flag;
};