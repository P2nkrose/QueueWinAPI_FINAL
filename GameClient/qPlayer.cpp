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
	m_Collider = (qCollider*)AddComponent(new qCollider);
	m_Collider = GetComponent<qCollider>();

	m_Collider->SetOffsetPos(Vec2(0.f, 0.f));
	m_Collider->SetScale(Vec2(120.f, 120.f));
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
		pCurLevel->AddObject(pMissile);

		//DrawDebugRect(PEN_TYPE::PEN_GREEN, GetPos(), Vec2(500.f, 500.f), 3.f);

	}


	SetPos(vPos);
}


void qPlayer::render()
{
	qObj::render();
}


