#pragma once
#include "qEntity.h"

#include "qEngine.h"
#include "qTimeMgr.h"
#include "qKeyMgr.h"

#include "qAssetMgr.h"
#include "qTexture.h"

class qComponent;
class qCollider;
class qAnimator;
class qRigidbody;
class qFSM;


class qObj : public qEntity
{
private:
	
	Vec2				m_Pos;		// 위치
	Vec2				m_Scale;	// 크기
	vector<qComponent*>	m_vecCom;	// 보유 컴포넌트들

	qAnimator*			m_Animator;


	LAYER_TYPE			m_Type;		// 소속 레이어
	bool				m_bDead;	// 삭제 예정 상태
	

public:
	void SetPos(Vec2 _Pos) { m_Pos = _Pos; }
	void SetScale(Vec2 _Scale) { m_Scale = _Scale; }

	void SetPos(float _x, float _y) { m_Pos.x = _x; m_Pos.y = _y; }
	void SetScale(float _width, float _height) { m_Scale.x = _width; m_Scale.y = _height; }

	Vec2 GetPos() { return m_Pos; }
	Vec2 GetScale() { return m_Scale; }
	LAYER_TYPE GetLayerType() { return m_Type; }
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
	virtual void tick();		// 오브젝트가 매 프레임마다 해야할 작업을 구현
	virtual void finaltick() final;	// 오브젝트가 소유한 컴포넌트들이 매 프레임마다 해야할 작업을 구현
	virtual void render();


	virtual void BeginOverlap(qCollider* _OwnCollider, qObj* _OtherObj, qCollider* _OtherCollider){}	// 막 충돌했을 때
	virtual void OnOverlap(qCollider* _OwnCollider, qObj* _OtherObj, qCollider* _OtherCollider){}		// 충돌중일 때
	virtual void EndOverlap(qCollider* _OwnCollider, qObj* _OtherObj, qCollider* _OtherCollider){}		// 충돌이 끝났을 때



public:
	virtual qObj* Clone() = 0;	// { return new qObj(*this); }


public:
	qObj();
	~qObj();

	friend class qLevel;
	friend class qTaskMgr;
};

