#pragma once

class qObj;

class qCamera
{
	SINGLE(qCamera)

public:
	void init();
	void tick();

public:
	Vec2 GetRenderPos(Vec2 _RealPos)
	{
		return _RealPos - m_Diff;
	}

	Vec2 GetRealPos(Vec2 _RenderPos)
	{
		return _RenderPos + m_Diff;
	}

	void SetOwner(qObj* _Owner) { m_Owner = _Owner; }


private:
	Vec2		m_LookAt;
	Vec2		m_Diff;

	float		m_CamSpeed;

	qObj*		m_Owner;

};

