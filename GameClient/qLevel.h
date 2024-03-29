#pragma once
#include "qEntity.h"

class qObj;
class qCollider;
class qPlatform;

class qLevel : public qEntity
{

public:
	friend class qUIMgr;

	CLONE_DISABLE(qLevel);


public:
	qLevel();
	~qLevel();

public:
	// ���� �Լ�
	virtual void begin();			// ������ ���۵� ��
	virtual void tick();			// �� �����Ӹ��� ȣ��
	virtual void finaltick();		// �� �����Ӹ��� ȣ��
	virtual void render();			// �� �����Ӹ��� ȣ��

	virtual void Enter() PURE;		// ������ ��ȯ�ǰ� ó�� �ʱ�ȭ �۾�
	virtual void Exit() PURE;		// ������ ������ �� ��


public:
	void AddObject(LAYER_TYPE _Layer, qObj* _Obj);
	void RegisterCollider(qCollider* _Collider);
	qObj* FindObjectByName(const wstring& _Name);
	qObj* FindObjectByName(LAYER_TYPE _Type, const wstring& _Name);

	const vector<qObj*>& GetObjects(LAYER_TYPE _Type) { return m_arrObj[(UINT)_Type]; }
	const vector<qCollider*>& GetColliders(LAYER_TYPE _Layer) { return m_arrCollider[(UINT)_Layer]; }

	void SetStageName(STAGE_NAME _name) { m_stageName = _name; }

	void SetPos(Vec2 _Pos) { m_Pos = _Pos; }
	Vec2 GetPos() { return m_Pos; }


protected:
	void DeleteAllObjects();
	void DeleteObjects(LAYER_TYPE _LayerType);


protected:
	void SavePlatform(const wstring& _strRelativePath);
	void SaveMonster(const wstring& _strRelativePath);


	void LoadPlatform(const wstring& _strRelativePath);
	void LoadMonster(const wstring& _strRelativePath);

private:
	vector<qObj*>		m_arrObj[(UINT)LAYER_TYPE::END];
	vector<qCollider*>	m_arrCollider[(UINT)LAYER_TYPE::END];
	STAGE_NAME			m_stageName;

	Vec2				m_Pos;
};

