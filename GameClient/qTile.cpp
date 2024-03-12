#include "pch.h"
#include "qTile.h"

#include "qTileMap.h"
#include "qPathMgr.h"

qTile::qTile()
{
	m_TileMap = (qTileMap*)AddComponent(new qTileMap);
}

qTile::~qTile()
{
}

void qTile::begin()
{
}

void qTile::tick()
{
}

void qTile::render()
{
	m_TileMap->render();
}

void qTile::SetRow(UINT _Row)
{
	m_TileMap->SetRow(_Row);
}

void qTile::SetCol(UINT _Col)
{
	m_TileMap->SetCol(_Col);
}

void qTile::SetRowCol(UINT _Row, UINT _Col)
{
	m_TileMap->SetRowCol(_Row, _Col);
}

void qTile::SetAtlasTex(qTexture* _Atlas)
{
	m_TileMap->SetAtlasTex(_Atlas);
}

void qTile::Clicked(Vec2 _vMousePos)
{
	m_TileMap->Clicked(_vMousePos);
}

//void qTile::SaveToFile(const wstring& _RelativePath)
//{
//	wstring strFilePath = qPathMgr::GetInst()->GetContentPath();
//	strFilePath += _RelativePath;
//
//	FILE* File = nullptr;
//	_wfopen_s(&File, strFilePath.c_str(), L"wb");
//
//	// 타일의 위치
//	Vec2 vPos = GetPos();
//	fwrite(&vPos, sizeof(Vec2), 1, File);
//
//	m_TileMap->SaveToFile(File);
//
//	fclose(File);
//}
//
//void qTile::LoadToFile(const wstring& _RelativePath)
//{
//	wstring strFilePath = qPathMgr::GetInst()->GetContentPath();
//	strFilePath += _RelativePath;
//
//	FILE* File = nullptr;
//	_wfopen_s(&File, strFilePath.c_str(), L"rb");
//
//	Vec2 vPos;
//	fread(&vPos, sizeof(Vec2), 1, File);
//	SetPos(vPos);
//
//	m_TileMap->LoadFromFile(File);
//
//	fclose(File);
//}
