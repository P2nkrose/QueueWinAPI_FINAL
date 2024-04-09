#include "pch.h"
#include "qBossGenesisState.h"

#include "qAnimator.h"
#include "qSound.h"

#include "qBossSkill_genesis.h"
#include "qLevel.h"
#include "qLevelMgr.h"

#include "qTaskMgr.h"

qBossGenesisState::qBossGenesisState()
	: m_Time(0.f)
	, m_Dir(-1.f)
	, m_OneShot(true)
{
}

qBossGenesisState::~qBossGenesisState()
{
}

void qBossGenesisState::Enter()
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
		GetAnimator()->Play(L"BossGenesisRight", false);

		// 스킬 사운드
		pSound = qAssetMgr::GetInst()->LoadSound(L"BGM_START", L"sound\\boss\\genesis.wav");
		pSound->SetVolume(30.f);
		pSound->Play();
	}
	else if (m_Dir == -1.f)
	{
		GetAnimator()->Play(L"BossGenesisLeft", false);

		// 스킬 사운드
		pSound = qAssetMgr::GetInst()->LoadSound(L"BGM_START", L"sound\\boss\\genesis.wav");
		pSound->SetVolume(30.f);
		pSound->Play();
	}
}

void qBossGenesisState::FinalTick()
{
	qObj* pBoss = GetBlackboardData<qObj*>(L"Boss");
	int pBossHP = GetBlackboardData<int>(L"BossHP");


	if (L"BossGenesisRight" == GetAnimator()->GetCurAnim()->GetName())
	{
		if (GetAnimator()->GetCurAnim()->GetCurFrmIdx() == 5)
		{
			if (m_OneShot == true)
			{
				// 다크 제네시스 소환 1
				qBossSkill_genesis* pBossSkillGenesis1 = new qBossSkill_genesis;
				pBossSkillGenesis1->SetName(L"BossSkillGenesis1");

				Vec2 vBossSkillGenesisPos1 = GetObj()->GetPos() + Vec2(-550.f, -185.f);
				Vec2 vBossSkillGenesisScale1 = Vec2(300.f, 590.f);

				pBossSkillGenesis1->SetPos(vBossSkillGenesisPos1);
				pBossSkillGenesis1->SetScale(vBossSkillGenesisScale1);

				if (L"BossSkillGenesis1" == pBossSkillGenesis1->GetName())
				{
					SpawnObject(qLevelMgr::GetInst()->GetCurrentLevel(), LAYER_TYPE::BOSS_SKILL, pBossSkillGenesis1);
				}


				// 다크 제네시스 소환 2
				qBossSkill_genesis* pBossSkillGenesis2 = new qBossSkill_genesis;
				pBossSkillGenesis2->SetName(L"BossSkillGenesis2");

				Vec2 vBossSkillGenesisPos2 = GetObj()->GetPos() + Vec2(-250.f, -185.f);
				Vec2 vBossSkillGenesisScale2 = Vec2(300.f, 590.f);

				pBossSkillGenesis2->SetPos(vBossSkillGenesisPos2);
				pBossSkillGenesis2->SetScale(vBossSkillGenesisScale2);

				if (L"BossSkillGenesis2" == pBossSkillGenesis2->GetName())
				{
					SpawnObject(qLevelMgr::GetInst()->GetCurrentLevel(), LAYER_TYPE::BOSS_SKILL, pBossSkillGenesis2);
				}


				// 다크 제네시스 소환 3
				qBossSkill_genesis* pBossSkillGenesis3 = new qBossSkill_genesis;
				pBossSkillGenesis3->SetName(L"BossSkillGenesis3");

				Vec2 vBossSkillGenesisPos3 = GetObj()->GetPos() + Vec2(250.f, -185.f);
				Vec2 vBossSkillGenesisScale3 = Vec2(300.f, 590.f);

				pBossSkillGenesis3->SetPos(vBossSkillGenesisPos3);
				pBossSkillGenesis3->SetScale(vBossSkillGenesisScale3);

				if (L"BossSkillGenesis3" == pBossSkillGenesis3->GetName())
				{
					SpawnObject(qLevelMgr::GetInst()->GetCurrentLevel(), LAYER_TYPE::BOSS_SKILL, pBossSkillGenesis3);
				}


				// 다크 제네시스 소환 4
				qBossSkill_genesis* pBossSkillGenesis4 = new qBossSkill_genesis;
				pBossSkillGenesis4->SetName(L"BossSkillGenesis4");

				Vec2 vBossSkillGenesisPos4 = GetObj()->GetPos() + Vec2(550.f, -185.f);
				Vec2 vBossSkillGenesisScale4 = Vec2(300.f, 590.f);

				pBossSkillGenesis4->SetPos(vBossSkillGenesisPos4);
				pBossSkillGenesis4->SetScale(vBossSkillGenesisScale4);

				if (L"BossSkillGenesis4" == pBossSkillGenesis4->GetName())
				{
					SpawnObject(qLevelMgr::GetInst()->GetCurrentLevel(), LAYER_TYPE::BOSS_SKILL, pBossSkillGenesis4);
				}

				m_OneShot = false;

			}
		}


		if (GetAnimator()->IsFinish())
		{
			GetFSM()->ChangeState(L"Idle");
		}
	}



	else if (L"BossGenesisLeft" == GetAnimator()->GetCurAnim()->GetName())
	{
		if (GetAnimator()->GetCurAnim()->GetCurFrmIdx() == 5)
		{
			if (m_OneShot == true)
			{
				// 다크 제네시스 소환 1
				qBossSkill_genesis* pBossSkillGenesis1 = new qBossSkill_genesis;
				pBossSkillGenesis1->SetName(L"BossSkillGenesis1");

				Vec2 vBossSkillGenesisPos1 = GetObj()->GetPos() + Vec2(-550.f, -185.f);
				Vec2 vBossSkillGenesisScale1 = Vec2(300.f, 590.f);

				pBossSkillGenesis1->SetPos(vBossSkillGenesisPos1);
				pBossSkillGenesis1->SetScale(vBossSkillGenesisScale1);

				if (L"BossSkillGenesis1" == pBossSkillGenesis1->GetName())
				{
					SpawnObject(qLevelMgr::GetInst()->GetCurrentLevel(), LAYER_TYPE::BOSS_SKILL, pBossSkillGenesis1);
				}


				// 다크 제네시스 소환 2
				qBossSkill_genesis* pBossSkillGenesis2 = new qBossSkill_genesis;
				pBossSkillGenesis2->SetName(L"BossSkillGenesis2");

				Vec2 vBossSkillGenesisPos2 = GetObj()->GetPos() + Vec2(-250.f, -185.f);
				Vec2 vBossSkillGenesisScale2 = Vec2(300.f, 590.f);

				pBossSkillGenesis2->SetPos(vBossSkillGenesisPos2);
				pBossSkillGenesis2->SetScale(vBossSkillGenesisScale2);

				if (L"BossSkillGenesis2" == pBossSkillGenesis2->GetName())
				{
					SpawnObject(qLevelMgr::GetInst()->GetCurrentLevel(), LAYER_TYPE::BOSS_SKILL, pBossSkillGenesis2);
				}


				// 다크 제네시스 소환 3
				qBossSkill_genesis* pBossSkillGenesis3 = new qBossSkill_genesis;
				pBossSkillGenesis3->SetName(L"BossSkillGenesis3");

				Vec2 vBossSkillGenesisPos3 = GetObj()->GetPos() + Vec2(250.f, -185.f);
				Vec2 vBossSkillGenesisScale3 = Vec2(300.f, 590.f);

				pBossSkillGenesis3->SetPos(vBossSkillGenesisPos3);
				pBossSkillGenesis3->SetScale(vBossSkillGenesisScale3);

				if (L"BossSkillGenesis3" == pBossSkillGenesis3->GetName())
				{
					SpawnObject(qLevelMgr::GetInst()->GetCurrentLevel(), LAYER_TYPE::BOSS_SKILL, pBossSkillGenesis3);
				}


				// 다크 제네시스 소환 4
				qBossSkill_genesis* pBossSkillGenesis4 = new qBossSkill_genesis;
				pBossSkillGenesis4->SetName(L"BossSkillGenesis4");

				Vec2 vBossSkillGenesisPos4 = GetObj()->GetPos() + Vec2(550.f, -185.f);
				Vec2 vBossSkillGenesisScale4 = Vec2(300.f, 590.f);

				pBossSkillGenesis4->SetPos(vBossSkillGenesisPos4);
				pBossSkillGenesis4->SetScale(vBossSkillGenesisScale4);

				if (L"BossSkillGenesis4" == pBossSkillGenesis4->GetName())
				{
					SpawnObject(qLevelMgr::GetInst()->GetCurrentLevel(), LAYER_TYPE::BOSS_SKILL, pBossSkillGenesis4);
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

void qBossGenesisState::Exit()
{
	m_OneShot = true;
	pSound->SetVolume(30.f);
	pSound->Stop();
}
