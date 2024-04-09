#include "pch.h"
#include "qBossTornadoState.h"

#include "qAnimator.h"
#include "qSound.h"

#include "qBossSkill_tornado.h"
#include "qLevel.h"
#include "qLevelMgr.h"

#include "qTaskMgr.h"

qBossTornadoState::qBossTornadoState()
	: m_Time(0.f)
	, m_Dir(-1.f)
	, m_OneShot(true)
{

}

qBossTornadoState::~qBossTornadoState()
{
	
}

void qBossTornadoState::Enter()
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
		GetAnimator()->Play(L"BossTornadoRight", false);

		// 스킬 사운드
		pSound = qAssetMgr::GetInst()->LoadSound(L"BGM_START", L"sound\\boss\\tornado.wav");
		pSound->SetVolume(30.f);
		pSound->Play();
	}
	else if (m_Dir == -1.f)
	{
		GetAnimator()->Play(L"BossTornadoLeft", false);

		// 스킬 사운드
		pSound = qAssetMgr::GetInst()->LoadSound(L"BGM_START", L"sound\\boss\\tornado.wav");
		pSound->SetVolume(30.f);
		pSound->Play();
	}
}

void qBossTornadoState::FinalTick()
{
	qObj* pBoss = GetBlackboardData<qObj*>(L"Boss");
	int pBossHP = GetBlackboardData<int>(L"BossHP");
	qObj* pPlayer = GetBlackboardData<qObj*>(L"Player");

	if (L"BossTornadoRight" == GetAnimator()->GetCurAnim()->GetName())
	{
		if (GetAnimator()->GetCurAnim()->GetCurFrmIdx() == 18)
		{
			if (m_OneShot == true)
			{
				// 불새 소환
				qBossSkill_tornado* pBossSkillTornado = new qBossSkill_tornado;
				pBossSkillTornado->SetName(L"BossSkillTornado");

				Vec2 vBossSkillTornadoScale = Vec2(265.f, 600.f);

				pBossSkillTornado->SetPos(Vec2(pPlayer->GetPos().x, GetObj()->GetPos().y - 130.f));
				pBossSkillTornado->SetScale(vBossSkillTornadoScale);

				if (L"BossSkillTornado" == pBossSkillTornado->GetName())
				{
					SpawnObject(qLevelMgr::GetInst()->GetCurrentLevel(), LAYER_TYPE::BOSS_SKILL, pBossSkillTornado);
				}

				m_OneShot = false;

			}
		}



		if (GetAnimator()->IsFinish())
		{
			GetFSM()->ChangeState(L"Idle");
		}
	}

	if (L"BossTornadoLeft" == GetAnimator()->GetCurAnim()->GetName())
	{
		if (GetAnimator()->GetCurAnim()->GetCurFrmIdx() == 18)
		{
			if (m_OneShot == true)
			{
				// 불새 소환
				qBossSkill_tornado* pBossSkillTornado = new qBossSkill_tornado;
				pBossSkillTornado->SetName(L"BossSkillTornado");

				Vec2 vBossSkillTornadoScale = Vec2(265.f, 600.f);

				pBossSkillTornado->SetPos(Vec2(pPlayer->GetPos().x, GetObj()->GetPos().y - 130.f));
				pBossSkillTornado->SetScale(vBossSkillTornadoScale);

				if (L"BossSkillTornado" == pBossSkillTornado->GetName())
				{
					SpawnObject(qLevelMgr::GetInst()->GetCurrentLevel(), LAYER_TYPE::BOSS_SKILL, pBossSkillTornado);
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

void qBossTornadoState::Exit()
{
	m_OneShot = true;
	pSound->SetVolume(30.f);
	pSound->Stop();
}
