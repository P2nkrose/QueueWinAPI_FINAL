#include "pch.h"
#include "qLevel_Stage01.h"

#include "qKeyMgr.h"
#include "qForce.h"

#include "qCollisionMgr.h"
#include "qPlayer.h"
#include "qMonster.h"
#include "qPlatform.h"
#include "qBackground.h"

qLevel_Stage01::qLevel_Stage01()
{
	SetName(L"stage1");
}

qLevel_Stage01::~qLevel_Stage01()
{
}

void qLevel_Stage01::begin()
{
	qLevel::begin();


	//qCamera::GetInst()->SetCameraEffect(CAM_EFFECT::FADE_IN, 2.f);
	//qCamera::GetInst()->SetCameraEffect(CAM_EFFECT::FADE_OUT, 2.f);
}

void qLevel_Stage01::tick()
{
	qLevel::tick();

	if (KEY_TAP(KEY::LBTN))
	{
		Vec2 vMousePos = qKeyMgr::GetInst()->GetMousePos();
		Vec2 vPos = qCamera::GetInst()->GetRenderPos(vMousePos);

		qForce* pForce = new qForce();
		pForce->SetPos(vPos);
		pForce->SetForce(1000.f, 500.f, 2.f);
		SpawnObject(this, LAYER_TYPE::FORCE, pForce);
	}

	if (KEY_TAP(KEY::ENTER))
	{
		ChangeLevel(LEVEL_TYPE::EDITOR);
	}
}

void qLevel_Stage01::Enter()
{
	// ������ ������Ʈ �߰�
	// 
	// Background
	qObj* pBack = new qBackground;
	pBack->SetName(L"Stage1");
	pBack->SetPos(0.0f, 420.f);
	pBack->SetScale(1.3f, 1.3f);
	AddObject(LAYER_TYPE::BACKGROUND, pBack);


	// Player
	qObj* pObject = new qPlayer;
	pObject->SetName(L"Player");
	pObject->SetPos(640.0f, 384.0f);
	pObject->SetScale(100.0f, 100.0f);
	AddObject(LAYER_TYPE::PLAYER, pObject);

	// �÷��̾� Ŭ��
	//qObj* pPlayerClone = pObject->Clone();
	//pPlayerClone->SetPos(800.f, 400.f);
	//m_pCurrentLevel->AddObject(LAYER_TYPE::PLAYER, pPlayerClone);


	//// ������ ���� �߰��ϱ�
	//pObject = new qMonster;
	//pObject->SetName(L"Monster");
	//pObject->SetPos(800.0f, 200.0f);
	//pObject->SetScale(100.0f, 100.0f);
	//AddObject(LAYER_TYPE::MONSTER, pObject);

	//// �Ѹ��� ��!
	//pObject = new qMonster;
	//pObject->SetName(L"Monster");
	//pObject->SetPos(100.0f, 100.0f);
	//pObject->SetScale(100.0f, 100.0f);
	//AddObject(LAYER_TYPE::MONSTER, pObject);

	// �÷��� ����
	pObject = new qPlatform;
	pObject->SetName(L"Platform");
	pObject->SetPos(Vec2(640.f, 700.f));
	AddObject(LAYER_TYPE::PLATFORM, pObject);

	// �ݶ��̴� �о����
	LoadFromFile(L"platform\\platform.plat");


	// ���� �浹 �����ϱ�
	qCollisionMgr::GetInst()->CollisionCheckClear();
	qCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::MONSTER);
	qCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER_MISSILE, LAYER_TYPE::MONSTER);
	qCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::PLATFORM);


	
}

void qLevel_Stage01::Exit()
{
	// ������ �ִ� ��� ������Ʈ �����Ѵ�.
	DeleteAllObjects();
}
