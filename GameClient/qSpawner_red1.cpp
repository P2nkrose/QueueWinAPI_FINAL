#include "pch.h"
#include "qSpawner_red1.h"

#include "qMonster_red.h"
#include "qLevelMgr.h"

qSpawner_red1::qSpawner_red1()
	: m_Time(0.f)
{
}

qSpawner_red1::~qSpawner_red1()
{
}

void qSpawner_red1::begin()
{
	qObj::begin();
}

void qSpawner_red1::tick()
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
		qObj* pRed1 = new qMonster_red(DIRECTION::LEFT);
		pRed1->SetName(L"Red");
		pRed1->SetPos(1336.f, 1093.f);
		pRed1->SetScale(100.0f, 100.0f);
		SpawnObject(qLevelMgr::GetInst()->GetCurrentLevel(), LAYER_TYPE::MONSTER_RED, pRed1);
		SetOwner(pRed1);
		pRed1->begin();
		m_Time = 0.f;
	}
}
