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
	// 추적할 대상이 있는지 없는지 확인
	//if (nullptr == m_Target || m_Target->IsDead())
	//{
	//	FindTarget();
	//}

	if (!IsValid(m_Target))
	{
		FindTarget();
	}


	// 대상 탐색을 했는데도 아직 타겟이 없다면
	if (m_Target)
	{
		// 미사일이 추적할 대상을 향하는 각도를 구해서 각도설정을 해준다.
		float fSlide = GetPos().GetDistance(m_Target->GetPos());	// 빗변
		float fDown = m_Target->GetPos().x - GetPos().x;			// 밑변
		float fHeight = m_Target->GetPos().y - GetPos().y;			// 높이

		// 코사인 비율값으로 각도를 얻는다.
		float fAngle = acosf(fDown / fSlide);

		// 몬스터의 위치가 미사일보다 아래있다면, 코사인 비율에 대한 각도가 더 큰 값이 나와야 하는데,
		// 아크 코사인 함수가 리턴 범위가 -180 ~ 180 이기 때문에, 전각 360 도에서 리턴된 값을 빼서 반대편의 큰 각도를 알아낸다.
		if (GetPos().y < m_Target->GetPos().y)
		{
			fAngle = PI * 2.f - fAngle;
		}

		SetAngle(fAngle);
	}
	else
	{
		SetAngle(PI / 2.f);		// 타겟 없으면 그냥 위로 쏜다.
	}

	qMissile::tick();
}

void qGuideMissile::FindTarget()
{
	if (LAYER_TYPE::MONSTER_MISSILE == GetLayerType())
	{
		// 플레이어를 탐색
		qLevel* pCurLevel = qLevelMgr::GetInst()->GetCurrentLevel();
		m_Target = pCurLevel->FindObjectByName(L"Player");
	}
	else if (LAYER_TYPE::PLAYER_MISSILE == GetLayerType())
	{
		// 몬스터 전체 목록을 받아옴
		qLevel* pCurLevel = qLevelMgr::GetInst()->GetCurrentLevel();
		const vector<qObj*>& vecMonster = pCurLevel->GetObjects(LAYER_TYPE::MONSTER);

		// 미사일의 위치
		Vec2 vMissilePos = GetPos();

		float fMinDist = m_Range;
		m_Target = nullptr;

		for (size_t i = 0; i < vecMonster.size(); ++i)
		{
			// Dead 상태인 오브젝트는 거른다.
			if (vecMonster[i]->IsDead())
			{
				continue;
			}

			// 몬스터와 미사일의 거리를 구한다.
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


