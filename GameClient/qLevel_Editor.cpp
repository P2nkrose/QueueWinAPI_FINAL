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
#include "qMonster.h"

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

	//m_CurImg = qAssetMgr::GetInst()->LoadTexture(L"stage1", L"texture\\edit\\edit.png");

}

void qLevel_Editor::tick()
{
	qLevel::tick();

	if (KEY_TAP(KEY::_1))
	{
		MessageBox(qEngine::GetInst()->GetMainWnd(), L"�������� 1 ����", L"STAGE", MB_OK);
		m_CurImg = qAssetMgr::GetInst()->LoadTexture(L"stage1", L"texture\\map\\stage1.png");
		m_CurImg->SetName(L"Stage1");


		SetStageName(STAGE_NAME::STAGE1);
	}
	else if (KEY_TAP(KEY::_2))
	{
		MessageBox(qEngine::GetInst()->GetMainWnd(), L"�������� 2 ����", L"STAGE", MB_OK);
		m_CurImg = qAssetMgr::GetInst()->LoadTexture(L"stage2", L"texture\\map\\stage2.png");
		m_CurImg->SetName(L"Stage2");
		SetStageName(STAGE_NAME::STAGE2);
	}
	else if (KEY_TAP(KEY::_3))
	{
		MessageBox(qEngine::GetInst()->GetMainWnd(), L"���� �������� 1 ����", L"STAGE", MB_OK);
		m_CurImg = qAssetMgr::GetInst()->LoadTexture(L"boss1", L"texture\\map\\boss1.png");
		m_CurImg->SetName(L"Boss1");

		SetStageName(STAGE_NAME::BOSS1);
	}
	else if (KEY_TAP(KEY::_4))
	{
		MessageBox(qEngine::GetInst()->GetMainWnd(), L"���� �������� 2 ����", L"STAGE", MB_OK);
		m_CurImg = qAssetMgr::GetInst()->LoadTexture(L"boss2", L"texture\\map\\boss2.png");
		m_CurImg->SetName(L"Boss2");

		SetStageName(STAGE_NAME::BOSS2);
	}

	// SetType �� edit MessageBox
	if (KEY_TAP(KEY::U))
	{
		SetType(EDIT_TYPE::PLATFORM);
		ResetInfo();
		MessageBox(qEngine::GetInst()->GetMainWnd(), L"PLATFORM EDIT", L"EDITOR TOOL", MB_OK);
	}
	if (KEY_TAP(KEY::I))
	{
		SetType(EDIT_TYPE::ROPE);
		ResetInfo();
		MessageBox(qEngine::GetInst()->GetMainWnd(), L"ROPE EDIT", L"EDITOR TOOL", MB_OK);
	}
	if (KEY_TAP(KEY::O))
	{
		SetType(EDIT_TYPE::PORTAL);
		ResetInfo();
		MessageBox(qEngine::GetInst()->GetMainWnd(), L"PORTAL EDIT", L"EDITOR TOOL", MB_OK);
	}
	else if (KEY_TAP(KEY::P))
	{
		SetType(EDIT_TYPE::MONSTER);
		ResetInfo();
		MessageBox(qEngine::GetInst()->GetMainWnd(), L"MONSTER EDIT", L"EDITOR TOOL", MB_OK);
	}

	
	// ����� Type ���� ����
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
	else if (EDIT_TYPE::MONSTER == GetType())
	{
		Monster();
	}

	// �׸� Edit ����
	if (KEY_TAP(KEY::_9))
	{
		SavePlatform(L"platform\\platform.dat");
		SaveRope(L"rope\\rope.dat");
		SavePortal(L"portal\\portal.dat");
		SaveMonster(L"monster\\monster.dat");	
		MessageBox(qEngine::GetInst()->GetMainWnd(), L"Collider ���� �Ϸ�", L"EDITOR", MB_OK);
	}

	// ����Ǿ��ִ� Edit �ҷ�����
	else if (KEY_TAP(KEY::_0))
	{
	
			LoadPlatform(L"platform\\platform.dat");
		
			LoadRope(L"rope\\rope.dat");
		
			LoadPortal(L"portal\\portal.dat");
		
			LoadMonster(L"monster\\monster.dat");
		
		MessageBox(qEngine::GetInst()->GetMainWnd(), L"Collider �ε� �Ϸ�", L"EDITOR", MB_OK);
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


	////Background
	//qObj* pBack = new qBackground_stage1;
	//pBack->SetName(L"Stage1");
	//pBack->SetPos(0.0f, 0.f);
	//pBack->SetScale(1.3f, 1.3f);
	//AddObject(LAYER_TYPE::BACKGROUND, pBack);

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

void qLevel_Editor::Monster()
{
	if (KEY_TAP(KEY::LBTN))
	{
		Vec2 vPos = qCamera::GetInst()->GetRealPos(qKeyMgr::GetInst()->GetMousePos());
		qMonster* pMonster = new qMonster;
		pMonster->SetPos(vPos);
		pMonster->SetScale(100.f, 100.f);
		AddObject(LAYER_TYPE::MONSTER, pMonster);
	}
}

void qLevel_Editor::render()
{
	qLevel::render();
	// Rendering
	if (nullptr == m_CurImg)
		return;
	Vec2 vPos = qCamera::GetInst()->GetRenderPos(GetPos());

	StretchBlt(DC, vPos.x, vPos.y
		, m_CurImg->GetWidth(), m_CurImg->GetHeight()
		, m_CurImg->GetDC()
		, 0, 0
		, m_CurImg->GetWidth(), m_CurImg->GetHeight(), SRCCOPY);

	if (m_Type == EDIT_TYPE::PLATFORM || m_Type == EDIT_TYPE::ROPE || m_Type == EDIT_TYPE::PORTAL)
	{
		USE_PEN(DC, PEN_TYPE::PEN_GREEN);
		USE_BRUSH(DC, BRUSH_TYPE::BRUSH_HOLLOW);

		Vec2 Start = qCamera::GetInst()->GetRenderPos(m_tInfo.StartPos);
		Vec2 End = qCamera::GetInst()->GetRenderPos(m_tInfo.EndPos);

		Rectangle(DC, Start.x, Start.y, End.x, End.y);
	}

}




