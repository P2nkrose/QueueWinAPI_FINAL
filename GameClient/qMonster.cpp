#include "pch.h"
#include "qMonster.h"

#include "qCollider.h"

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
