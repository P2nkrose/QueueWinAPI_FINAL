#pragma once
class qDbgRender
{
	SINGLE(qDbgRender)


private:
	list<tDbgRenderInfo>	m_RenderList;

	bool					m_bRender;


public:
	void AddDbgRenderInfo(const tDbgRenderInfo& _info)
	{
		m_RenderList.push_back(_info);
	}


public:
	void tick();
	void render();

};

