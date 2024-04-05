#include "pch.h"
#include "qSpawner_red2.h"

#include "qMonster_red.h"
#include "qLevelMgr.h"

qSpawner_red2::qSpawner_red2()
	: m_Time(0.f)
{
}

qSpawner_red2::~qSpawner_red2()
{
}

void qSpawner_red2::begin()
{
	qObj::begin();
}

void qSpawner_red2::tick()
{
	qObj::tick();

	if (nullptr != GetOwner())
	{
		if (GetOwner()->IsDead())
		{
			SetOwner(nullptr);
		}
	}
	if (nullptr == GetOwner())
	{
		m_Time += DT;
	}

	if (m_Time > 5.f)
	{
		qObj* pRed2 = new qMonster_red(DIRECTION::RIGHT);
		pRed2->SetName(L"Red");
		pRed2->SetPos(700.f, 1093.f);
		pRed2->SetScale(100.0f, 100.0f);
		SpawnObject(qLevelMgr::GetInst()->GetCurrentLevel(), LAYER_TYPE::MONSTER_RED, pRed2);
		SetOwner(pRed2);
		pRed2->begin();
		m_Time = 0.f;
	}
}
