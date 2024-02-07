#include "pch.h"
#include "qMonster.h"

#include "qCollider.h"
#include "qMissile.h"

qMonster::qMonster()
{
	m_Collider = (qCollider*)AddComponent(new qCollider);
	m_Collider->SetScale(Vec2(120.f, 120.f));
}

qMonster::~qMonster()
{
}

void qMonster::tick()
{
}

void qMonster::BeginOverlap(qCollider* _OwnCollider, qObj* _OtherObj, qCollider* _OtherCollider)
{
	qMissile* pMissile = dynamic_cast<qMissile*>(_OtherObj);

	if (pMissile != nullptr)
	{
		int a = 0;
	}

	if (_OtherObj->GetName() == L"Missile")
	{
		int a = 0;
	}
}
