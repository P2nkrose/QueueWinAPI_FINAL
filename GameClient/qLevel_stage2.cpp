#include "pch.h"
#include "qLevel_stage2.h"

#include "qKeyMgr.h"
#include "qLevelMgr.h"

#include "qCollisionMgr.h"
#include "qPlayer.h"

#include "qMinimap_stage2.h"
#include "qMenu.h"
#include "qAssetMgr.h"

#include "qPlatform.h"
#include "qRope.h"
#include "qPortal.h"
#include "qMonster_red.h"
#include "qMonster_blue.h"

#include "qSpawner_blue1.h"
#include "qSpawner_blue2.h"
#include "qSpawner_blue3.h"
#include "qSpawner_red1.h"
#include "qSpawner_red2.h"

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

	pSound = qAssetMgr::GetInst()->LoadSound(L"BGM_START", L"sound\\level\\stage2.wav");
	pSound->SetVolume(30.f);
	pSound->Play();

	qCamera::GetInst()->SetCameraEffect(CAM_EFFECT::FADE_IN, 0.7f);
}

void qLevel_stage2::tick()
{
	qLevel::tick();

	wchar_t szBuff[256] = {};
	Vec2 vMousePos = qKeyMgr::GetInst()->GetMousePos();
	Vec2 vRenderPos = qCamera::GetInst()->GetRealPos(vMousePos);
	swprintf_s(szBuff, L"%f, %f", vRenderPos.x, vRenderPos.y);
	static float AccTime = 0.f;

	if (AccTime >= 1.f)
	{
		LOG(LOG_TYPE::DBG_WARNING, szBuff);
		AccTime = 0.f;
	}

	if (KEY_TAP(KEY::ENTER))
	{
		ChangeLevel(LEVEL_TYPE::EDITOR);
	}

	if (KEY_TAP(KEY::Z))
	{
		::ChangeLevel(LEVEL_TYPE::STAGE_01);
	}

	if (KEY_TAP(KEY::C))
	{
		::ChangeLevel(LEVEL_TYPE::BOSS_01);
	}

	if (KEY_TAP(KEY::V))
	{
		ChangeLevel(LEVEL_TYPE::BOSS_02);
	}
	


}

