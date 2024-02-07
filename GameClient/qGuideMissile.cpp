#include "pch.h"
#include "qGuideMissile.h"

#include "qLevelMgr.h"
#include "qLevel.h"

qGuideMissile::qGuideMissile()
	: m_Target(nullptr)
	, m_Range(1000.f)
{
}

qGuideMissile::~qGuideMissile()
{
}



void qGuideMissile::tick()
{
	// ������ ����� �ִ��� ������ Ȯ��
	//if (nullptr == m_Target || m_Target->IsDead())
	//{
	//	FindTarget();
	//}

	if (!IsValid(m_Target))
	{
		FindTarget();
	}


	// ��� Ž���� �ߴµ��� ���� Ÿ���� ���ٸ�
	if (m_Target)
	{
		// �̻����� ������ ����� ���ϴ� ������ ���ؼ� ���������� ���ش�.
		float fSlide = GetPos().GetDistance(m_Target->GetPos());	// ����
		float fDown = m_Target->GetPos().x - GetPos().x;			// �غ�
		float fHeight = m_Target->GetPos().y - GetPos().y;			// ����

		// �ڻ��� ���������� ������ ��´�.
		float fAngle = acosf(fDown / fSlide);

		// ������ ��ġ�� �̻��Ϻ��� �Ʒ��ִٸ�, �ڻ��� ������ ���� ������ �� ū ���� ���;� �ϴµ�,
		// ��ũ �ڻ��� �Լ��� ���� ������ -180 ~ 180 �̱� ������, ���� 360 ������ ���ϵ� ���� ���� �ݴ����� ū ������ �˾Ƴ���.
		if (GetPos().y < m_Target->GetPos().y)
		{
			fAngle = PI * 2.f - fAngle;
		}

		SetAngle(fAngle);
	}
	else
	{
		SetAngle(PI / 2.f);		// Ÿ�� ������ �׳� ���� ���.
	}

	qMissile::tick();
}

void qGuideMissile::FindTarget()
{
	if (LAYER_TYPE::MONSTER_MISSILE == GetLayerType())
	{
		// �÷��̾ Ž��
		qLevel* pCurLevel = qLevelMgr::GetInst()->GetCurrentLevel();
		m_Target = pCurLevel->FindObjectByName(L"Player");
	}
	else if (LAYER_TYPE::PLAYER_MISSILE == GetLayerType())
	{
		// ���� ��ü ����� �޾ƿ�
		qLevel* pCurLevel = qLevelMgr::GetInst()->GetCurrentLevel();
		const vector<qObj*>& vecMonster = pCurLevel->GetObjects(LAYER_TYPE::MONSTER);

		// �̻����� ��ġ
		Vec2 vMissilePos = GetPos();

		float fMinDist = m_Range;
		m_Target = nullptr;

		for (size_t i = 0; i < vecMonster.size(); ++i)
		{
			// Dead ������ ������Ʈ�� �Ÿ���.
			if (vecMonster[i]->IsDead())
			{
				continue;
			}

			// ���Ϳ� �̻����� �Ÿ��� ���Ѵ�.
			float fDist = vMissilePos.GetDistance(vecMonster[i]->GetPos());

			if (fDist < fMinDist)
			{
				fMinDist = fDist;
				m_Target = vecMonster[i];
			}
		}
	}
}


void qGuideMissile::BeginOverlap(qCollider* _OwnCollider, qObj* _OtherObj, qCollider* _OtherCollider)
{
	if (_OtherObj->GetName() == L"Monster")
	{
		//Destroy();
	}
}


