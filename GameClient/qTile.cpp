#include "pch.h"
#include "qTile.h"

#include "qTileMap.h"

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
