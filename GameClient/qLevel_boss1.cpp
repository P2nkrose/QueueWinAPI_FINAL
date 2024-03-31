#include "pch.h"
#include "qLevel_boss1.h"

#include "qCollisionMgr.h"
#include "qPlayer.h"

#include "qPlatform.h"
#include "qRope.h"
#include "qPortal.h"
#include "qMonster_red.h"
#include "qMonster_blue.h"

#include "qBackground_boss1.h"

#include "qSound.h"

qLevel_boss1::qLevel_boss1()
{
	SetName(L"Boss1");
}

qLevel_boss1::~qLevel_boss1()
{
}

void qLevel_boss1::begin()
{
	qLevel::begin();

	pSound = qAssetMgr::GetInst()->LoadSound(L"BGM_START", L"sound\\boss1.wav");
	pSound->SetVolume(30.f);
	pSound->Play();

	qCamera::GetInst()->SetCameraEffect(CAM_EFFECT::FADE_IN, 0.7f);
}

void qLevel_boss1::tick()
{
	qLevel::tick();

	if (KEY_TAP(KEY::ENTER))
	{
		::ChangeLevel(LEVEL_TYPE::EDITOR);
	}

	if (KEY_TAP(KEY::Z))
	{
		::ChangeLevel(LEVEL_TYPE::STAGE_01);
	}

	if (KEY_TAP(KEY::X))
	{
		::ChangeLevel(LEVEL_TYPE::STAGE_02);
	}

	if (KEY_TAP(KEY::V))
	{
		::ChangeLevel(LEVEL_TYPE::BOSS_02);
	}

}

void qLevel_boss1::Enter()
{
	

	// ������ ������Ʈ �߰�
	//
	// Background
	qObj* pBack = new qBackground_boss1;
	pBack->SetName(L"Boss1");
	pBack->SetPos(0.f, 0.f);
	AddObject(LAYER_TYPE::BACKGROUND, pBack);

	// Player
	qObj* pPlayer = new qPlayer;
	pPlayer->SetName(L"Player");
	pPlayer->SetPos(223.f, 771.f);
	pPlayer->SetScale(100.0f, 100.0f);
	AddObject(LAYER_TYPE::PLAYER, pPlayer);


	// �÷��� ����
	//qObj* pPlatform = new qPlatform;
	//pPlatform->SetName(L"Platform");
	//pPlatform->SetPos(Vec2(640.f, 700.f));
	//AddObject(LAYER_TYPE::PLATFORM, pPlatform);


	// �ݶ��̴� �о����
	LoadPlatform(L"platform\\platform.dat");
	LoadRope(L"rope\\rope.dat");
	LoadPortal(L"portal\\portal.dat");

	LoadMonster_blue(L"monster_blue\\monster_blue.dat");
	LoadMonster_red(L"monster_red\\monster_red.dat");

	// ���� �浹 �����ϱ�
	qCollisionMgr::GetInst()->CollisionCheckClear();

	qCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::PLATFORM);
	qCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::ROPE);
	qCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::PORTAL);
}

void qLevel_boss1::Exit()
{

	pSound->SetVolume(30.f);
	pSound->Stop();

	// ������ �ִ� ��� ������Ʈ �����Ѵ�.
	DeleteAllObjects();
}
