#include "pch.h"
#include "qCollisionMgr.h"

#include "qLevel.h"
#include "qLevelMgr.h"


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

