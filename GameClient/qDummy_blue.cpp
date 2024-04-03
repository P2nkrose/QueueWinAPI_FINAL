#include "pch.h"
#include "qDummy_blue.h"

#include "qCollider.h"
#include "qTexture.h"

qDummy_blue::qDummy_blue()
{
	// 콜라이더 설정
	m_Collider = (qCollider*)AddComponent(new qCollider);
	m_Collider->SetScale(Vec2(65.f, 85.f));

	m_Img = qAssetMgr::GetInst()->LoadTexture(L"monster_blue", L"texture\\edit\\monster_blue.png");

	SetName(L"DummyBlue");
}

qDummy_blue::qDummy_blue(const qDummy_blue& _Other)
{
	m_Collider = GetComponent<qCollider>();

	m_Img = qAssetMgr::GetInst()->LoadTexture(L"monster_blue", L"texture\\edit\\monster_blue.png");
}

qDummy_blue::~qDummy_blue()
{
}

void qDummy_blue::begin()
{
	qObj::begin();
}

void qDummy_blue::tick()
{
	qObj::tick();
}

void qDummy_blue::render()
{
	Vec2 vPos = GetRenderPos();
	Vec2 vScale = GetScale();

	BLENDFUNCTION bf = {};

	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.SourceConstantAlpha = 255;
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
