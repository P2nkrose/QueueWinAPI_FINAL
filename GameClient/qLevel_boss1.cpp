#include "pch.h"
#include "qLevel_boss1.h"

#include "qCollisionMgr.h"
#include "qPlayer.h"

#include "qPlatform.h"
#include "qRope.h"
#include "qPortal.h"
#include "qMonster_red.h"
#include "qMonster_blue.h"

#include "qMinimap_boss1.h"
#include "qMenu.h"

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

	pSound = qAssetMgr::GetInst()->LoadSound(L"BGM_START", L"sound\\level\\boss1.wav");
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
	// UI 추가
	// 화면 해상도
	Vec2 vResol = qEngine::GetInst()->GetResolution();

	// 미니맵 UI 추가
	qMinimap_boss1* pMinimap_boss1 = new qMinimap_boss1;
	m_Minimap = qAssetMgr::GetInst()->FindTexture(L"minimap_boss1");

	pMinimap_boss1->SetImage(m_Minimap);
	pMinimap_boss1->SetScale(Vec2(158.f, 145.f));

	//pMinimap_stage1->SetPos(Vec2(vResol.x - (pMinimap_stage1->GetScale().x + 30), 30.f));

	pMinimap_boss1->SetPos(Vec2(0.f, 0.f));

	AddObject(LAYER_TYPE::UI, pMinimap_boss1);


	// 메뉴 UI 추가
	qMenu* pMenu = new qMenu;
	m_Menu = qAssetMgr::GetInst()->FindTexture(L"menu");

	pMenu->SetImage(m_Menu);
	pMenu->SetScale(Vec2(1600.f, 900.f));

	//pMinimap_stage1->SetPos(Vec2(vResol.x - (pMinimap_stage1->GetScale().x + 30), 30.f));

	pMenu->SetPos(Vec2(0.f, 0.f));

	AddObject(LAYER_TYPE::UI, pMenu);
	

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
	pPlayer->SetPos(223.f, 768.f);
	pPlayer->SetScale(100.0f, 100.0f);
	AddObject(LAYER_TYPE::PLAYER, pPlayer);


	// 플랫폼 생성
	//qObj* pPlatform = new qPlatform;
	//pPlatform->SetName(L"Platform");
	//pPlatform->SetPos(Vec2(640.f, 700.f));
	//AddObject(LAYER_TYPE::PLATFORM, pPlatform);


	// 콜라이더 읽어오기
	LoadPlatform(L"platform\\platform.dat");
	LoadRope(L"rope\\rope.dat");
	LoadPortal(L"portal\\portal.dat");

	LoadMonster_blue(L"monster_blue\\monster_blue.dat");
	LoadMonster_red(L"monster_red\\monster_red.dat");

	// 레벨 충돌 설정하기
	qCollisionMgr::GetInst()->CollisionCheckClear();

	qCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::PLATFORM);
	qCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::ROPE);
	qCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::PORTAL);

	qCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::MONSTER_BLUE, LAYER_TYPE::PLATFORM);
	qCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::MONSTER_RED, LAYER_TYPE::PLATFORM);
}

void qLevel_boss1::Exit()
{

	pSound->SetVolume(30.f);
	pSound->Stop();

	// 레벨에 있는 모든 오브젝트 삭제한다.
	DeleteAllObjects();
}
