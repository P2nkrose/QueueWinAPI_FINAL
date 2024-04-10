#include "pch.h"
#include "qBossBallState.h"

#include "qAnimator.h"
#include "qSound.h"

#include "qBossSkill_ball_left.h"
#include "qBossSkill_ball_right.h"
#include "qLevel.h"
#include "qLevelMgr.h"

#include "qTaskMgr.h"


qBossBallState::qBossBallState()
	: m_Time(0.f)
	, m_Dir(-1.f)
	, m_OneShot(true)
{
}

qBossBallState::~qBossBallState()
{
}

void qBossBallState::Enter()
{
	init();

	//qObj* pBossBallLeft = GetBlackboardData<qObj*>(L"BossBallLeft");

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
		GetAnimator()->Play(L"BossBallRight", false);

		// 스킬 사운드
		pSound = qAssetMgr::GetInst()->LoadSound(L"BGM_START", L"sound\\boss\\ball.wav");
		pSound->SetVolume(30.f);
		pSound->Play();
	}
	else if (m_Dir == -1.f)
	{
		GetAnimator()->Play(L"BossBallLeft", false);

		// 스킬 사운드
		pSound = qAssetMgr::GetInst()->LoadSound(L"BGM_START", L"sound\\boss\\ball.wav");
		pSound->SetVolume(30.f);
		pSound->Play();

	}
}

void qBossBallState::FinalTick()
{
	qObj* pBoss = GetBlackboardData<qObj*>(L"Boss");


	if (L"BossBallRight" == GetAnimator()->GetCurAnim()->GetName())
	{
		if (GetAnimator()->GetCurAnim()->GetCurFrmIdx() == 9)
		{
			if (m_OneShot == true)
			{
				// 다크니스 볼 발사
				qBossSkill_ball_right* pBossSkillBallRight = new qBossSkill_ball_right;
				pBossSkillBallRight->SetName(L"BossSkillBallRight");

				Vec2 vBossSkillBallRightPos = GetObj()->GetPos() + Vec2(70.f, 33.f);
				Vec2 vBossSkillBallRightScale = Vec2(120.f, 60.f);

				pBossSkillBallRight->SetPos(vBossSkillBallRightPos);
				pBossSkillBallRight->SetScale(vBossSkillBallRightScale);

				if (L"BossSkillBallRight" == pBossSkillBallRight->GetName())
				{
					SpawnObject(qLevelMgr::GetInst()->GetCurrentLevel(), LAYER_TYPE::BOSS_SKILL, pBossSkillBallRight);
				}

				m_OneShot = false;
			}
		}

		if (GetAnimator()->IsFinish())
		{
			GetFSM()->ChangeState(L"Idle");
		}
	}

	if (L"BossBallLeft" == GetAnimator()->GetCurAnim()->GetName())
	{
		if (GetAnimator()->GetCurAnim()->GetCurFrmIdx() == 9)
		{
			if (m_OneShot == true)
			{
				// 다크니스 볼 발사
				qBossSkill_ball_left* pBossSkillBallLeft = new qBossSkill_ball_left;
				pBossSkillBallLeft->SetName(L"BossSkillBallLeft");

				Vec2 vBossSkillBallLeftPos = GetObj()->GetPos() + Vec2(-70.f, 33.f);
				Vec2 vBossSkillBallLeftScale = Vec2(120.f, 60.f);

				pBossSkillBallLeft->SetPos(vBossSkillBallLeftPos);
				pBossSkillBallLeft->SetScale(vBossSkillBallLeftScale);

				if (L"BossSkillBallLeft" == pBossSkillBallLeft->GetName())
				{
					SpawnObject(qLevelMgr::GetInst()->GetCurrentLevel(), LAYER_TYPE::BOSS_SKILL, pBossSkillBallLeft);
				}

				m_OneShot = false;
			}
		}

		if (GetAnimator()->IsFinish())
		{
			GetFSM()->ChangeState(L"Idle");
		}
	}
	
	
}

void qBossBallState::Exit()
{
	m_OneShot = true;
	pSound->SetVolume(30.f);
	pSound->Stop();
}
