#include "pch.h"
#include "qMonster.h"

#include "qCollider.h"
#include "qMissile.h"

#include "qRigidbody.h"

qMonster::qMonster()
	: m_HP(5)
{
	m_Collider = (qCollider*)AddComponent(new qCollider);
	m_Collider->SetScale(Vec2(120.f, 120.f));

	m_Rigidbody = (qRigidbody*)AddComponent(new qRigidbody);
	m_Rigidbody->SetMass(2.f);
	m_Rigidbody->SetInitialWalkSpeed(0.f);
	m_Rigidbody->SetMaxWalkSpeed(400.f);
	m_Rigidbody->SetFriction(2000.f);

	m_Img = qAssetMgr::GetInst()->LoadTexture(L"texture\\Fighter.bmp", L"texture\\Fighter.bmp");
}

qMonster::~qMonster()
{
}

void qMonster::tick()
{
}

void qMonster::render()
{
	Vec2 vPos = GetRenderPos();
	Vec2 vScale = GetScale();

	static float alpha = 0;
	static float dir = 1;

	alpha += DT * 400.f * dir;

	if (255.f <= alpha)
	{
		dir *= -1.f;
	}
	else if (alpha <= 0.f)
	{
		dir *= -1.f;
	}

	// AlphaBlending
	BLENDFUNCTION bf = {};

	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.SourceConstantAlpha = (int)alpha;
	bf.AlphaFormat = AC_SRC_ALPHA;

	AlphaBlend(DC
				, (int)(vPos.x - m_Img->GetWidth() * 0.5f)
				, (int)(vPos.y - m_Img->GetHeight() * 0.5f)
				, m_Img->GetWidth()
				, m_Img->GetHeight()
				, m_Img->GetDC()
				, 0, 0
				, m_Img->GetWidth(), m_Img->GetHeight()
				, bf);
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
