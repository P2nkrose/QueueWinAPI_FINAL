#pragma once
#include "qEntity.h"

#include "qEngine.h"
#include "qTimeMgr.h"
#include "qKeyMgr.h"

#include "qAssetMgr.h"
#include "qTexture.h"

#include "qCamera.h"

class qComponent;
class qCollider;
class qAnimator;
class qRigidbody;
class qFSM;


class qObj : public qEntity
{
private:

	DIRECTION			m_Dir;		// ����
	
	Vec2				m_CenterPos;
	Vec2				m_Pos;		// ��ġ
	Vec2				m_PrevPos;	// ���� �����ӿ����� ��ġ
	Vec2				m_Scale;	// ũ��
	vector<qComponent*>	m_vecCom;	// ���� ������Ʈ��

	qAnimator*			m_Animator;

	LAYER_TYPE			m_Type;		// �Ҽ� ���̾�
	bool				m_bDead;	// ���� ���� ����
	

public:
	void SetDir(DIRECTION _Dir) { m_Dir = _Dir; }
	DIRECTION GetDir() { return m_Dir; }

	void SetPos(Vec2 _Pos) { m_Pos = _Pos; }
	void SetScale(Vec2 _Scale) { m_Scale = _Scale; }

	void SetPos(float _x, float _y) { m_Pos.x = _x; m_Pos.y = _y; }
	void SetScale(float _width, float _height) { m_Scale.x = _width; m_Scale.y = _height; }
	void SetCenterPos(Vec2 _CenterPos) { m_CenterPos = _CenterPos; }


	Vec2 GetCenterPos() { return m_CenterPos; }
	Vec2 GetPos() { return m_Pos; }
	Vec2 GetPrevPos() { return m_PrevPos; }
	Vec2 GetRenderPos() { return qCamera::GetInst()->GetRenderPos(m_Pos); }
	Vec2 GetScale() { return m_Scale; }

	LAYER_TYPE GetLayerType() { return m_Type; }
	void SetLayerType(LAYER_TYPE _Type) { m_Type = _Type; }

	bool IsDead() { return m_bDead; }

	void Destroy();

	qComponent* AddComponent(qComponent* _Component);

	template<typename T>
	T* GetComponent()
	{
		for (size_t i = 0; i < m_vecCom.size(); ++i)
		{
			T* pComponent = dynamic_cast<T*>(m_vecCom[i]);

			if (pComponent)
			{
				return pComponent;
			}
		}

		return nullptr;
	}

public:
	virtual void begin();		
	virtual void tick();		// ������Ʈ�� �� �����Ӹ��� �ؾ��� �۾��� ����
	virtual void finaltick() final;	// ������Ʈ�� ������ ������Ʈ���� �� �����Ӹ��� �ؾ��� �۾��� ����
	virtual void render();


	virtual void BeginOverlap(qCollider* _OwnCollider, qObj* _OtherObj, qCollider* _OtherCollider){}	// �� �浹���� ��
	virtual void OnOverlap(qCollider* _OwnCollider, qObj* _OtherObj, qCollider* _OtherCollider){}		// �浹���� ��
	virtual void EndOverlap(qCollider* _OwnCollider, qObj* _OtherObj, qCollider* _OtherCollider){}		// �浹�� ������ ��



public:
	virtual qObj* Clone() = 0;	// { return new qObj(*this); }


public:
	qObj();
	qObj(const qObj& _Other);
	~qObj();

	friend class qLevel;
	friend class qTaskMgr;
};

