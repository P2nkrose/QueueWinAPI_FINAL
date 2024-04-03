#include "pch.h"
#include "qLevel_Editor.h"
#include "qKeyMgr.h"
#include "qTile.h"
#include "qPathMgr.h"
#include "qPlatform.h"
#include "qRope.h"
#include "qPortal.h"
#include "qCollider.h"
#include "qTexture.h"
#include "qAnimation.h"
#include "qAnimator.h"

#include "qMonster_red.h"
#include "qMonster_blue.h"
#include "qDummy_blue.h"
#include "qDummy_red.h"

#include "qBackground_stage1.h"
#include "qBackground_stage2.h"
#include "qBackground_boss1.h"
#include "qBackground_boss2.h"

#include "qLevel_stage1.h"
#include "qLevel_stage2.h"
#include "qLevel_boss1.h"
#include "qLevel_boss2.h"

#include "qUI.h"
#include "qButton.h"

qLevel_Editor::qLevel_Editor()
	: m_EditTile(nullptr)
	, m_Type(EDIT_TYPE::END)
	, m_CurImg(nullptr)
	, m_Background(nullptr)
{
	SetName(L"Editor");
	
}

qLevel_Editor::~qLevel_Editor()
{
}

void qLevel_Editor::begin()
{
	qLevel::begin();

	//m_CurImg = qAssetMgr::GetInst()->LoadTexture(L"edit", L"texture\\edit\\edit1.png");

}

