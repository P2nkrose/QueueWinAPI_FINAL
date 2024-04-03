#include "pch.h"
#include "qBlueDeadState.h"

#include "qSound.h"

qBlueDeadState::qBlueDeadState()
{
	
}

qBlueDeadState::~qBlueDeadState()
{
}

void qBlueDeadState::Enter()
{
	// 스킬 사운드
	pSound = qAssetMgr::GetInst()->LoadSound(L"BGM_START", L"sound\\monster\\die.wav");
	pSound->SetVolume(30.f);
	pSound->Play();

	init();

	if (DIRECTION::RIGHT == GetObj()->GetDir())
	{

		GetAnimator()->Play(L"BlueDeadRight", false);
	}
	else if (DIRECTION::LEFT == GetObj()->GetDir())
	{
		GetAnimator()->Play(L"BlueDeadLeft", false);
	}
}

void qBlueDeadState::FinalTick()
{


	if (L"BlueDeadLeft" == GetAnimator()->GetCurAnim()->GetName())
	{
		if (GetAnimator()->IsFinish())
		{
			GetObj()->Destroy();
		}
	}



	if (L"BlueDeadRight" == GetAnimator()->GetCurAnim()->GetName())
	{
		if (GetAnimator()->IsFinish())
		{
			GetObj()->Destroy();

		
		}
	}



	
}

void qBlueDeadState::Exit()
{
	pSound->SetVolume(30.f);
	pSound->Stop();
}
