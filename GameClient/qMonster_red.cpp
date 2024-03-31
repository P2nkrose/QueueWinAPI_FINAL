#include "pch.h"
#include "qMonster_red.h"

#include "qCollider.h"
#include "qMissile.h"

#include "qRigidbody.h"
#include "qFSM.h"
#include "qIdleState.h"
#include "qTraceState.h"

#include "qLevelMgr.h"

qMonster_red::qMonster_red()
	: m_HP(5)
	, m_DetectRange(400)
	, m_Speed(100)
{
	SetName(L"Red");

	m_Collider = (qCollider*)AddComponent(new qCollider);
	m_Collider->SetScale(Vec2(60.f, 70.f));

	m_Img = qAssetMgr::GetInst()->LoadTexture(L"monster_red", L"texture\\edit\\monster_red.png");
}

qMonster_red::qMonster_red(Vec2 _Pos, Vec2 _Scale)
	: m_HP(5)
	, m_DetectRange(400)
	, m_Speed(100)
{
	SetName(L"Red");

	m_Img = qAssetMgr::GetInst()->LoadTexture(L"monster_red", L"texture\\edit\\monster_red.png");

	SetPos(_Pos);
	SetScale(_Scale);
	m_Collider = (qCollider*)AddComponent(new qCollider);
	m_Collider->SetScale(GetScale());

}

qMonster_red::~qMonster_red()
{
}

void qMonster_red::begin()
{
}

void qMonster_red::tick()
{
}

void qMonster_red::render()
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

void qMonster_red::BeginOverlap(qCollider* _OwnCollider, qObj* _OtherObj, qCollider* _OtherCollider)
{

}
