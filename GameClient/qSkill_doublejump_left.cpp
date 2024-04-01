#include "pch.h"
#include "qSkill_doublejump_left.h"

#include "qCollider.h"
#include "qAnimator.h"
#include "qCamera.h"

#include "qTaskMgr.h"


qSkill_doublejump_left::qSkill_doublejump_left()
	: m_Animator(nullptr)
{
	m_Animator = (qAnimator*)AddComponent(new qAnimator);

	// Animation 추가
	qTexture* DoubleJumpLeft = qAssetMgr::GetInst()->LoadTexture(L"DoubleJumpLeft", L"texture\\skill\\doublejump\\doublejump_left.png");

	// 애니메이션 CREATE
	m_Animator->CreateAnimation(L"DoubleJumpLeft", DoubleJumpLeft, Vec2(0.f, 0.f), Vec2(255.f, 185.f), 10, 13);

	// 애니메이션 SAVE
	m_Animator->FindAnimation(L"DoubleJumpLeft")->Save(L"animation\\skill\\doublejump\\");

	// 애니메이션 LOAD
	m_Animator->LoadAnimation(L"animation\\skill\\doublejump\\DoubleJumpLeft.anim");

	m_Animator->Play(L"DoubleJumpLeft", false);


}

qSkill_doublejump_left::qSkill_doublejump_left(const qSkill_doublejump_left& _Other)
	: m_Animator(nullptr)
{
	m_Animator = GetComponent<qAnimator>();
}

qSkill_doublejump_left::~qSkill_doublejump_left()
{
}

void qSkill_doublejump_left::tick()
{
	qObj::tick();

	if (L"DoubleJumpLeft" == m_Animator->GetCurAnim()->GetName())
	{
		if (m_Animator->IsFinish())
		{
			Destroy();
		}
	}
}
