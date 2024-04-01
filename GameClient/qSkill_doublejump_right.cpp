#include "pch.h"
#include "qSkill_doublejump_right.h"

#include "qCollider.h"
#include "qAnimator.h"
#include "qCamera.h"

#include "qTaskMgr.h"


qSkill_doublejump_right::qSkill_doublejump_right()
	: m_Animator(nullptr)
{
	m_Animator = (qAnimator*)AddComponent(new qAnimator);

	// Animation 추가
	qTexture* DoubleJumpRight = qAssetMgr::GetInst()->LoadTexture(L"DoubleJumpRight", L"texture\\skill\\doublejump\\doublejump_right.png");

	// 애니메이션 CREATE
	m_Animator->CreateAnimation(L"DoubleJumpRight", DoubleJumpRight, Vec2(0.f, 0.f), Vec2(255.f, 185.f), 10, 13);

	// 애니메이션 SAVE
	m_Animator->FindAnimation(L"DoubleJumpRight")->Save(L"animation\\skill\\doublejump\\");

	// 애니메이션 LOAD
	m_Animator->LoadAnimation(L"animation\\skill\\doublejump\\DoubleJumpRight.anim");

	m_Animator->Play(L"DoubleJumpRight", false);



}

qSkill_doublejump_right::qSkill_doublejump_right(const qSkill_doublejump_right& _Other)
	: m_Animator(nullptr)
{
	m_Animator = GetComponent<qAnimator>();
}

qSkill_doublejump_right::~qSkill_doublejump_right()
{
}

void qSkill_doublejump_right::tick()
{
	qObj::tick();

	if (L"DoubleJumpRight" == m_Animator->GetCurAnim()->GetName())
	{
		if (m_Animator->IsFinish())
		{
			Destroy();
		}
	}
}
