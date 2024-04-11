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

	DIRECTION			m_Dir;		// 방향
	
	qObj*				m_Owner;

	Vec2				m_CenterPos;
	Vec2				m_Pos;		// 위치
	Vec2				m_PrevPos;	// 이전 프레임에서의 위치
	Vec2				m_Scale;	// 크기
	vector<qComponent*>	m_vecCom;	// 보유 컴포넌트들

	qAnimator*			m_Animator;

	int					m_AttackDamage;
	int					m_MissileDamage;
	int					m_SlashDamage;
	int					m_SpecialDamage;

	int					m_AttackCount;
	int					m_MissileCount;
	int					m_SlashCount;
	int					m_SpecialCount;


	int					m_PhysicalDamage;
	int					m_MagicDamage;

	int					m_PhysicalCount;
	int					m_MagicCount;

	int					m_BossHP;
	int					m_PlayerHP;

	int					m_Exp;

	LAYER_TYPE			m_Type;		// 소속 레이어
	bool				m_bDead;	// 삭제 예정 상태
	

public:

	int GetAttackCount() { return m_AttackCount; }
	void PlusAttackCount() { m_AttackCount += 1; }

	int GetMissileCount() { return m_MissileCount; }
	void PlusMissileCount() { m_MissileCount += 1; }

	int GetSlashCount() { return m_SlashCount; }
	void PlusSlashCount() { m_SlashCount += 1; }

	int GetSpecialCount() { return m_SpecialCount; }
	void PlusSpecialCount() { m_SpecialCount += 1; }

	int GetPhysicalCount() { return m_PhysicalCount; }
	void PlusPhysicalCount() { m_PhysicalCount += 1; }

	int GetMagicCount() { return m_MagicCount; }
	void PlusMagicCount() { m_MagicCount += 1; }


	int GetExp() { return m_Exp; }
	void PlusExp() { m_Exp += 40; }

	int GetBossHP() { return m_BossHP; }
	void SetBossHP(int _hp) { m_BossHP = _hp; }

	int GetPlayerHP() { return m_PlayerHP; }
	void SetPlayerHP(int _hp) { m_PlayerHP = _hp; }


	int GetAttackDamage() { return m_AttackDamage; }
	int GetMissileDamage() { return m_MissileDamage; }
	int GetSlashDamage() { return m_SlashDamage; }
	int GetSpecialDamage() { return m_SpecialDamage; }

	int GetPhysicalDamage() { return m_PhysicalDamage; }
	int GetMagicDamage() { return m_MagicDamage; }


	void SetDir(DIRECTION _Dir) { m_Dir = _Dir; }
	DIRECTION GetDir() { return m_Dir; }

	void SetPos(Vec2 _Pos) { m_Pos = _Pos; }
	void SetScale(Vec2 _Scale) { m_Scale = _Scale; }

	void SetPos(float _x, float _y) { m_Pos.x = _x; m_Pos.y = _y; }
	void SetScale(float _width, float _height) { m_Scale.x = _width; m_Scale.y = _height; }
	void SetCenterPos(Vec2 _CenterPos) { m_CenterPos = _CenterPos; }


	void SetOwner(qObj* _Owner) { m_Owner = _Owner; }
	qObj* GetOwner() { return m_Owner; }

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
	qObj(const qObj& _Other);
	~qObj();

	friend class qLevel;
	friend class qTaskMgr;
};

