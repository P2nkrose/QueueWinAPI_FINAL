#include "pch.h"
#include "qCollisionMgr.h"

#include "qLevel.h"
#include "qLevelMgr.h"

#include "qCollider.h"


qCollisionMgr::qCollisionMgr()
	: m_Matrix{}
{

}

qCollisionMgr::~qCollisionMgr()
{

}

void qCollisionMgr::init()
{

}

void qCollisionMgr::tick()
{
	qLevel* pCurLevel = qLevelMgr::GetInst()->GetCurrentLevel();

	for (int Row = 0; Row < (UINT)LAYER_TYPE::END; ++Row)
	{
		for (int Col = 0; Col < (UINT)LAYER_TYPE::END; ++Col)
		{
			if (m_Matrix[Row] & (1 << Col))
			{
				const vector<qCollider*>& vecLeft = pCurLevel->GetColliders((LAYER_TYPE)Row);
				const vector<qCollider*>& vecRight = pCurLevel->GetColliders((LAYER_TYPE)Col);

				for (size_t i = 0; i < vecLeft.size(); ++i)
				{
					for (size_t j = 0; j < vecRight.size(); ++j)
					{
						COLLIDER_ID id = {};

						id.LeftID = vecLeft[i]->GetID();
						id.RightID = vecRight[j]->GetID();

						map<ULONGLONG, bool>::iterator iter = m_mapCollisionInfo.find(id.ID);

						// 등록된 적이 없으면 등록시킨다.
						if (iter == m_mapCollisionInfo.end())
						{
							m_mapCollisionInfo.insert(make_pair(id.ID, false));
							iter = m_mapCollisionInfo.find(id.ID);
						}

						bool bDead = vecLeft[i]->GetOwner()->IsDead() || vecRight[j]->GetOwner()->IsDead();

						// 두 충돌체가 지금 충돌중이다.
						if (IsCollision(vecLeft[i], vecRight[j]))
						{
							// 이전에도 충돌중이었다.
							if (iter->second)
							{
								vecLeft[i]->OnOverlap(vecRight[j]);
								vecRight[j]->OnOverlap(vecLeft[i]);
							}

							// 이전에는 충돌중이 아니었다.
							else
							{
								vecLeft[i]->BeginOverlap(vecRight[j]);
								vecRight[j]->BeginOverlap(vecLeft[i]);
							}

							iter->second = true;

							// 두 충돌체 중 하나라도 Dead 상태라면 추가로 충돌 해제를 호출시켜 준다.
							if (bDead)
							{
								vecLeft[i]->EndOverlap(vecRight[j]);
								vecRight[j]->EndOverlap(vecLeft[i]);
							}
						}

						// 두 충돌체가 지금 충돌중이 아니다.
						else
						{
							// 이전에는 충돌중이었다.
							if (iter->second)
							{
								vecLeft[i]->EndOverlap(vecRight[j]);
								vecRight[j]->EndOverlap(vecLeft[i]);
							}

							iter->second = false;
						}
					}
				}

			}
		}
	}
}


void qCollisionMgr::CollisionCheck(LAYER_TYPE Layer1, LAYER_TYPE Layer2)
{
	UINT Row = (UINT)Layer1;
	UINT Col = (UINT)Layer2;

	if (Row > Col)
	{
		Row = (UINT)Layer2;
		Col = (UINT)Layer1;
	}

	m_Matrix[Row] |= (1 << Col);
	// m_Matrix[Row] = m_Matrix[Row] | (1 << Col);
}

void qCollisionMgr::CollisionUnCheck(LAYER_TYPE _Layer1, LAYER_TYPE _Layer2)
{
	UINT Row = (UINT)_Layer1;
	UINT Col = (UINT)_Layer2;

	if (Row > Col)
	{
		Row = (UINT)_Layer2;
		Col = (UINT)_Layer1;
	}

	m_Matrix[Row] &= ~(1 << Col);
}


bool qCollisionMgr::IsCollision(qCollider* _Left, qCollider* _Right)
{
	Vec2 vLeftPos = _Left->GetFinalPos();
	Vec2 vLeftScale = _Left->GetScale();

	Vec2 vRightPos = _Right->GetFinalPos();
	Vec2 vRightScale = _Right->GetScale();

	if (abs(vLeftPos.x - vRightPos.x) <= (vLeftScale.x + vRightScale.x) * 0.5f
		&& abs(vLeftPos.y - vRightPos.y) <= (vLeftScale.y + vRightScale.y) * 0.5f)
	{
		return true;
	}

	return false;
}

