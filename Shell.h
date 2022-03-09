#pragma once
#include "MyObject.h"
class Shell : public MyObject//( : )
{
public:
	Shell();
    ~Shell() {};

	void Draw(CDC* pDC);
	void Move(int nDirection) {};
	void SetInitalTime();
	_int64 GetInitalTime();

public:
	_int64 m_InitalTime;
};

