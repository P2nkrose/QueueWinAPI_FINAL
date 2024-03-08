#pragma once
class qDbgRender
{
	SINGLE(qDbgRender)


private:
	list<tDbgRenderInfo>	m_RenderList;
	list<tDbgLog>			m_LogList;
	bool					m_bRender;


	float					m_LogLife;			// 남아있는 시간
	int						m_LogSpace;			// 장간
	Vec2					m_LogStartPos;		// 시작 위치


public:
	void AddDbgRenderInfo(const tDbgRenderInfo& _info)
	{
		m_RenderList.push_back(_info);
	}

	void AddDbgLog(const tDbgLog& _info) { m_LogList.push_back(_info); }


	bool IsDbgRender() { return m_bRender; }

public:
	void tick();
	void render();
};