void qLevel_Editor::tick()
{
	qLevel::tick();

	if (KEY_TAP(KEY::_1))
	{
		MessageBox(qEngine::GetInst()->GetMainWnd(), L"스테이지 1 설정", L"STAGE", MB_OK);
		m_CurImg = qAssetMgr::GetInst()->LoadTexture(L"stage1", L"texture\\map\\stage1.png");
		m_CurImg->SetName(L"Stage1");

		SetStageName(STAGE_NAME::STAGE1);
	}
	else if (KEY_TAP(KEY::_2))
	{
		MessageBox(qEngine::GetInst()->GetMainWnd(), L"스테이지 2 설정", L"STAGE", MB_OK);
		m_CurImg = qAssetMgr::GetInst()->LoadTexture(L"stage2", L"texture\\map\\stage2.png");
		m_CurImg->SetName(L"Stage2");

		SetStageName(STAGE_NAME::STAGE2);
	}
	else if (KEY_TAP(KEY::_3))
	{
		MessageBox(qEngine::GetInst()->GetMainWnd(), L"보스 스테이지 1 설정", L"STAGE", MB_OK);
		m_CurImg = qAssetMgr::GetInst()->LoadTexture(L"boss1", L"texture\\map\\boss1.png");
		m_CurImg->SetName(L"Boss1");

		SetStageName(STAGE_NAME::BOSS1);
	}
	else if (KEY_TAP(KEY::_4))
	{
		MessageBox(qEngine::GetInst()->GetMainWnd(), L"보스 스테이지 2 설정", L"STAGE", MB_OK);
		m_CurImg = qAssetMgr::GetInst()->LoadTexture(L"boss2", L"texture\\map\\boss2.png");
		m_CurImg->SetName(L"Boss2");

		SetStageName(STAGE_NAME::BOSS2);
	}

	// SetType 후 edit MessageBox
	if (KEY_TAP(KEY::I))
	{
		SetType(EDIT_TYPE::PLATFORM);
		ResetInfo();
		MessageBox(qEngine::GetInst()->GetMainWnd(), L"PLATFORM EDIT", L"EDITOR TOOL", MB_OK);
	}
	if (KEY_TAP(KEY::O))
	{
		SetType(EDIT_TYPE::ROPE);
		ResetInfo();
		MessageBox(qEngine::GetInst()->GetMainWnd(), L"ROPE EDIT", L"EDITOR TOOL", MB_OK);
	}
	if (KEY_TAP(KEY::P))
	{
		SetType(EDIT_TYPE::PORTAL);
		ResetInfo();
		MessageBox(qEngine::GetInst()->GetMainWnd(), L"PORTAL EDIT", L"EDITOR TOOL", MB_OK);
	}
	else if (KEY_TAP(KEY::K))
	{
		SetType(EDIT_TYPE::DUMMY_BLUE);
		ResetInfo();
		MessageBox(qEngine::GetInst()->GetMainWnd(), L"MONSTER BLUE EDIT", L"EDITOR TOOL", MB_OK);
	}
	else if (KEY_TAP(KEY::L))
	{
		SetType(EDIT_TYPE::DUMMY_RED);
		ResetInfo();
		MessageBox(qEngine::GetInst()->GetMainWnd(), L"MONSTER RED EDIT", L"EDITOR TOOL", MB_OK);
	}

	
	// 사용할 Type 으로 변경
	if (EDIT_TYPE::PLATFORM == GetType())
	{
		Platform();
	}
	else if (EDIT_TYPE::ROPE == GetType())
	{
		Rope();
	}
	else if (EDIT_TYPE::PORTAL == GetType())
	{
		Portal();
	}
	else if (EDIT_TYPE::DUMMY_BLUE == GetType())
	{
		Monster_blue();
	}
	else if (EDIT_TYPE::DUMMY_RED == GetType())
	{
		Monster_red();
	}

	// 그린 Edit 저장
	if (KEY_TAP(KEY::_9))
	{
		SavePlatform(L"platform\\platform.dat");
		SaveRope(L"rope\\rope.dat");
		SavePortal(L"portal\\portal.dat");
		SaveMonster_blue(L"monster_blue\\monster_blue.dat");	
		SaveMonster_red(L"monster_red\\monster_red.dat");	
		MessageBox(qEngine::GetInst()->GetMainWnd(), L"저장 완료", L"EDITOR", MB_OK);
	}

	// 저장되어있는 Edit 불러오기
	else if (KEY_TAP(KEY::_0))
	{
		LoadPlatform(L"platform\\platform.dat");
		LoadRope(L"rope\\rope.dat");
		LoadPortal(L"portal\\portal.dat");
		LoadMonster_blue(L"monster_blue\\monster_blue.dat");
		LoadMonster_red(L"monster_red\\monster_red.dat");
		
		MessageBox(qEngine::GetInst()->GetMainWnd(), L"로딩 완료", L"EDITOR", MB_OK);
	}


	if (KEY_TAP(KEY::Z))
	{
		ChangeLevel(LEVEL_TYPE::STAGE_01);
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

void qLevel_Editor::Enter()
{
	qCamera::GetInst()->SetOwner(nullptr);
	

}

void qLevel_Editor::Exit()
{
	DeleteAllObjects();
}

void qLevel_Editor::Platform()
{

	if (KEY_TAP(KEY::LBTN))
	{
		m_tInfo.StartPos = qCamera::GetInst()->GetRealPos(qKeyMgr::GetInst()->GetMousePos());
	}
	else if (KEY_PRESSED(KEY::LBTN))
	{
		m_tInfo.EndPos = qCamera::GetInst()->GetRealPos(qKeyMgr::GetInst()->GetMousePos());
	}
	else if (KEY_RELEASED(KEY::LBTN))
	{
		m_tInfo.EndPos = qCamera::GetInst()->GetRealPos(qKeyMgr::GetInst()->GetMousePos());
		float x = abs((m_tInfo.StartPos.x + m_tInfo.EndPos.x) * 0.5f);
		float y = abs((m_tInfo.StartPos.y + m_tInfo.EndPos.y) * 0.5f);

		float width = abs(m_tInfo.EndPos.x - m_tInfo.StartPos.x);
		float height = abs(m_tInfo.EndPos.y - m_tInfo.StartPos.y);

		qPlatform* pPlatform = new qPlatform(Vec2(x, y), Vec2(width, height));
 		AddObject(LAYER_TYPE::PLATFORM, pPlatform);

		memset(&m_tInfo, 0, sizeof(tInfo));
	}
}

void qLevel_Editor::Rope()
{
	if (KEY_TAP(KEY::LBTN))
	{
		m_tInfo.StartPos = qCamera::GetInst()->GetRealPos(qKeyMgr::GetInst()->GetMousePos());
	}
	else if (KEY_PRESSED(KEY::LBTN))
	{
		m_tInfo.EndPos = qCamera::GetInst()->GetRealPos(qKeyMgr::GetInst()->GetMousePos());
	}
	else if (KEY_RELEASED(KEY::LBTN))
	{
		m_tInfo.EndPos = qCamera::GetInst()->GetRealPos(qKeyMgr::GetInst()->GetMousePos());
		float x = abs((m_tInfo.StartPos.x + m_tInfo.EndPos.x) * 0.5f);
		float y = abs((m_tInfo.StartPos.y + m_tInfo.EndPos.y) * 0.5f);

		float width = abs(m_tInfo.EndPos.x - m_tInfo.StartPos.x);
		float height = abs(m_tInfo.EndPos.y - m_tInfo.StartPos.y);

		qRope* pRope = new qRope(Vec2(x, y), Vec2(width, height));
		pRope->SetName(L"Rope");
		AddObject(LAYER_TYPE::ROPE, pRope);

		memset(&m_tInfo, 0, sizeof(tInfo));
	}
}

void qLevel_Editor::Portal()
{
	if (KEY_TAP(KEY::LBTN))
	{
		m_tInfo.StartPos = qCamera::GetInst()->GetRealPos(qKeyMgr::GetInst()->GetMousePos());
	}
	else if (KEY_PRESSED(KEY::LBTN))
	{
		m_tInfo.EndPos = qCamera::GetInst()->GetRealPos(qKeyMgr::GetInst()->GetMousePos());
	}
	else if (KEY_RELEASED(KEY::LBTN))
	{
		m_tInfo.EndPos = qCamera::GetInst()->GetRealPos(qKeyMgr::GetInst()->GetMousePos());
		float x = abs((m_tInfo.StartPos.x + m_tInfo.EndPos.x) * 0.5f);
		float y = abs((m_tInfo.StartPos.y + m_tInfo.EndPos.y) * 0.5f);

		float width = abs(m_tInfo.EndPos.x - m_tInfo.StartPos.x);
		float height = abs(m_tInfo.EndPos.y - m_tInfo.StartPos.y);

		qPortal* pPortal = new qPortal(Vec2(x, y), Vec2(width, height));
		AddObject(LAYER_TYPE::PORTAL, pPortal);

		memset(&m_tInfo, 0, sizeof(tInfo));
	}
}

void qLevel_Editor::Monster_blue()
{
	if (KEY_TAP(KEY::LBTN))
	{
		Vec2 vPos = qCamera::GetInst()->GetRealPos(qKeyMgr::GetInst()->GetMousePos());
		qDummy_blue* pMonster = new qDummy_blue;
		pMonster->SetPos(vPos);
		pMonster->SetScale(100.f, 100.f);
		pMonster->SetName(L"Blue");

		AddObject(LAYER_TYPE::DUMMY_BLUE, pMonster);

	}
}

void qLevel_Editor::Monster_red()
{
	if (KEY_TAP(KEY::LBTN))
	{
		Vec2 vPos = qCamera::GetInst()->GetRealPos(qKeyMgr::GetInst()->GetMousePos());
		qDummy_red* pMonster = new qDummy_red;
		pMonster->SetPos(vPos);
		pMonster->SetScale(100.f, 100.f);
		pMonster->SetName(L"Red");

		AddObject(LAYER_TYPE::DUMMY_RED, pMonster);
	}
}


void qLevel_Editor::render()
{

	// Rendering
	if (nullptr == m_CurImg)
		return;
		
	Vec2 vPos = qCamera::GetInst()->GetRenderPos(GetPos());


	StretchBlt(DC, vPos.x, vPos.y
		, m_CurImg->GetWidth(), m_CurImg->GetHeight()
		, m_CurImg->GetDC()
		, 0, 0
		, m_CurImg->GetWidth(), m_CurImg->GetHeight(), SRCCOPY);

	//m_BlueImg = qAssetMgr::GetInst()->LoadTexture(L"monster_blue", L"texture\\edit\\monster_blue.png");

	//Vec2 vMousePos = qCamera::GetInst()->GetRenderPos(qKeyMgr::GetInst()->GetMousePos());

	

	if (m_Type == EDIT_TYPE::PLATFORM || m_Type == EDIT_TYPE::ROPE || m_Type == EDIT_TYPE::PORTAL)
	{
		USE_PEN(DC, PEN_TYPE::PEN_GREEN);
		USE_BRUSH(DC, BRUSH_TYPE::BRUSH_HOLLOW);

		Vec2 Start = qCamera::GetInst()->GetRenderPos(m_tInfo.StartPos);
		Vec2 End = qCamera::GetInst()->GetRenderPos(m_tInfo.EndPos);

		Rectangle(DC, Start.x, Start.y, End.x, End.y);
	}

	

	qLevel::render();
}




