#include "pch.h"
#include "qLevel_Editor.h"

#include "qKeyMgr.h"
#include "qTile.h"

qLevel_Editor::qLevel_Editor()
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

	if (KEY_TAP(KEY::ENTER))
	{
		ChangeLevel(LEVEL_TYPE::STAGE_01);
	}
}

void qLevel_Editor::Enter()
{
	qObj* pTile = new qTile;
	AddObject(LAYER_TYPE::TILE, pTile);
}

void qLevel_Editor::Exit()
{
	DeleteAllObjects();
}
