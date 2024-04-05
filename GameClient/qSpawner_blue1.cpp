#include "pch.h"
#include "qSpawner_blue1.h"

#include "qMonster_blue.h"
#include "qLevelMgr.h"

qSpawner_blue1::qSpawner_blue1()
	: m_Time(0.f)
{
}

qSpawner_blue1::~qSpawner_blue1()
{
}

void qSpawner_blue1::begin()
{
	qObj::begin();

	
}

void qSpawner_blue1::tick()
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
		qObj* pBlue1 = new qMonster_blue(DIRECTION::LEFT);
		pBlue1->SetName(L"Blue");
		pBlue1->SetPos(1377.f, 1448.f);
		pBlue1->SetScale(100.0f, 100.0f);
		SpawnObject(qLevelMgr::GetInst()->GetCurrentLevel(), LAYER_TYPE::MONSTER_BLUE, pBlue1);
		SetOwner(pBlue1);
		pBlue1->begin();
		m_Time = 0.f;
	}
}
