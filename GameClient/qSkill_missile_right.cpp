#include "pch.h"
#include "qSkill_missile_right.h"

#include "qAnimator.h"
#include "qCamera.h"

#include "qTaskMgr.h"

qSkill_missile_right::qSkill_missile_right()
	: m_Animator(nullptr)
{
	m_Animator = (qAnimator*)AddComponent(new qAnimator);

	// Animation 추가
	qTexture* MissileRight = qAssetMgr::GetInst()->LoadTexture(L"MissileRight", L"texture\\skill\\missile\\missile_right.png");

	// 애니메이션 CREATE
	m_Animator->CreateAnimation(L"MissileRight", MissileRight, Vec2(0.f, 0.f), Vec2(240.f, 195.f), 11, 5);

	// 애니메이션 SAVE
	m_Animator->FindAnimation(L"MissileRight")->Save(L"animation\\skill\\missile\\");

	// 애니메이션 LOAD
	m_Animator->LoadAnimation(L"animation\\skill\\missile\\MissileRight.anim");

	m_Animator->Play(L"MissileRight", false);
}

qSkill_missile_right::qSkill_missile_right(const qSkill_missile_right& _Other)
	: m_Animator(nullptr)
{
	m_Animator = GetComponent<qAnimator>();
}

qSkill_missile_right::~qSkill_missile_right()
{
}

void qSkill_missile_right::tick()
{
	qObj::tick();

	if (L"MissileRight" == m_Animator->GetCurAnim()->GetName())
	{
		if (m_Animator->IsFinish())
		{
			Destroy();
		}
	}
}
