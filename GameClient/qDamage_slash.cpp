#include "pch.h"
#include "qDamage_slash.h"

#include "qAnimator.h"
#include "qTaskMgr.h"

qDamage_slash::qDamage_slash()
	: m_Animator(nullptr)
{
	m_Animator = (qAnimator*)AddComponent(new qAnimator);

	// Animation Ãß°¡
	qTexture* DamageSlash = qAssetMgr::GetInst()->LoadTexture(L"DamageSlash", L"texture\\damage\\slash\\slash.png");

	// Animation CREATE
	m_Animator->CreateAnimation(L"DamageSlash", DamageSlash, Vec2(0.f, 0.f), Vec2(258.f, 112.f), 11, 10);

	// Animation Save
	m_Animator->FindAnimation(L"DamageSlash")->Save(L"animation\\damage\\slash\\");

	// Animation Load
	m_Animator->LoadAnimation(L"animation\\damage\\slash\\DamageSlash.anim");

	m_Animator->Play(L"DamageSlash", false);
}

qDamage_slash::qDamage_slash(const qDamage_slash& _Other)
	: m_Animator(nullptr)
{
	m_Animator = GetComponent<qAnimator>();
}

qDamage_slash::~qDamage_slash()
{
}

void qDamage_slash::tick()
{
	qObj::tick();

	if (L"DamageSlash" == m_Animator->GetCurAnim()->GetName())
	{
		if (m_Animator->IsFinish())
		{
			Destroy();

		}
	}
}
