#include "pch.h"
#include "qForce.h"

#include "qLevel.h"
#include "qLevelMgr.h"
#include "qRigidbody.h"


qForce::qForce()
	: m_Force(0.f)
	, m_Range(0.f)
	, m_Time(0.f)
	, m_Age(0.f)
{
}

qForce::~qForce()
{
}

void qForce::tick()
{
	AddForce(LAYER_TYPE::MONSTER_BLUE);
	AddForce(LAYER_TYPE::MONSTER_RED);
	AddForce(LAYER_TYPE::PLAYER);

	DrawDebugCircle(PEN_TYPE::PEN_BLUE, GetPos(), Vec2(m_Range * 2.f, m_Range * 2.f), 0.f);

	m_Age += DT;

	if (m_Time < m_Age)
	{
		Destroy();
	}

}

void qForce::AddForce(LAYER_TYPE _type)
{
	// �������� Force �ֺ��� �ִ� ��ü�鿡�� ���� �����Ų��.
	qLevel* pCurLevel = qLevelMgr::GetInst()->GetCurrentLevel();
	const vector<qObj*>& vecObj = pCurLevel->GetObjects(_type);

	for (size_t i = 0; i < vecObj.size(); ++i)
	{
		float fDist = GetPos().GetDistance(vecObj[i]->GetPos());
		if (fDist <= m_Range)
		{
			qRigidbody* pComponent = vecObj[i]->GetComponent<qRigidbody>();
			if (nullptr == pComponent)
				continue;

			// ��ü�� Force �� �������� 1�� ����� �������� ���´�.
			// ��ü�� Force �� �ּ��� 0�� ����� �������� ���´�. Force�� Range �� ����� Ratio �� 0�̴�.
			float fRatio = Saturate(1.f - fDist / m_Range);
			float Force = m_Force * fRatio;

			Vec2 vForce = vecObj[i]->GetPos() - GetPos();
			if (!vForce.IsZero())
			{
				vForce.Normalize();
				vForce *= Force;
				pComponent->AddForce(vForce);
			}
		}
	}
}
