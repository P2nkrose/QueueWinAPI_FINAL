#include "pch.h"
#include "qLevel_Editor.h"

#include "qKeyMgr.h"

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

}

void qLevel_Editor::Exit()
{
	DeleteAllObjects();
}
