#include "pch.h"
#include "qLevel_stage1.h"

#include "qKeyMgr.h"
#include "qForce.h"

#include "qLevelMgr.h"
#include "qCollisionMgr.h"
#include "qPlayer.h"

#include "qMinimap_stage1.h"
#include "qMenu.h"
#include "qAssetMgr.h"

#include "qPlatform.h"
#include "qRope.h"
#include "qPortal.h"
#include "qMonster_red.h"
#include "qMonster_blue.h"
#include "qBackground_stage1.h"

#include "qSound.h"

qLevel_stage1::qLevel_stage1()
{
	SetName(L"Stage1");
}

qLevel_stage1::~qLevel_stage1()
{
}

void qLevel_stage1::begin()
{
	qLevel::begin();

	pSound = qAssetMgr::GetInst()->LoadSound(L"BGM_START", L"sound\\level\\stage1.wav");
	pSound->SetVolume(30.f);
	pSound->Play();

	// 페이드 인 페이드 아웃
	qCamera::GetInst()->SetCameraEffect(CAM_EFFECT::FADE_IN, 0.7f);
	//qCamera::GetInst()->SetCameraEffect(CAM_EFFECT::FADE_OUT, 1.f);


}

void qLevel_stage1::tick()
{
	qLevel::tick();

	//if (KEY_TAP(KEY::LBTN))
	//{
	//	Vec2 vMousePos = qKeyMgr::GetInst()->GetMousePos();
	//	Vec2 vPos = qCamera::GetInst()->GetRenderPos(vMousePos);

	//	qForce* pForce = new qForce();
	//	pForce->SetPos(vPos);
	//	pForce->SetForce(1000.f, 500.f, 2.f);
	//	SpawnObject(this, LAYER_TYPE::FORCE, pForce);
	//}

	if (KEY_TAP(KEY::ENTER))
	{
		ChangeLevel(LEVEL_TYPE::EDITOR);
	}

	if (KEY_TAP(KEY::X))
	{
		ChangeLevel(LEVEL_TYPE::STAGE_02);
	}

	if (KEY_TAP(KEY::C))
	{
		ChangeLevel(LEVEL_TYPE::BOSS_01);
	}

	if (KEY_TAP(KEY::V))
	{
		ChangeLevel(LEVEL_TYPE::BOSS_02);
	}
}

void qLevel_stage1::Enter()
{
	// UI 추가
	// 화면 해상도
	Vec2 vResol = qEngine::GetInst()->GetResolution();


	// 미니맵 UI 추가
	qMinimap_stage1* pMinimap_stage1 = new qMinimap_stage1;
	m_Minimap = qAssetMgr::GetInst()->FindTexture(L"minimap_stage1");

	pMinimap_stage1->SetImage(m_Minimap);
	pMinimap_stage1->SetScale(Vec2(214.f, 142.f));

	//pMinimap_stage1->SetPos(Vec2(vResol.x - (pMinimap_stage1->GetScale().x + 30), 30.f));

	pMinimap_stage1->SetPos(Vec2(0.f, 0.f));

	AddObject(LAYER_TYPE::UI, pMinimap_stage1);


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
	qObj* pBack = new qBackground_stage1;
	pBack->SetName(L"Stage1");
	pBack->SetPos(0.0f, 0.f);
	AddObject(LAYER_TYPE::BACKGROUND, pBack);
	

	// Player
	qObj* pObject = new qPlayer;
	pObject->SetName(L"Player");
	pObject->SetPos(1342.f, 744.f);
	pObject->SetScale(100.0f, 100.0f);
	AddObject(LAYER_TYPE::PLAYER, pObject);


	// 플레이어 클론
	//qObj* pPlayerClone = pObject->Clone();
	//pPlayerClone->SetPos(800.f, 400.f);
	//m_pCurrentLevel->AddObject(LAYER_TYPE::PLAYER, pPlayerClone);


	// 콜라이더 읽어오기
	LoadPlatform(L"platform\\platform.dat");
	LoadRope(L"rope\\rope.dat");
	LoadPortal(L"portal\\portal.dat");

	LoadMonster_blue(L"monster_blue\\monster_blue.dat");
	LoadMonster_red(L"monster_red\\monster_red.dat");



	// 레벨 충돌 설정하기
	qCollisionMgr::GetInst()->CollisionCheckClear();

	qCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::PLATFORM);
	qCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::MONSTER_BLUE, LAYER_TYPE::PLATFORM);
	qCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::MONSTER_RED, LAYER_TYPE::PLATFORM);

	qCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::ROPE);
	qCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::PORTAL);


	
}

void qLevel_stage1::Exit()
{
	

	pSound->SetVolume(30.f);
	pSound->Stop();

	// 레벨에 있는 모든 오브젝트 삭제한다.
	DeleteAllObjects();

	//qCamera::GetInst()->SetCameraEffect(CAM_EFFECT::FADE_OUT, 1.f);
}
