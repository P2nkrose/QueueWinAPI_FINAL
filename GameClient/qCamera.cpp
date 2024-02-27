#include "pch.h"
#include "qCamera.h"

#include "qEngine.h"
#include "qKeyMgr.h"
#include "qTimeMgr.h"

#include "qObj.h"

qCamera::qCamera()
	: m_CamSpeed(500.f)
{
}

qCamera::~qCamera()
{
}

void qCamera::init()
{
	Vec2 vResol = qEngine::GetInst()->GetResolution();
	m_LookAt = Vec2(vResol.x * 0.5f, vResol.y * 0.5f);

	// 윈도우 해상도랑 동일한 크기의 검은색 텍스쳐를 생성
	m_FadeTex = qAssetMgr::GetInst()->CreateTexture(L"FadeTexture", (UINT)vResol.x, (UINT)vResol.y);

}

void qCamera::tick()
{
	// 카메라 이동
	Move();
	
	// 해상도 중심과 카메라가 바라보고 있는 지점 간의 차이값
	Vec2 vResol = qEngine::GetInst()->GetResolution();
	m_Diff = m_LookAt - Vec2(vResol.x * 0.5f, vResol.y * 0.5f);

	// 카메라 효과
	CameraEffect();
}

void qCamera::render()
{
	if (m_Alpha <= 0.f)
	{
		return;
	}

	BLENDFUNCTION bf = {};

	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.SourceConstantAlpha = (int)m_Alpha;
	bf.AlphaFormat = 0;

	AlphaBlend(DC, 0, 0, m_FadeTex->GetWidth(), m_FadeTex->GetHeight()
		, m_FadeTex->GetDC(), 0, 0, m_FadeTex->GetWidth(), m_FadeTex->GetHeight(), bf);
}


void qCamera::Move()
{
	if (KEY_PRESSED(KEY::W))
		m_LookAt.y -= DT * m_CamSpeed;
	if (KEY_PRESSED(KEY::S))
		m_LookAt.y += DT * m_CamSpeed;
	if (KEY_PRESSED(KEY::A))
		m_LookAt.x -= DT * m_CamSpeed;
	if (KEY_PRESSED(KEY::D))
		m_LookAt.x += DT * m_CamSpeed;
}

void qCamera::CameraEffect()
{
	if (CAM_EFFECT::NONE == m_Effect)
		return;

	m_Time += DT;
	if (m_Duration < m_Time)
	{
		m_Effect = CAM_EFFECT::NONE;
	}

	if (CAM_EFFECT::FADE_IN == m_Effect)
	{
		m_Alpha = (1.f - (m_Time / m_Duration)) * 255.f;
	}
	else if (CAM_EFFECT::FADE_OUT == m_Effect)
	{
		m_Alpha = (m_Time / m_Duration) * 255.f;
	}

}

void qCamera::SetCameraEffect(CAM_EFFECT _Effect, float _Duration)
{
	m_Effect = _Effect;
	m_Duration = _Duration;
	m_Time = 0.f;
}
