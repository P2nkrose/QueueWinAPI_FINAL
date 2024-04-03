#include "pch.h"
#include "qDummy_red.h"

#include "qCollider.h"
#include "qTexture.h"

qDummy_red::qDummy_red()
{
	// 콜라이더 설정
	m_Collider = (qCollider*)AddComponent(new qCollider);
	m_Collider->SetScale(Vec2(57.f, 70.f));

	m_Img = qAssetMgr::GetInst()->LoadTexture(L"monster_red", L"texture\\edit\\monster_red.png");

	SetName(L"DummyRed");
}

qDummy_red::qDummy_red(const qDummy_red& _Other)
{
	m_Collider = GetComponent<qCollider>();

	m_Img = qAssetMgr::GetInst()->LoadTexture(L"monster_red", L"texture\\edit\\monster_red.png");
}

qDummy_red::~qDummy_red()
{
}

void qDummy_red::begin()
{
	qObj::begin();
}

void qDummy_red::tick()
{
	qObj::tick();
}

void qDummy_red::render()
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
