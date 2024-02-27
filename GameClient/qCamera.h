#pragma once

enum class CAM_EFFECT
{
	FADE_IN,
	FADE_OUT,
	NONE,
};

struct CAM_EFFECT_INFO
{
	CAM_EFFECT		Effect;
	float			Duration;
	float			Time;
	float			Alpha;

};

class qObj;
class qTexture;

class qCamera
{
	SINGLE(qCamera)

public:
	void init();
	void tick();
	void render();

public:
	Vec2 GetRenderPos(Vec2 _RealPos) { return _RealPos - m_Diff; }
	Vec2 GetRealPos(Vec2 _RenderPos) { return _RenderPos + m_Diff; }
	void SetCameraEffect(CAM_EFFECT _Effect, float _Duration);

	void SetOwner(qObj* _Owner) { m_Owner = _Owner; }


private:
	void Move();
	void CameraEffect();

private:
	Vec2					m_LookAt;
	Vec2					m_Diff;
	float					m_CamSpeed;

	qObj*					m_Owner;	

	list<CAM_EFFECT_INFO>	m_EffectList;

	qTexture*				m_FadeTex;
	qTexture*				m_RedTex;

};

