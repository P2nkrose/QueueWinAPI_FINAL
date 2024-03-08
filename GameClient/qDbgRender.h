#pragma once
class qDbgRender
{
	SINGLE(qDbgRender)


private:
	list<tDbgRenderInfo>	m_RenderList;
	list<tDbgLog>			m_LogList;
	bool					m_bRender;


	float					m_LogLife;			// �����ִ� �ð�
	int						m_LogSpace;			// �尣
	Vec2					m_LogStartPos;		// ���� ��ġ


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

