#include "pch.h"
#include "qPlayer.h"

#include "qLevelMgr.h"
#include "qLevel.h"

#include "qMissile.h"
#include "qCollider.h"


qPlayer::qPlayer()
	: m_Speed(500.f)
{
	// Player�� ������Ʈ ����
	m_HeadCol = (qCollider*)AddComponent(new qCollider);
	m_BodyCol = (qCollider*)AddComponent(new qCollider);
	//m_Collider = GetComponent<qCollider>();

	m_HeadCol->SetName(L"Head Collider");
	m_HeadCol->SetOffsetPos(Vec2(0.f, -80.f));
	m_HeadCol->SetScale(Vec2(30.f, 30.f));
	m_HeadCol->SetActive(true);

	m_BodyCol->SetName(L"Body Collider");
	m_BodyCol->SetOffsetPos(Vec2(0.f, 0.f));
	m_BodyCol->SetScale(Vec2(60.f, 60.f));
	m_BodyCol->SetActive(true);

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
	// 0x0000 : �������� �������� ����, ȣ�� �������� �ȴ���������
	// 0x0001 : ������ �������� �ְ�, ȣ�� ������ �ȴ��������� (����)
	// 0x8000 : ������ �������� ����, ȣ�� ������ ���������� (������)
	// 0x8001 : ������ �����ְ�, ȣ�� ������ ���������� (��Ӵ�����)

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

	// SPACE ������ �̻��� �߻�
	if (KEY_TAP(SPACE))
	{
		qMissile* pMissile = new qMissile;

		Vec2 vMissilePos = GetPos();
		vMissilePos.y -= GetScale().y / 2.f;

		pMissile->SetPos(vMissilePos);
		pMissile->SetScale(Vec2(20.f, 20.f));

		qLevel* pCurLevel = qLevelMgr::GetInst()->GetCurrentLevel();
		pCurLevel->AddObject(LAYER_TYPE::PLAYER_MISSILE, pMissile);

		//DrawDebugRect(PEN_TYPE::PEN_GREEN, GetPos(), Vec2(500.f, 500.f), 3.f);

	}


	SetPos(vPos);
}


void qPlayer::render()
{
	qObj::render();
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


