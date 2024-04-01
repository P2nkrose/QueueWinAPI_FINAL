#include "pch.h"
#include "qSkill_missile_left.h"

#include "qAnimator.h"
#include "qCamera.h"
#include "qSound.h"

#include "qTaskMgr.h"

qSkill_missile_left::qSkill_missile_left()
	: m_Animator(nullptr)
{
	m_Animator = (qAnimator*)AddComponent(new qAnimator);

	// Animation 추가
	qTexture* MissileLeft = qAssetMgr::GetInst()->LoadTexture(L"MissileLeft", L"texture\\skill\\missile\\missile_left.png");

	// 애니메이션 CREATE
	m_Animator->CreateAnimation(L"MissileLeft", MissileLeft, Vec2(0.f, 0.f), Vec2(240.f, 195.f), 11, 13);

	// 애니메이션 SAVE
	m_Animator->FindAnimation(L"MissileLeft")->Save(L"animation\\skill\\missile\\");

	// 애니메이션 LOAD
	m_Animator->LoadAnimation(L"animation\\skill\\missile\\MissileLeft.anim");

	m_Animator->Play(L"MissileLeft", false);



	// 스킬 사운드
	pSound = qAssetMgr::GetInst()->LoadSound(L"BGM_START", L"sound\\skill\\missile.wav");
	pSound->SetVolume(30.f);
	pSound->Play();
}

qSkill_missile_left::qSkill_missile_left(const qSkill_missile_left& _Other)
	: m_Animator(nullptr)
{
	m_Animator = GetComponent<qAnimator>();
}

qSkill_missile_left::~qSkill_missile_left()
{
}

void qSkill_missile_left::tick()
{
	qObj::tick();

	if (L"MissileLeft" == m_Animator->GetCurAnim()->GetName())
	{
		if (m_Animator->IsFinish())
		{
			Destroy();

			pSound->SetVolume(30.f);
			pSound->Stop();
		}
	}
}
