#include "pch.h"
#include "qTile.h"

qTile::qTile()
{
	SetScale(Vec2(TILE_SIZE, TILE_SIZE));
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
	Vec2 vRenderPos = GetRenderPos();
	Vec2 vScale = GetScale();

	USE_PEN(DC, PEN_TYPE::PEN_GREEN);
	USE_BRUSH(DC, BRUSH_TYPE::BRUSH_HOLLOW);

	Rectangle(DC, (int)vRenderPos.x, (int)vRenderPos.y
		, (int)vRenderPos.x + (int)vScale.x, (int)vRenderPos.y + (int)vScale.y);
}
