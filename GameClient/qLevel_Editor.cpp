#include "pch.h"
#include "qLevel_Editor.h"

#include "qKeyMgr.h"
#include "qTile.h"

qLevel_Editor::qLevel_Editor()
	: m_EditTile(nullptr)
{
}

qLevel_Editor::~qLevel_Editor()
{
}

void qLevel_Editor::begin()
{
	qLevel::begin();
}

void qLevel_Editor::tick()
{
	qLevel::tick();

	// 마우스 클릭 발생 시, 타일 오브젝트에게 알림
	if (KEY_TAP(KEY::LBTN))
	{
		m_EditTile->Clicked(qKeyMgr::GetInst()->GetMousePos());
	}


	if (KEY_TAP(KEY::ENTER))
	{
		ChangeLevel(LEVEL_TYPE::STAGE_01);
	}
}

void qLevel_Editor::Enter()
{
	m_EditTile = new qTile;
	m_EditTile->SetPos(Vec2(100.f, 100.f));

	m_EditTile->SetRowCol(10, 10);
	m_EditTile->SetAtlasTex(qAssetMgr::GetInst()->LoadTexture(L"texture\\TILE.bmp", L"texture\\TILE.bmp"));

	AddObject(LAYER_TYPE::TILE, m_EditTile);
}

void qLevel_Editor::Exit()
{
	DeleteAllObjects();
}
