#include "pch.h"
#include "qMonster.h"

#include "qCollider.h"
#include "qMissile.h"

qMonster::qMonster()
	: m_HP(5)
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

void qMonster::render()
{
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();

	Rectangle(DC, (int)(vPos.x - vScale.x * 0.5f)
		, (int)(vPos.y - vScale.y * 0.5f)
		, (int)(vPos.x + vScale.x * 0.5f)
		, (int)(vPos.y + vScale.y * 0.5f));
}

void qMonster::BeginOverlap(qCollider* _OwnCollider, qObj* _OtherObj, qCollider* _OtherCollider)
{
	if (_OtherObj->GetName() == L"Missile")
	{
		--m_HP;

		if (0 >= m_HP)
		{
			Destroy();
		}
	}
}
