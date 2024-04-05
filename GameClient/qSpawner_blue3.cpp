#include "pch.h"
#include "qSpawner_blue3.h"

#include "qMonster_blue.h"
#include "qLevelMgr.h"

qSpawner_blue3::qSpawner_blue3()
	: m_Time(0.f)
{
}

qSpawner_blue3::~qSpawner_blue3()
{
}

void qSpawner_blue3::begin()
{
	qObj::begin();
}

void qSpawner_blue3::tick()
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
		qObj* pBlue3 = new qMonster_blue(DIRECTION::LEFT);
		pBlue3->SetName(L"Blue");
		pBlue3->SetPos(543.f, 1448.f);
		pBlue3->SetScale(100.0f, 100.0f);
		SpawnObject(qLevelMgr::GetInst()->GetCurrentLevel(), LAYER_TYPE::MONSTER_BLUE, pBlue3);
		SetOwner(pBlue3);
		pBlue3->begin();
		m_Time = 0.f;
	}
}
