#include "pch.h"
#include "qBossFirebirdState.h"

#include "qAnimator.h"
#include "qSound.h"

#include "qBossSkill_firebird.h"
#include "qLevel.h"
#include "qLevelMgr.h"

#include "qTaskMgr.h"

qBossFirebirdState::qBossFirebirdState()
	: m_Time(0.f)
	, m_Dir(-1.f)
	, m_OneShot(true)
{
}

qBossFirebirdState::~qBossFirebirdState()
{
}

void qBossFirebirdState::Enter()
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
		GetAnimator()->Play(L"BossFirebirdRight", false);

		// 스킬 사운드
		pSound = qAssetMgr::GetInst()->LoadSound(L"BGM_START", L"sound\\boss\\firebird.wav");
		pSound->SetVolume(30.f);
		pSound->Play();
	}
	else if (m_Dir == -1.f)
	{
		GetAnimator()->Play(L"BossFirebirdLeft", false);

		// 스킬 사운드
		pSound = qAssetMgr::GetInst()->LoadSound(L"BGM_START", L"sound\\boss\\firebird.wav");
		pSound->SetVolume(30.f);
		pSound->Play();
	}
}

void qBossFirebirdState::FinalTick()
{
	qObj* pBoss = GetBlackboardData<qObj*>(L"Boss");
	qObj* pPlayer = GetBlackboardData<qObj*>(L"Player");
	int pBossHP = GetBlackboardData<int>(L"BossHP");


	if (L"BossFirebirdRight" == GetAnimator()->GetCurAnim()->GetName())
	{
		if (GetAnimator()->GetCurAnim()->GetCurFrmIdx() == 12)
		{
			if (m_OneShot == true)
			{
				// 불새 소환
				qBossSkill_firebird* pBossSkillFirebird = new qBossSkill_firebird;
				pBossSkillFirebird->SetName(L"BossSkillFirebird");

				Vec2 vBossSkillFirebirdScale = Vec2(700.f, 400.f);

				pBossSkillFirebird->SetPos(Vec2(pPlayer->GetPos().x, GetObj()->GetPos().y - 56.f));
				pBossSkillFirebird->SetScale(vBossSkillFirebirdScale);

				if (L"BossSkillFirebird" == pBossSkillFirebird->GetName())
				{
					SpawnObject(qLevelMgr::GetInst()->GetCurrentLevel(), LAYER_TYPE::BOSS_SKILL, pBossSkillFirebird);
				}

				m_OneShot = false;

			}
		}


		if (GetAnimator()->IsFinish())
		{
			GetFSM()->ChangeState(L"Idle");
		}
	}

	else if (L"BossFirebirdLeft" == GetAnimator()->GetCurAnim()->GetName())
	{
		if (GetAnimator()->GetCurAnim()->GetCurFrmIdx() == 12)
		{
			if (m_OneShot == true)
			{
				// 불새 소환
				qBossSkill_firebird* pBossSkillFirebird = new qBossSkill_firebird;
				pBossSkillFirebird->SetName(L"BossSkillFirebird");

				Vec2 vBossSkillFirebirdScale = Vec2(700.f, 400.f);

				pBossSkillFirebird->SetPos(Vec2(pPlayer->GetPos().x, GetObj()->GetPos().y - 56.f));
				pBossSkillFirebird->SetScale(vBossSkillFirebirdScale);

				if (L"BossSkillFirebird" == pBossSkillFirebird->GetName())
				{
					SpawnObject(qLevelMgr::GetInst()->GetCurrentLevel(), LAYER_TYPE::BOSS_SKILL, pBossSkillFirebird);
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

void qBossFirebirdState::Exit()
{
	m_OneShot = true;
	pSound->SetVolume(30.f);
	pSound->Stop();
}



