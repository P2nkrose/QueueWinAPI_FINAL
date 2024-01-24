#pragma once
#include "qEntity.h"

class qObj : public qEntity
{
private:
	
	POINT		m_Pos;		// 위치
	POINT		m_Scale;	// 크기

public:
	void SetPos(POINT _Pos) { m_Pos = _Pos; }
	void SetScale(POINT _Scale) { m_Scale = _Scale; }

	POINT GetPos() { return m_Pos; }
	POINT GetScale() { return m_Scale; }

public:
	virtual void begin();		
	virtual void tick();		
	virtual void finaltick();	
	virtual void render();



public:
	qObj();
	~qObj();
};

