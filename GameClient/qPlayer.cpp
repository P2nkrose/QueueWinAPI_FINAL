#include "pch.h"
#include "qPlayer.h"

#include "qLevelMgr.h"
#include "qLevel.h"

#include "qMissile.h"
#include "qCollider.h"

#include "qDbgRender.h"


qPlayer::qPlayer()
	: m_Speed(500.f)
	, m_PlayerImg(nullptr)
{
	// Player의 컴포넌트 설정
	m_HeadCol = (qCollider*)AddComponent(new qCollider);
	m_BodyCol = (qCollider*)AddComponent(new qCollider);

	m_HeadCol->SetName(L"Head Collider");
	m_HeadCol->SetOffsetPos(Vec2(0.f, -80.f));
	m_HeadCol->SetScale(Vec2(30.f, 30.f));
	m_HeadCol->SetActive(true);

	m_BodyCol->SetName(L"Body Collider");
	m_BodyCol->SetOffsetPos(Vec2(0.f, 0.f));
	m_BodyCol->SetScale(Vec2(60.f, 60.f));
	m_BodyCol->SetActive(true);

	m_PlayerImg = qAssetMgr::GetInst()->LoadTexture(L"PlayerTex", L"texture\\Fighter.bmp");

}

qPlayer::~qPlayer()
{
}


void qPlayer::begin()
{
}

void qPlayer::tick()
{
	// GetAsyncKeyState
	// 0x0000 : 이전에도 누른적이 없고, 호출 시점에도 안눌려있을때
	// 0x0001 : 이전에 누른적이 있고, 호출 시점에 안눌려있을때 (뗄떼)
	// 0x8000 : 이전에 누른적이 없고, 호출 시점에 눌려있을때 (누를때)
	// 0x8001 : 이전에 눌려있고, 호출 시점에 눌려있을때 (계속누를때)

	Vec2 vPos = GetPos();

	if (KEY_PRESSED(LEFT))
	{
		vPos.x -= m_Speed * DT;
	}

	if (KEY_PRESSED(RIGHT))
	{
		vPos.x += m_Speed * DT;
	}

	if (KEY_PRESSED(UP))
	{
		vPos.y -= m_Speed * DT;
	}

	if (KEY_PRESSED(DOWN))
	{
		vPos.y += m_Speed * DT;
	}

	// SPACE 누르면 미사일 발사
	if (KEY_TAP(SPACE))
	{
		qMissile* pMissile = new qMissile;
		pMissile->SetName(L"Missile");

		Vec2 vMissilePos = GetPos();
		vMissilePos.y -= GetScale().y / 2.f;

		pMissile->SetPos(vMissilePos);
		pMissile->SetScale(Vec2(20.f, 20.f));


		// TASK
		SpawnObject(qLevelMgr::GetInst()->GetCurrentLevel(), LAYER_TYPE::PLAYER_MISSILE, pMissile);
	}


	SetPos(vPos);
}


void qPlayer::render()
{
	Vec2 vPos = GetPos();

	float fWidth = (float)m_PlayerImg->GetWidth();
	float fHeight = (float)m_PlayerImg->GetHeight();

	//BitBlt(DC, vPos.x - fWidth / 2.f
	//	, vPos.y - fHeight / 2.f
	//	, fWidth, fHeight
	//	, m_PlayerImg->GetDC()
	//	, 0, 0, SRCCOPY);

	TransparentBlt(DC, int(vPos.x - fWidth / 2.f)
		, int(vPos.y - fHeight / 2.f)
		, (int)fWidth, (int)fHeight
		, m_PlayerImg->GetDC()
		, 0, 0, (int)fWidth, (int)fHeight
		, RGB(255, 0, 255));


	//qObj::render();
}


void qPlayer::BeginOverlap(qCollider* _OwnCollider, qObj* _OtherObj, qCollider* _OtherCollider)
{
	int a = 0;
}


void qPlayer::OnOverlap(qCollider* _OwnCollider, qObj* _OtherObj, qCollider* _OtherCollider)
{

}


void qPlayer::EndOverlap(qCollider* _OwnCollider, qObj* _OtherObj, qCollider* _OtherCollider)
{
	int a = 0;
}


