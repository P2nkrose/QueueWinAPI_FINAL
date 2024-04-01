#include "pch.h"
#include "qSkill_buff.h"

#include "qAnimator.h"
#include "qCamera.h"

#include "qTaskMgr.h"


qSkill_buff::qSkill_buff()
	: m_Animator(nullptr)
{
	m_Animator = (qAnimator*)AddComponent(new qAnimator);

	// Animation 추가
	qTexture* Buff = qAssetMgr::GetInst()->LoadTexture(L"Buff", L"texture\\skill\\buff\\buff.png");

	// 애니메이션 CREATE
	m_Animator->CreateAnimation(L"Buff", Buff, Vec2(0.f, 0.f), Vec2(400.f, 400.f), 17, 5);

	// 애니메이션 SAVE
	m_Animator->FindAnimation(L"Buff")->Save(L"animation\\skill\\buff\\");

	// 애니메이션 LOAD
	m_Animator->LoadAnimation(L"animation\\skill\\buff\\Buff.anim");

	m_Animator->Play(L"Buff", false);
}

qSkill_buff::qSkill_buff(const qSkill_buff& _Other)
	: m_Animator(nullptr)
{
	m_Animator = GetComponent<qAnimator>();
}

qSkill_buff::~qSkill_buff()
{
}

void qSkill_buff::tick()
{
	qObj::tick();

	if (L"Buff" == m_Animator->GetCurAnim()->GetName())
	{
		if (m_Animator->IsFinish())
		{
			Destroy();
		}
	}
}
