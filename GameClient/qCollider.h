#pragma once
#include "qComponent.h"

class qCollider : public qComponent
{
public:

	CLONE(qCollider);

	friend class qCollisionMgr;

	qCollider();
	~qCollider();


public:
	virtual void finaltick() override;
	

public:
	void SetOffsetPos(Vec2 _Offset) { m_OffsetPos = _Offset; }
	void SetScale(Vec2 _Scale) { m_Scale = _Scale; }

	Vec2 GetFinalPos() { return m_FinalPos; }
	Vec2 GetScale() { return m_Scale; }

	void SetActive(bool _Set) 
	{ 
		m_Active = _Set; 

		if (m_Active)
		{
			m_bRegister = true;
		}
	}

	bool IsActive() { return m_Active; }


private:

	void BeginOverlap(qCollider* _OtherCollider);
	void OnOverlap(qCollider* _OtherCollider);
	void EndOverlap(qCollider* _OtherCollider);


private:
	Vec2	m_OffsetPos;		// 소유 오브젝트로부터 상대적인 좌표
	Vec2	m_Scale;

	Vec2	m_FinalPos;			// 최종 좌표 (소유 오브젝트 포지션 + 오프셋 포즈)
	
	
	UINT	m_CollisionCount;	// 카운트를 활용하여 충돌상태를 체크한다.

	bool	m_Active;			// 충돌체 활성화, 비활성화 상태 bool
	bool	m_bRegister;		// 충돌체를 레벨에 등록할지 말지의 상태
};

