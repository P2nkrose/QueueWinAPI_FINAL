#include "pch.h"
#include "qLevel_Editor.h"

#include "qKeyMgr.h"
#include "qTile.h"

#include "qPathMgr.h"
#include "qPlatform.h"
#include "qCollider.h"
#include "qBackground_stage1.h"

#include "qUI.h"
#include "qButton.h"

qLevel_Editor::qLevel_Editor()
	: m_EditTile(nullptr)
{
	SetName(L"editor");
}

qLevel_Editor::~qLevel_Editor()
{
}

void qLevel_Editor::begin()
{
	qLevel::begin();

	qCamera::GetInst()->SetCameraEffect(CAM_EFFECT::FADE_IN, 0.7f);
}

void qLevel_Editor::tick()
{
	qLevel::tick();

	// 마우스 클릭 발생 시, 타일 오브젝트에게 알림
	//if (KEY_TAP(KEY::LBTN))
	//{
	//	m_EditTile->Clicked(qKeyMgr::GetInst()->GetMousePos());
	//}


	// 콜라이더 그리기
	if (KEY_TAP(KEY::LBTN))
	{
		m_TestPlatform = new qPlatform();
		m_Info.startPos = qCamera::GetInst()->GetRealPos(qKeyMgr::GetInst()->GetMousePos());
		m_TestInfo.startPos = qCamera::GetInst()->GetRealPos(qKeyMgr::GetInst()->GetMousePos());
		m_TestPlatform->SetPos(m_TestInfo.startPos);
		m_TestPlatform->SetName(L"Test");
		AddObject(LAYER_TYPE::PLATFORM, m_TestPlatform);

	}
	else if (KEY_PRESSED(KEY::LBTN))
	{
		m_TestInfo.EndPos = qCamera::GetInst()->GetRenderPos(qKeyMgr::GetInst()->GetMousePos());
		m_TestPlatform->SetScale(m_TestInfo.EndPos);
	}
	else if (KEY_RELEASED(KEY::LBTN))
	{
		m_TestPlatform->Destroy();
		m_Info.EndPos = qCamera::GetInst()->GetRealPos(qKeyMgr::GetInst()->GetMousePos());

		float x = (m_Info.startPos.x + m_Info.EndPos.x) * 0.5f;
		float y = (m_Info.startPos.y + m_Info.EndPos.y) * 0.5f;
		float width = fabs(m_Info.EndPos.x - m_Info.startPos.x);
		float height = fabs(m_Info.EndPos.y - m_Info.startPos.y);

		m_Platform = new qPlatform(Vec2(x, y), Vec2(width, height));
		m_vecEditPlat.push_back(m_Platform);
		AddObject(LAYER_TYPE::PLATFORM, m_Platform);
	}

	else if (KEY_TAP(KEY::O))
	{
		SaveToFile(L"platform\\platform.plat");
	}
	else if (KEY_TAP(KEY::P))
	{
		m_vecEditPlat.clear();
		LoadFromFile(L"platform\\platform.plat");
	}

	

	if (KEY_TAP(KEY::ENTER))
	{
		ChangeLevel(LEVEL_TYPE::STAGE_01);
	}
}

void qLevel_Editor::Enter()
{
	//m_EditTile = new qTile;
	//m_EditTile->SetPos(Vec2(100.f, 100.f));

	//m_EditTile->SetRowCol(10, 10);
	//m_EditTile->SetAtlasTex(qAssetMgr::GetInst()->LoadTexture(L"texture\\TILE.bmp", L"texture\\TILE.bmp"));

	//AddObject(LAYER_TYPE::TILE, m_EditTile);


	//Background
	qObj* pBack = new qBackground_stage1;
	pBack->SetName(L"Stage1");
	pBack->SetPos(0.0f, 0.f);
	pBack->SetScale(1.3f, 1.3f);
	AddObject(LAYER_TYPE::BACKGROUND, pBack);

}

void qLevel_Editor::Exit()
{
	DeleteAllObjects();
}


void qLevel_Editor::SaveToFile(const wstring& _strRelativePath)
{
	wstring strPath = qPathMgr::GetInst()->GetContentPath();
	strPath += _strRelativePath;

	FILE* pFile = nullptr;
	_wfopen_s(&pFile, strPath.c_str(), L"wb");

	size_t len = m_vecEditPlat.size();

	fwrite(&len, sizeof(size_t), 1, pFile);

	for (size_t i = 0; i < len; ++i)
	{
		Vec2 vPos = m_vecEditPlat[i]->GetPos();
		Vec2 vScale = m_vecEditPlat[i]->GetScale();
		fwrite(&vPos, sizeof(Vec2), 1, pFile);
		fwrite(&vScale, sizeof(Vec2), 1, pFile);
	}

	fclose(pFile);
}


