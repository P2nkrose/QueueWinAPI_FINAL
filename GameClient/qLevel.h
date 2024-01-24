#pragma once
#include "qEntity.h"

class qObj;

class qLevel : public qEntity
{
private:

	vector<qObj*>		m_vecObj;

public:

	// 시점 함수
	void begin();		// 레벨이 시작될 때

	void tick();		// 매 프레임마다 호출
	void finaltick();	// 매 프레임마다 호출
	void render();		// 매 프레임마다 호출


public:
	void AddObject(qObj* _Obj) { m_vecObj.push_back(_Obj); }


public:
	qLevel();
	~qLevel();
};

