#include "pch.h"
#include "qSkill_highjump.h"

#include "qAnimator.h"
#include "qCamera.h"

#include "qTaskMgr.h"


qSkill_highjump::qSkill_highjump()
	: m_Animator(nullptr)
{
	m_Animator = (qAnimator*)AddComponent(new qAnimator);

	// Animation 추가
	qTexture* HighJump = qAssetMgr::GetInst()->LoadTexture(L"HighJump", L"texture\\skill\\highjump\\highjump.png");

	// 애니메이션 CREATE
	m_Animator->CreateAnimation(L"HighJump", HighJump, Vec2(0.f, 0.f), Vec2(185.f, 255.f), 10, 13);

	// 애니메이션 SAVE
	m_Animator->FindAnimation(L"HighJump")->Save(L"animation\\skill\\highjump\\");

	// 애니메이션 LOAD
	m_Animator->LoadAnimation(L"animation\\skill\\highjump\\HighJump.anim");

	m_Animator->Play(L"HighJump", false);
}

qSkill_highjump::qSkill_highjump(const qSkill_highjump& _Other)
	: m_Animator(nullptr)
{
	m_Animator = GetComponent<qAnimator>();
}

qSkill_highjump::~qSkill_highjump()
{
}

void qSkill_highjump::tick()
{
	qObj::tick();

	if (L"HighJump" == m_Animator->GetCurAnim()->GetName())
	{
		if (m_Animator->IsFinish())
		{
			Destroy();
		}
	}
}
