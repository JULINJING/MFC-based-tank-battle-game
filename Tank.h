#pragma once
#include "MyObject.h"
class Tank : public MyObject
{
public:
	Tank() ;
	~Tank() {};

	void Draw(CDC* pDC) ;//函数声明在cpp中定义此处不带花括号
	void Move(int nDirection);
	Shell Fire();
	bool IsEnableMove(int nDirection);

public:
	static CImage m_img[4];

};

