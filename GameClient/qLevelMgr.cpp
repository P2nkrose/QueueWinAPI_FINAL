#include "pch.h"
#include "qLevelMgr.h"
#include "qCollisionMgr.h"

#include "qLevel.h"
#include "qLevel_Logo.h"
#include "qLevel_Start.h"
#include "qLevel_Editor.h"
#include "qLevel_stage1.h"
#include "qLevel_stage2.h"


#include "qLevel_boss1.h"
#include "qLevel_boss2.h"

#include "qPlayer.h"
#include "qMonster_red.h"
#include "qMonster_blue.h"

#include "qPlatform.h"
#include "qRope.h"
#include "qPortal.h"

qLevelMgr::qLevelMgr()
	: m_arrLevel{}
	, m_pCurrentLevel(nullptr)
{

}


qLevelMgr::~qLevelMgr()
{
	Safe_Del_Arr(m_arrLevel);
}



qObj* qLevelMgr::FindObjectByName(const wstring& _StrName)
{
	return m_pCurrentLevel->FindObjectByName(_StrName);
;}

void qLevelMgr::init()
{
	// 모든 레벨 생성

	m_arrLevel[(UINT)LEVEL_TYPE::LOGO] = new qLevel_Logo;
	m_arrLevel[(UINT)LEVEL_TYPE::START] = new qLevel_Start;
	m_arrLevel[(UINT)LEVEL_TYPE::EDITOR] = new qLevel_Editor;
	m_arrLevel[(UINT)LEVEL_TYPE::EDITOR]->SetPos(Vec2(0.f, 0.f));
	m_arrLevel[(UINT)LEVEL_TYPE::STAGE_01] = new qLevel_stage1;
	m_arrLevel[(UINT)LEVEL_TYPE::STAGE_02] = new qLevel_stage2;
	m_arrLevel[(UINT)LEVEL_TYPE::BOSS_01] = new qLevel_boss1;
	m_arrLevel[(UINT)LEVEL_TYPE::BOSS_02] = new qLevel_boss2;

	// 처음 시작할 레벨 
	::ChangeLevel(LEVEL_TYPE::LOGO);
	
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
	if (nullptr == m_pCurrentLevel)
		return;

	m_pCurrentLevel->render();
}


void qLevelMgr::ChangeLevel(LEVEL_TYPE _NextLevelType)
{
	if (m_arrLevel[(UINT)_NextLevelType] == m_pCurrentLevel)
	{
		LOG(LOG_TYPE::DBG_ERROR, L"현재 레벨과 변경하려는 레벨이 동일합니다.");
		return;
	}

	// 기존 레벨에서 Exit 한다.
	if (m_pCurrentLevel)
		m_pCurrentLevel->Exit();

	// 새로운 레벨로 포인터의 주소값을 교체한다.
	m_pCurrentLevel = m_arrLevel[(UINT)_NextLevelType];
	assert(m_pCurrentLevel);

	// 변경된 새로운 레벨로 Enter 한다.
	m_pCurrentLevel->Enter();
	m_pCurrentLevel->begin();
}
