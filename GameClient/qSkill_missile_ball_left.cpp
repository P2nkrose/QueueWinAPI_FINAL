#include "pch.h"
#include "qSkill_missile_ball_left.h"

#include "qCollider.h"
#include "qAnimator.h"
#include "qCamera.h"

#include "qLevel.h"
#include "qLevelMgr.h"

#include "qEffect_missile.h"
#include "qDamage_missile.h"

#include "qTaskMgr.h"

qSkill_missile_ball_left::qSkill_missile_ball_left()
	: m_Animator(nullptr)
	, m_BallSpeed(600.f)
{
	m_Animator = (qAnimator*)AddComponent(new qAnimator);

	// Animation 추가
	qTexture* MissileBallLeft = qAssetMgr::GetInst()->LoadTexture(L"MissileBallLeft", L"texture\\skill\\missile\\missile_ball_left.png");

	// 애니메이션 CREATE
	m_Animator->CreateAnimation(L"MissileBallLeft", MissileBallLeft, Vec2(0.f, 0.f), Vec2(100.f, 70.f), 4, 5);

	// 애니메이션 SAVE
	m_Animator->FindAnimation(L"MissileBallLeft")->Save(L"animation\\skill\\missile\\");

	// 애니메이션 LOAD
	m_Animator->LoadAnimation(L"animation\\skill\\missile\\MissileBallLeft.anim");

	m_Animator->Play(L"MissileBallLeft", true);


	// 콜라이더

	m_Collider = (qCollider*)AddComponent(new qCollider);

	m_Collider->SetOffsetPos(Vec2(0.f, 0.f));
	m_Collider->SetScale(Vec2(60.f, 30.f));
}

qSkill_missile_ball_left::qSkill_missile_ball_left(const qSkill_missile_ball_left& _Other)
	: m_Animator(nullptr)
	, m_BallSpeed(600.f)
{
	m_Animator = GetComponent<qAnimator>();
}

qSkill_missile_ball_left::~qSkill_missile_ball_left()
{
}

void qSkill_missile_ball_left::tick()
{
	qObj::tick();

	Vec2 vPos = GetPos();
	Vec2 vDir = Vec2(-1.f, 0.f);

	vPos += vDir * m_BallSpeed * DT;

	SetPos(vPos);
}


void qSkill_missile_ball_left::BeginOverlap(qCollider* _OwnCollider, qObj* _OtherObj, qCollider* _OtherCollider)
{
	if (LAYER_TYPE::MONSTER_BLUE == _OtherObj->GetLayerType() || LAYER_TYPE::BOSS == _OtherObj->GetLayerType()
		|| LAYER_TYPE::MONSTER_RED == _OtherObj->GetLayerType())
	{
		qEffect_missile* pMissileEffect = new qEffect_missile;
		pMissileEffect->SetName(L"MissileEffect");

		Vec2 vMissileEffectPos = _OtherObj->GetPos() + Vec2(30.f, 0.f);
		Vec2 vMissileEffectScale = Vec2(150.f, 130.f);

		pMissileEffect->SetPos(vMissileEffectPos);
		pMissileEffect->SetScale(vMissileEffectScale);

		if (L"MissileEffect" == pMissileEffect->GetName())
		{
			// TASK
			SpawnObject(qLevelMgr::GetInst()->GetCurrentLevel(), LAYER_TYPE::EFFECT, pMissileEffect);
		}
	}

	if (LAYER_TYPE::MONSTER_BLUE == _OtherObj->GetLayerType() || LAYER_TYPE::BOSS == _OtherObj->GetLayerType()
		|| LAYER_TYPE::MONSTER_RED == _OtherObj->GetLayerType())
	{
		qDamage_missile* pDamageMissile = new qDamage_missile;
		pDamageMissile->SetName(L"DamageMissile");

		Vec2 vDamageMissilePos = _OtherObj->GetPos() + Vec2(0.f, -90.f);
		Vec2 vDamageMissileScale = Vec2(258.f, 112.f);

		pDamageMissile->SetPos(vDamageMissilePos);
		pDamageMissile->SetScale(vDamageMissileScale);

		if (L"DamageMissile" == pDamageMissile->GetName())
		{
			// TASK
			SpawnObject(qLevelMgr::GetInst()->GetCurrentLevel(), LAYER_TYPE::EFFECT, pDamageMissile);
		}
	}



	// 적과 부딪혔을때 Destroy();
	if (_OtherObj->GetName() == L"Blue" || _OtherObj->GetName() == L"Red" || _OtherObj->GetName() == L"Boss")
	{
		Destroy();
	}




}
