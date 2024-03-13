#include "pch.h"
#include "qLevelMgr.h"

#include "qCollisionMgr.h"

#include "qLevel.h"
#include "qLogo.h"
#include "qStart.h"
#include "qLevel_Editor.h"
#include "qLevel_Stage01.h"
#include "qLevel_Stage02.h"

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



qObj* qLevelMgr::FindObjectByName(const wstring& _StrName)
{
	return m_pCurrentLevel->FindObjectByName(_StrName);
;}

void qLevelMgr::init()
{
	// ��� ���� ����

	m_arrLevel[(UINT)LEVEL_TYPE::START] = new qStart;
	m_arrLevel[(UINT)LEVEL_TYPE::EDITOR] = new qLevel_Editor;
	m_arrLevel[(UINT)LEVEL_TYPE::STAGE_01] = new qLevel_Stage01;

	// ó�� ������ ����
	::ChangeLevel(LEVEL_TYPE::START);
	
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
