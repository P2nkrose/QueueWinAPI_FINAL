#include "pch.h"
#include "qLevel_stage2.h"

#include "qKeyMgr.h"
#include "qLevelMgr.h"

#include "qCollisionMgr.h"
#include "qPlayer.h"
#include "qMonster.h"
#include "qPlatform.h"
#include "qBackground_stage2.h"

#include "qSound.h"


qLevel_stage2::qLevel_stage2()
{
	SetName(L"Stage2");
}

qLevel_stage2::~qLevel_stage2()
{
}

void qLevel_stage2::begin()
{
	qLevel::begin();

	pSound = qAssetMgr::GetInst()->LoadSound(L"BGM_START", L"sound\\stage2.wav");
	pSound->SetVolume(50.f);
	pSound->Play();

	qCamera::GetInst()->SetCameraEffect(CAM_EFFECT::FADE_IN, 0.7f);
}

void qLevel_stage2::tick()
{
	qLevel::tick();


	if (KEY_TAP(KEY::ENTER))
	{
		ChangeLevel(LEVEL_TYPE::EDITOR);
	}

	if (KEY_TAP(KEY::X))
	{
		::ChangeLevel(LEVEL_TYPE::BOSS_01);
	}
}

void qLevel_stage2::Enter()
{
	

	// 레벨에 오브젝트 추가
	// 
	// Background
	qObj* pBack = new qBackground_stage2;
	pBack->SetName(L"Stage2");
	pBack->SetPos(0.0f, -710.f);
	pBack->SetScale(1.3f, 1.3f);
	AddObject(LAYER_TYPE::BACKGROUND, pBack);

	// Player
	qObj* pPlayer = new qPlayer;
	pPlayer->SetName(L"Player");
	pPlayer->SetPos(1825.f, 745.f);
	pPlayer->SetScale(100.0f, 100.0f);
	AddObject(LAYER_TYPE::PLAYER, pPlayer);


	// 플랫폼 생성
	qObj* pPlatform = new qPlatform;
	pPlatform->SetName(L"Platform");
	pPlatform->SetPos(Vec2(640.f, 700.f));
	AddObject(LAYER_TYPE::PLATFORM, pPlatform);


	// 콜라이더 읽어오기
	LoadFromFile(L"platform\\platform.plat");


	// 레벨 충돌 설정하기
	qCollisionMgr::GetInst()->CollisionCheckClear();
	qCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::MONSTER);
	qCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER_MISSILE, LAYER_TYPE::MONSTER);
	qCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::PLATFORM);


}

void qLevel_stage2::Exit()
{
	

	pSound->SetVolume(50.f);
	pSound->Stop();

	// 레벨에 있는 모든 오브젝트 삭제한다.
	DeleteAllObjects();

	//qCamera::GetInst()->SetCameraEffect(CAM_EFFECT::FADE_OUT, 1.f);
}
