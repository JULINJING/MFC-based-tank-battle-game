#pragma once
class MyObject
{
public:
	MyObject() { m_nSize = 32; };
	~MyObject() {};

	void Draw(CDC* pDC);
	void Move(int nDirection) {};//设置运动方向or方向
	bool IsOverlap(MyObject& obj);//判断两个物体是否碰撞
	bool IsFriend(MyObject& OBJ);
	void SetSize(int nSize);//设置外形尺寸
	void SetDirection(int nDir);
	void SetFriend(bool bFriend);
	void SetArmor(int nArmor);
	void SetSpeed(int nSpeed);
	int GetDirection();//访问m_nDirection
	int GetSize();//访问m_nSize
	bool GetFriend();
	int GetArmor();
	int GetSpeed();
	template<class T1, class T2>
	bool IsOverLapRect_(T1& a, T2& obj)
	{
		if ((fabs(a.m_ptPos.x - obj.m_ptPos.x) <= 2*a.m_nSize)&& (fabs(a.m_ptPos.y - obj.m_ptPos.y) <= 2 * a.m_nSize))
			return true;
		else 
			return false;
	};


public:
	int m_nSpeed;//<=0 stop
	int m_nArmor;//==0 destroy 0< disable
	CPoint m_ptPos;//当前坐标
protected:
	bool m_bFriend;
	int m_nSize;//外形范围
	int m_nDirection;//1234 上下左右 方向
};