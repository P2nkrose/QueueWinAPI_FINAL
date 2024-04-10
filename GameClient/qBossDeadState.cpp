#include "pch.h"
#include "qBossDeadState.h"

#include "qSound.h"

qBossDeadState::qBossDeadState()
	: m_Time(0.f)
	, m_Dir(-1.f)
{
}

qBossDeadState::~qBossDeadState()
{
}

void qBossDeadState::Enter()
{
	init();

	m_CenterPos = GetObj()->GetCenterPos();

	if (DIRECTION::LEFT == GetObj()->GetDir())
	{
		m_Dir = -1.f;
	}
	else if (DIRECTION::RIGHT == GetObj()->GetDir())
	{
		m_Dir = 1.f;
	}

	if (m_Dir == 1.f)
	{
		GetAnimator()->Play(L"BossDeadRight", false);

		// 스킬 사운드
		pSound = qAssetMgr::GetInst()->LoadSound(L"BGM_START", L"sound\\boss\\dead.wav");
		pSound->SetVolume(30.f);
		pSound->Play();
	}
	else if (m_Dir == -1.f)
	{
		GetAnimator()->Play(L"BossDeadLeft", false);

		// 스킬 사운드
		pSound = qAssetMgr::GetInst()->LoadSound(L"BGM_START", L"sound\\boss\\dead.wav");
		pSound->SetVolume(30.f);
		pSound->Play();
	}
}

void qBossDeadState::FinalTick()
{
	qObj* pBoss = GetBlackboardData<qObj*>(L"Boss");

	if (L"BossDeadRight" == GetAnimator()->GetCurAnim()->GetName())
	{
		if (GetAnimator()->IsFinish())
		{
			GetObj()->Destroy();
		}
	}

	if (L"BossDeadLeft" == GetAnimator()->GetCurAnim()->GetName())
	{
		if (GetAnimator()->IsFinish())
		{
			GetObj()->Destroy();
		}
	}
}

void qBossDeadState::Exit()
{
}