void qLevel_stage2::Enter()
{
	// UI 추가
	// 화면 해상도
	Vec2 vResol = qEngine::GetInst()->GetResolution();

	// 미니맵 UI 추가
	qMinimap_stage2* pMinimap_stage2 = new qMinimap_stage2;
	m_Minimap = qAssetMgr::GetInst()->FindTexture(L"minimap_stage2");

	pMinimap_stage2->SetImage(m_Minimap);
	pMinimap_stage2->SetScale(Vec2(147.f, 160.f));

	//pMinimap_stage1->SetPos(Vec2(vResol.x - (pMinimap_stage1->GetScale().x + 30), 30.f));

	pMinimap_stage2->SetPos(Vec2(0.f, 0.f));

	AddObject(LAYER_TYPE::UI, pMinimap_stage2);


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
	qObj* pBack = new qBackground_stage2;
	pBack->SetName(L"Stage2");
	pBack->SetPos(0.f, 0.f);
	AddObject(LAYER_TYPE::BACKGROUND, pBack);

	// Player
	qObj* pPlayer = new qPlayer;
	pPlayer->SetName(L"Player");
	pPlayer->SetPos(1821.f, 1454.f);
	pPlayer->SetScale(100.0f, 100.0f);
	AddObject(LAYER_TYPE::PLAYER, pPlayer);

	// 몬스터 블루1 (티구르) 생성
	qObj* pBlue1 = new qMonster_blue(DIRECTION::LEFT);
	pBlue1->SetName(L"Blue");
	pBlue1->SetPos(1377.f, 1448.f);
	pBlue1->SetScale(100.0f, 100.0f);
	AddObject(LAYER_TYPE::MONSTER_BLUE, pBlue1);
	
	qObj* pSpawnBlue1 = new qSpawner_blue1;
	pSpawnBlue1->SetOwner(pBlue1);
	AddObject(LAYER_TYPE::MONSTER_BLUE, pSpawnBlue1);
	
	// 몬스터 블루2 (티구르) 생성
	qObj* pBlue2 = new qMonster_blue(DIRECTION::RIGHT);
	pBlue2->SetName(L"Blue");
	pBlue2->SetPos(972.f, 1448.f);
	pBlue2->SetScale(100.0f, 100.0f);
	AddObject(LAYER_TYPE::MONSTER_BLUE, pBlue2);

	qObj* pSpawnBlue2 = new qSpawner_blue2;
	pSpawnBlue2->SetOwner(pBlue2);
	AddObject(LAYER_TYPE::MONSTER_BLUE, pSpawnBlue2);


	// 몬스터 블루3 (티구르) 생성
	qObj* pBlue3 = new qMonster_blue(DIRECTION::LEFT);
	pBlue3->SetName(L"Blue");
	pBlue3->SetPos(543.f, 1448.f);
	pBlue3->SetScale(100.0f, 100.0f);
	AddObject(LAYER_TYPE::MONSTER_BLUE, pBlue3);

	qObj* pSpawnBlue3 = new qSpawner_blue3;
	pSpawnBlue3->SetOwner(pBlue3);
	AddObject(LAYER_TYPE::MONSTER_BLUE, pSpawnBlue3);


	// 레드 몬스터(티루) 생성
	qObj* pRed1 = new qMonster_red(DIRECTION::LEFT);
	pRed1->SetName(L"Red");
	pRed1->SetPos(1336.f, 1093.f);
	pRed1->SetScale(100.0f, 100.0f);
	AddObject(LAYER_TYPE::MONSTER_RED, pRed1);

	qObj* pSpawnRed1 = new qSpawner_red1;
	pSpawnRed1->SetOwner(pRed1);
	AddObject(LAYER_TYPE::MONSTER_RED, pSpawnRed1);

	// 몬스터 생성
	qObj* pRed2 = new qMonster_red(DIRECTION::RIGHT);
	pRed2->SetName(L"Red");
	pRed2->SetPos(700.f, 1093.f);
	pRed2->SetScale(100.0f, 100.0f);
	AddObject(LAYER_TYPE::MONSTER_RED, pRed2);

	qObj* pSpawnRed2 = new qSpawner_red2;
	pSpawnRed2->SetOwner(pRed2);
	AddObject(LAYER_TYPE::MONSTER_RED, pSpawnRed2);




	// 콜라이더 읽어오기
	LoadPlatform(L"platform\\platform.dat");
	LoadRope(L"rope\\rope.dat");
	LoadPortal(L"portal\\portal.dat");

	//LoadMonster_blue(L"monster_blue\\monster_blue.dat");
	//LoadMonster_red(L"monster_red\\monster_red.dat");

	// 레벨 충돌 설정하기
	qCollisionMgr::GetInst()->CollisionCheckClear();
	qCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::MONSTER_BLUE);
	qCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::MONSTER_RED);

	qCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::PLATFORM);
	qCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::ROPE);
	qCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::PORTAL);

	qCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER_SKILL, LAYER_TYPE::MONSTER_BLUE);
	qCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER_SKILL, LAYER_TYPE::MONSTER_RED);

	qCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::MONSTER_BLUE, LAYER_TYPE::PLATFORM);
	qCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::MONSTER_RED, LAYER_TYPE::PLATFORM);

}

void qLevel_stage2::Exit()
{
	

	pSound->SetVolume(30.f);
	pSound->Stop();

	// 레벨에 있는 모든 오브젝트 삭제한다.
	DeleteAllObjects();

	//qCamera::GetInst()->SetCameraEffect(CAM_EFFECT::FADE_OUT, 1.f);
}


