#pragma once
#include "qComponent.h"

struct tTileInfo
{
	int ImgIdx;

	tTileInfo()
		: ImgIdx(0)
	{}
};



class qTileMap : public qComponent
{
public:
	CLONE(qTileMap);

public:
	qTileMap();
	//qTileMap(const qTileMap& _Other);
	~qTileMap();


public:
	virtual void finaltick() override;
	void render();

	void SaveToFile(FILE* _File);
	void LoadFromFile(FILE* _File);

	
public:
	
	void SetRow(UINT _Row);
	void SetCol(UINT _Col);
	void SetRowCol(UINT _Row, UINT _Col);

	UINT GetRow() { return m_Row; }
	UINT GetCol() { return m_Col; }

	void SetAtlasTex(qTexture* _Atlas);
	qTexture* GetAtlasTex() { return m_AtlasTex; }

	void Clicked(Vec2 _vMousePos);
	

private:
	void render_grid();
	void render_tile();


private:
	UINT					m_Row;				// ��
	UINT					m_Col;				// ��
	Vec2					m_TileSize;			// Ÿ�� ���� ������
	
	qTexture*				m_AtlasTex;			// Ÿ���� ����ϴ� ��Ʋ�� �ؽ���
	UINT					m_MaxImgRow;		// ��Ʋ�� �ؽ��İ� �����ϰ� �ִ� Ÿ�� �̹��� ����(��) ����
	UINT					m_MaxImgCol;		// ��Ʋ�� �ؽ��İ� �����ϰ� �ִ� Ÿ�� �̹��� ����(��) ����

	vector<tTileInfo>		m_vecTileInfo;

};

