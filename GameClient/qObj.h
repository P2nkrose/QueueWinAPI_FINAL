#pragma once
#include "qEntity.h"

#include "qEngine.h"
#include "qTimeMgr.h"

class qObj : public qEntity
{
private:
	
	Vec2		m_Pos;		// ��ġ
	Vec2		m_Scale;	// ũ��

public:
	void SetPos(Vec2 _Pos) { m_Pos = _Pos; }
	void SetScale(Vec2 _Scale) { m_Scale = _Scale; }

	void SetPos(float _x, float _y) { m_Pos.x = _x; m_Pos.y = _y; }
	void SetScale(float _width, float _height) { m_Scale.x = _width; m_Scale.y = _height; }

	Vec2 GetPos() { return m_Pos; }
	Vec2 GetScale() { return m_Scale; }

public:
	virtual void begin();		
	virtual void tick();		// ������Ʈ�� �� �����Ӹ��� �ؾ��� �۾��� ����
	virtual void finaltick();	
	virtual void render();

public:
	virtual qObj* Clone() = 0;	// { return new qObj(*this); }


public:
	qObj();
	~qObj();
};

