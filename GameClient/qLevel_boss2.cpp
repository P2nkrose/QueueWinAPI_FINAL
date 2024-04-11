#include "pch.h"
#include "qLevel_boss2.h"
#include "qCollisionMgr.h"
#include "qPlayer.h"

#include "qPlatform.h"
#include "qRope.h"
#include "qPortal.h"
#include "qMonster_red.h"
#include "qMonster_blue.h"

#include "qBackground_boss2.h"
#include "qMinimap_boss2.h"
#include "qMenu.h"

#include "qBoss.h"
#include "qBossHUD.h"
#include "qBossHP.h"
#include "qPlayerHP.h"

#include "qSound.h"

qLevel_boss2::qLevel_boss2()
{
	SetName(L"Boss2");
}

qLevel_boss2::~qLevel_boss2()
{
}

void qLevel_boss2::begin()
{
	qLevel::begin();

	pSound = qAssetMgr::GetInst()->LoadSound(L"BGM_START", L"sound\\level\\boss2.wav");
	pSound->SetVolume(30.f);
	pSound->Play();

	qCamera::GetInst()->SetCameraEffect(CAM_EFFECT::FADE_IN, 0.7f);
}

void qLevel_boss2::tick()
{
	qLevel::tick();

	if (KEY_TAP(KEY::ENTER))
	{
		ChangeLevel(LEVEL_TYPE::EDITOR);
	}

	if (KEY_TAP(KEY::Z))
	{
		::ChangeLevel(LEVEL_TYPE::STAGE_01);
	}

	if (KEY_TAP(KEY::X))
	{
		::ChangeLevel(LEVEL_TYPE::STAGE_02);
	}

	if (KEY_TAP(KEY::C))
	{
		::ChangeLevel(LEVEL_TYPE::BOSS_01);
	}






}

void qLevel_boss2::Enter()
{

	// UI 추가
	// 화면 해상도
	Vec2 vResol = qEngine::GetInst()->GetResolution();


	// 미니맵 UI 추가
	qMinimap_boss2* pMinimap_boss2 = new qMinimap_boss2;
	m_Minimap = qAssetMgr::GetInst()->FindTexture(L"minimap_boss2");

	pMinimap_boss2->SetImage(m_Minimap);
	pMinimap_boss2->SetScale(Vec2(158.f, 130.f));

	//pMinimap_stage1->SetPos(Vec2(vResol.x - (pMinimap_stage1->GetScale().x + 30), 30.f));

	pMinimap_boss2->SetPos(Vec2(0.f, 0.f));

	AddObject(LAYER_TYPE::UI, pMinimap_boss2);
	

	// 메뉴 UI 추가
	qMenu* pMenu = new qMenu;
	m_Menu = qAssetMgr::GetInst()->FindTexture(L"menuno");

	pMenu->SetImage(m_Menu);
	pMenu->SetScale(Vec2(1600.f, 900.f));

	//pMinimap_stage1->SetPos(Vec2(vResol.x - (pMinimap_stage1->GetScale().x + 30), 30.f));

	pMenu->SetPos(Vec2(0.f, 0.f));

	AddObject(LAYER_TYPE::UI, pMenu);





	// 레벨에 오브젝트 추가
	//
	// Background
	qObj* pBack = new qBackground_boss2;
	pBack->SetName(L"Boss2");
	pBack->SetPos(0.f, 0.f);
	AddObject(LAYER_TYPE::BACKGROUND, pBack);

	// Player
	qObj* pPlayer = new qPlayer;
	pPlayer->SetName(L"Player");
	pPlayer->SetPos(156.f, 755.f);
	pPlayer->SetScale(100.0f, 100.0f);
	AddObject(LAYER_TYPE::PLAYER, pPlayer);

	// Boss
	qObj* pBoss = new qBoss;
	pBoss->SetName(L"Boss");
	pBoss->SetPos(910.f, 693.f);
	pBoss->SetScale(100.f, 100.f);
	pBoss->SetDir(DIRECTION::LEFT);
	
	AddObject(LAYER_TYPE::BOSS, pBoss);


	// 보스 HUD
	qBossHUD* pBossHud = new qBossHUD;
	m_BossHud = qAssetMgr::GetInst()->FindTexture(L"hud");

	pBossHud->SetImage(m_BossHud);
	pBossHud->SetScale(Vec2(801.f, 40.f));

	//pBossHud->SetPos(Vec2(vResol.x - (pBossHud->GetScale().x + 800), 500.f));
	pBossHud->SetPos(Vec2(400.f, 0.f));

	AddObject(LAYER_TYPE::UI, pBossHud);


	// 보스 HP
	qBossHP* pBossHP = new qBossHP;
	m_BossHp = qAssetMgr::GetInst()->FindTexture(L"hp");

	pBossHP->SetImage(m_BossHp);
	pBossHP->SetScale(Vec2(801.f, 40.f));
	pBossHP->SetPos(Vec2(439.f, 4.f));
	pBossHP->SetOwner(pBoss);

	AddObject(LAYER_TYPE::UI, pBossHP);


	// 플레이어 Hp
	qPlayerHP* pPlayerHP = new qPlayerHP;
	m_PlayerHP = qAssetMgr::GetInst()->FindTexture(L"playerhp");

	pPlayerHP->SetImage(m_PlayerHP);
	pPlayerHP->SetScale(Vec2(169.f, 11.f));
	pPlayerHP->SetPos(Vec2(719.f, 843.f));
	pPlayerHP->SetOwner(pPlayer);

	AddObject(LAYER_TYPE::UI, pPlayerHP);
	


	// 콜라이더 읽어오기
	LoadPlatform(L"platform\\platform.dat");
	LoadRope(L"rope\\rope.dat");
	LoadPortal(L"portal\\portal.dat");

	LoadMonster_blue(L"monster_blue\\monster_blue.dat");
	LoadMonster_red(L"monster_red\\monster_red.dat");


	// 레벨 충돌 설정하기
	qCollisionMgr::GetInst()->CollisionCheckClear();
	qCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::MONSTER_BLUE);
	qCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::MONSTER_RED);

	qCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::BOSS);
	qCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER_SKILL, LAYER_TYPE::BOSS);

	qCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::PLATFORM);
	qCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::BOSS, LAYER_TYPE::PLATFORM);

	qCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::BOSS_SKILL);
	qCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::PORTAL);

	
}

void qLevel_boss2::Exit()
{

	pSound->SetVolume(30.f);
	pSound->Stop();

	// 레벨에 있는 모든 오브젝트 삭제한다.
	DeleteAllObjects();
}
