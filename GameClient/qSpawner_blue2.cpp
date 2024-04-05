#include "pch.h"
#include "qSpawner_blue2.h"

#include "qMonster_blue.h"
#include "qLevelMgr.h"

qSpawner_blue2::qSpawner_blue2()
	: m_Time(0.f)
{
}

qSpawner_blue2::~qSpawner_blue2()
{
}

void qSpawner_blue2::begin()
{
	qObj::begin();
}

void qSpawner_blue2::tick()
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
		qObj* pBlue2 = new qMonster_blue(DIRECTION::RIGHT);
		pBlue2->SetName(L"Blue");
		pBlue2->SetPos(972.f, 1448.f);
		pBlue2->SetScale(100.0f, 100.0f);
		SpawnObject(qLevelMgr::GetInst()->GetCurrentLevel(), LAYER_TYPE::MONSTER_BLUE, pBlue2);
		SetOwner(pBlue2);
		pBlue2->begin();
		m_Time = 0.f;
	}
}
