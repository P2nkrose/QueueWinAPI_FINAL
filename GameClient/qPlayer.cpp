#include "pch.h"
#include "qPlayer.h"

#include "qLevelMgr.h"
#include "qLevel.h"

#include "qMissile.h"

qPlayer::qPlayer()
	: m_Speed(500.f)
{
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

	if (0x8001 & GetAsyncKeyState(VK_LEFT))
	{
		vPos.x -= m_Speed * DT;
	}

	if (0x8001 & GetAsyncKeyState(VK_RIGHT))
	{
		vPos.x += m_Speed * DT;
	}

	if (0x8001 & GetAsyncKeyState(VK_UP))
	{
		vPos.y -= m_Speed * DT;
	}

	if (0x8001 & GetAsyncKeyState(VK_DOWN))
	{
		vPos.y += m_Speed * DT;
	}

	// SPACE ������ �̻��� �߻�
	if (0x8001 & GetAsyncKeyState(VK_SPACE))
	{
		qMissile* pMissile = new qMissile;

		Vec2 vMissilePos = GetPos();
		vMissilePos.y -= GetScale().y / 2.f;

		pMissile->SetPos(vMissilePos);
		pMissile->SetScale(Vec2(20.f, 20.f));

		qLevel* pCurLevel = qLevelMgr::GetInst()->GetCurrentLevel();
		pCurLevel->AddObject(pMissile);

	}


	SetPos(vPos);
}

void qPlayer::finaltick()
{
}

void qPlayer::render()
{
	qObj::render();
}


