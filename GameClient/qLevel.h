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
	
	// ���� �Լ�
	virtual void begin();		// ������ ���۵� ��
	virtual void tick();		// �� �����Ӹ��� ȣ��
	virtual void finaltick();	// �� �����Ӹ��� ȣ��
	virtual void render();		// �� �����Ӹ��� ȣ��


public:
	void AddObject(LAYER_TYPE _Layer, qObj* _Obj);
	void RegisterCollider(qCollider* _Collider);
	qObj* FindObjectByName(const wstring& _Name);
	qObj* FindObjectByName(LAYER_TYPE _Type, const wstring& _Name);

	const vector<qObj*>& GetObjects(LAYER_TYPE _Type) { return m_arrObj[(UINT)_Type]; }
	const vector<qCollider*>& GetColliders(LAYER_TYPE _Layer) { return m_arrCollider[(UINT)_Layer]; }

public:
	CLONE_DISABLE(qLevel);


public:
	qLevel();
	~qLevel();
};

