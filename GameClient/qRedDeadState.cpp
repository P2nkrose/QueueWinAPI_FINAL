#include "pch.h"
#include "qRedDeadState.h"

#include "qSound.h"

qRedDeadState::qRedDeadState()
{
}

qRedDeadState::~qRedDeadState()
{
}

void qRedDeadState::Enter()
{
	// 스킬 사운드
	pSound = qAssetMgr::GetInst()->LoadSound(L"BGM_START", L"sound\\monster\\die.wav");
	pSound->SetVolume(30.f);
	pSound->Play();

	init();

	if (DIRECTION::RIGHT == GetObj()->GetDir())
	{
		GetAnimator()->Play(L"RedDeadRight", false);
	}
	else if (DIRECTION::LEFT == GetObj()->GetDir())
	{
		GetAnimator()->Play(L"RedDeadLeft", false);
	}
}

void qRedDeadState::FinalTick()
{
	if (L"RedDeadLeft" == GetAnimator()->GetCurAnim()->GetName())
	{
		if (GetAnimator()->IsFinish())
		{
			GetObj()->Destroy();
		}
	}



	if (L"RedDeadRight" == GetAnimator()->GetCurAnim()->GetName())
	{
		if (GetAnimator()->IsFinish())
		{
			GetObj()->Destroy();
		}
	}
}

void qRedDeadState::Exit()
{
	pSound->SetVolume(30.f);
	pSound->Stop();
}
