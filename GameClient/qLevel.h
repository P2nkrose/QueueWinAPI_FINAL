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
	virtual void begin();			// 레벨이 시작될 때
	virtual void tick();			// 매 프레임마다 호출
	virtual void finaltick();		// 매 프레임마다 호출
	virtual void render();			// 매 프레임마다 호출

	virtual void Enter() PURE;		// 레벨이 전환되고 처음 초기화 작업
	virtual void Exit() PURE;		// 레벨이 끝날때 할 일


public:
	void AddObject(LAYER_TYPE _Layer, qObj* _Obj);
	void RegisterCollider(qCollider* _Collider);
	qObj* FindObjectByName(const wstring& _Name);
	qObj* FindObjectByName(LAYER_TYPE _Type, const wstring& _Name);

	const vector<qObj*>& GetObjects(LAYER_TYPE _Type) { return m_arrObj[(UINT)_Type]; }
	const vector<qCollider*>& GetColliders(LAYER_TYPE _Layer) { return m_arrCollider[(UINT)_Layer]; }


protected:
	void DeleteAllObjects();
	void DeleteObjects(LAYER_TYPE _LayerType);


public:
	CLONE_DISABLE(qLevel);


public:
	qLevel();
	~qLevel();
};

