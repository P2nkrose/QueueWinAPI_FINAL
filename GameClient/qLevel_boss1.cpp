#include "pch.h"
#include "qLevel_boss1.h"

#include "qCollisionMgr.h"
#include "qPlayer.h"
#include "qMonster.h"
#include "qPlatform.h"
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
	pSound->SetVolume(50.f);
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
	

	// 레벨에 오브젝트 추가
	//
	// Background
	qObj* pBack = new qBackground_boss1;
	pBack->SetName(L"Boss1");
	pBack->SetPos(0.f, 0.f);
	AddObject(LAYER_TYPE::BACKGROUND, pBack);

	// Player
	qObj* pPlayer = new qPlayer;
	pPlayer->SetName(L"Player");
	pPlayer->SetPos(227.f, 766.f);
	pPlayer->SetScale(100.0f, 100.0f);
	AddObject(LAYER_TYPE::PLAYER, pPlayer);


	// 플랫폼 생성
	//qObj* pPlatform = new qPlatform;
	//pPlatform->SetName(L"Platform");
	//pPlatform->SetPos(Vec2(640.f, 700.f));
	//AddObject(LAYER_TYPE::PLATFORM, pPlatform);


	// 콜라이더 읽어오기
	LoadPlatform(L"platform\\platform.dat");
	LoadMonster(L"monster\\monster.dat");


	// 레벨 충돌 설정하기
	qCollisionMgr::GetInst()->CollisionCheckClear();
	qCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::MONSTER);
	qCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER_MISSILE, LAYER_TYPE::MONSTER);
	qCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::PLATFORM);
}

void qLevel_boss1::Exit()
{
	


	pSound->SetVolume(50.f);
	pSound->Stop();

	// 레벨에 있는 모든 오브젝트 삭제한다.
	DeleteAllObjects();
}
