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
	// ��� ���� ����

	m_arrLevel[(UINT)LEVEL_TYPE::LOGO] = new qLevel_Logo;
	m_arrLevel[(UINT)LEVEL_TYPE::START] = new qLevel_Start;
	m_arrLevel[(UINT)LEVEL_TYPE::EDITOR] = new qLevel_Editor;
	m_arrLevel[(UINT)LEVEL_TYPE::EDITOR]->SetPos(Vec2(0.f, 0.f));
	m_arrLevel[(UINT)LEVEL_TYPE::STAGE_01] = new qLevel_stage1;
	m_arrLevel[(UINT)LEVEL_TYPE::STAGE_02] = new qLevel_stage2;
	m_arrLevel[(UINT)LEVEL_TYPE::BOSS_01] = new qLevel_boss1;
	m_arrLevel[(UINT)LEVEL_TYPE::BOSS_02] = new qLevel_boss2;

	// ó�� ������ ���� 
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
		LOG(LOG_TYPE::DBG_ERROR, L"���� ������ �����Ϸ��� ������ �����մϴ�.");
		return;
	}

	// ���� �������� Exit �Ѵ�.
	if (m_pCurrentLevel)
		m_pCurrentLevel->Exit();

	// ���ο� ������ �������� �ּҰ��� ��ü�Ѵ�.
	m_pCurrentLevel = m_arrLevel[(UINT)_NextLevelType];
	assert(m_pCurrentLevel);

	// ����� ���ο� ������ Enter �Ѵ�.
	m_pCurrentLevel->Enter();
	m_pCurrentLevel->begin();
}
