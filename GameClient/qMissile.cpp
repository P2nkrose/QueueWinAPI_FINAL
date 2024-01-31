#include "pch.h"
#include "qMissile.h"

#include "qCollider.h"

qMissile::qMissile()
	: m_Speed(500.f)
{
	m_Collider = (qCollider*)AddComponent(new qCollider);

	m_Collider->SetOffsetPos(Vec2(0.f, 0.f));
	m_Collider->SetScale(Vec2(20.f, 20.f));
}

qMissile::~qMissile()
{
}


void qMissile::tick()
{
	Vec2 vPos = GetPos();
	vPos.y -= DT * m_Speed;
	SetPos(vPos);
}

void qMissile::render()
{
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();

	Ellipse(DC, (int)(vPos.x - vScale.x * 0.5f)
		, (int)(vPos.y - vScale.y * 0.5f)
		, (int)(vPos.x + vScale.x * 0.5f)
		, (int)(vPos.y + vScale.y * 0.5f));
}


