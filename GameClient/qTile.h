#pragma once
#include "qObj.h"

class qTileMap;

class qTile : public qObj
{
public:
	CLONE(qTile);

public:
	qTile();
	~qTile();

private:
	virtual void begin() override;
	virtual void tick() override;
	virtual void render() override;

public:
	void SetRow(UINT _Row);
	void SetCol(UINT _Col);
	void SetRowCol(UINT _Row, UINT _Col);
	void SetAtlasTex(qTexture* _Atlas);


	void Clicked(Vec2 _vMousePos);


private:
	qTileMap*	m_TileMap;


};

