#include "pch.h"
#include "qLevelMgr.h"

#include "qLevel.h"
#include "qLevel_Stage01.h"

#include "qPlayer.h"

qLevelMgr::qLevelMgr()
	: m_arrLevel{}
	, m_pCurrentLevel(nullptr)
{

}


qLevelMgr::~qLevelMgr()
{

}


void qLevelMgr::init()
{
	// 모든 레벨 생성
	m_arrLevel[(UINT)LEVEL_TYPE::STAGE_01] = new qLevel_Stage01;

	// 현재 레벨 지정
	m_pCurrentLevel = m_arrLevel[(UINT)LEVEL_TYPE::STAGE_01];

	// 레벨에 물체 추가하기
	qObj* pObject = new qPlayer;
	pObject->SetPos(640.0f, 384.0f);
	pObject->SetScale(100.0f, 100.0f);

	m_pCurrentLevel->AddObject(pObject);
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
