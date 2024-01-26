#include "pch.h"
#include "qMissile.h"

qMissile::qMissile()
	: m_Speed(1000.f)
{
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


