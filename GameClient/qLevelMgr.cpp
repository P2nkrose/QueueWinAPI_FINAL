#include "pch.h"
#include "qLevelMgr.h"

#include "qCollisionMgr.h"

#include "qLevel.h"
#include "qLevel_Stage01.h"

#include "qPlayer.h"
#include "qMonster.h"

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
	pObject->SetPos(640.0f, 384.0f);
	pObject->SetScale(100.0f, 100.0f);
	m_pCurrentLevel->AddObject(LAYER_TYPE::PLAYER, pObject);


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


	// ���� �浹 �����ϱ�
	qCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::MONSTER);
	qCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER_MISSILE, LAYER_TYPE::MONSTER);

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
