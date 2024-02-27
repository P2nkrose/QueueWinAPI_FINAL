#include "pch.h"
#include "qLevelMgr.h"

#include "qCollisionMgr.h"

#include "qLevel.h"
#include "qLevel_Stage01.h"

#include "qPlayer.h"
#include "qMonster.h"
#include "qPlatform.h"

qLevelMgr::qLevelMgr()
	: m_arrLevel{}
	, m_pCurrentLevel(nullptr)
{

}


qLevelMgr::~qLevelMgr()
{
	Safe_Del_Arr(m_arrLevel);
}


void qLevelMgr::init()
{
	// ��� ���� ����
	m_arrLevel[(UINT)LEVEL_TYPE::STAGE_01] = new qLevel_Stage01;

	// ���� ���� ����
	m_pCurrentLevel = m_arrLevel[(UINT)LEVEL_TYPE::STAGE_01];

	// ������ ��ü �߰��ϱ�
	qObj* pObject = new qPlayer;
	pObject->SetName(L"Player");
	pObject->SetPos(640.0f, 384.0f);
	pObject->SetScale(100.0f, 100.0f);
	m_pCurrentLevel->AddObject(LAYER_TYPE::PLAYER, pObject);

	//qObj* pPlayerClone = pObject->Clone();
	//pPlayerClone->SetPos(800.f, 400.f);
	//m_pCurrentLevel->AddObject(LAYER_TYPE::PLAYER, pPlayerClone);


	// ������ ���� �߰��ϱ�
	pObject = new qMonster;
	pObject->SetName(L"Monster");
	pObject->SetPos(800.0f, 200.0f);
	pObject->SetScale(100.0f, 100.0f);
	m_pCurrentLevel->AddObject(LAYER_TYPE::MONSTER, pObject);
	
	// �Ѹ��� ��!
	pObject = new qMonster;
	pObject->SetName(L"Monster");
	pObject->SetPos(100.0f, 100.0f);
	pObject->SetScale(100.0f, 100.0f);
	m_pCurrentLevel->AddObject(LAYER_TYPE::MONSTER, pObject);

	// �÷��� ����
	pObject = new qPlatform;
	pObject->SetName(L"Platform");
	pObject->SetPos(Vec2(640.f, 700.f));
	m_pCurrentLevel->AddObject(LAYER_TYPE::PLATFORM, pObject);


	// ���� �浹 �����ϱ�
	qCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::MONSTER);
	qCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER_MISSILE, LAYER_TYPE::MONSTER);
	qCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::PLATFORM);
	
	// ���� ���� (�÷���)
	m_pCurrentLevel->begin();
}

void qLevelMgr::progress()
{
	if (nullptr == m_pCurrentLevel)
		return;

	m_pCurrentLevel->tick();
	m_pCurrentLevel->finaltick();

}

void qLevelMgr::render()
{
	m_pCurrentLevel->render();
}
