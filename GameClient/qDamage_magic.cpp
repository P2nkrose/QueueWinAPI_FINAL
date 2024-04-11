#include "pch.h"
#include "qDamage_magic.h"

#include "qAnimator.h"
#include "qTaskMgr.h"

qDamage_magic::qDamage_magic()
{
	m_Animator = (qAnimator*)AddComponent(new qAnimator);

	// Animation Ãß°¡
	qTexture* DamageMagic = qAssetMgr::GetInst()->LoadTexture(L"DamageMagic", L"texture\\boss_damage\\magic\\magic.png");

	// Animation CREATE
	m_Animator->CreateAnimation(L"DamageMagic", DamageMagic, Vec2(0.f, 0.f), Vec2(181.f, 58.f), 11, 10);

	// Animation Save
	m_Animator->FindAnimation(L"DamageMagic")->Save(L"animation\\boss_damage\\magic\\");

	// Animation Load
	m_Animator->LoadAnimation(L"animation\\boss_damage\\magic\\DamageMagic.anim");

	m_Animator->Play(L"DamageMagic", false);
}

qDamage_magic::~qDamage_magic()
{
}

void qDamage_magic::tick()
{
	qObj::tick();

	if (L"DamageMagic" == m_Animator->GetCurAnim()->GetName())
	{
		if (m_Animator->IsFinish())
		{
			Destroy();

		}
	}
}
