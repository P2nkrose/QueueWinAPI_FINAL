#pragma once
#include "qEntity.h"

class qObj;
class qCollider;

class qLevel : public qEntity
{
private:

	vector<qObj*>		m_arrObj[(UINT)LAYER_TYPE::END];
	vector<qCollider*>	m_arrCollider[(UINT)LAYER_TYPE::END];

public:

	// 시점 함수
	virtual void begin();		// 레벨이 시작될 때
	virtual void tick();		// 매 프레임마다 호출
	virtual void finaltick();	// 매 프레임마다 호출
	virtual void render();		// 매 프레임마다 호출


public:
	void AddObject(LAYER_TYPE _Layer, qObj* _Obj);
	void RegisterCollider(qCollider* _Collider);

	const vector<qCollider*>& GetColliders(LAYER_TYPE _Layer)
	{
		return m_arrCollider[(UINT)_Layer];
	}

public:
	virtual qLevel* Clone() = 0;


public:
	qLevel();
	~qLevel();
};

