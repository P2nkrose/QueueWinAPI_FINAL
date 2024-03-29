#include "pch.h"
#include "qCamera.h"

#include "qEngine.h"
#include "qKeyMgr.h"
#include "qTimeMgr.h"
#include "qPlayer.h"
#include "qLevelMgr.h"
#include "qLevel.h"

#include "qObj.h"
#include "qBackground_stage1.h"
#include "qBackground_stage2.h"

qCamera::qCamera()
	: m_CamSpeed(500.f)
	, m_FadeTex(nullptr)
	, m_RightBlock(false)
{
}

qCamera::~qCamera()
{
}

void qCamera::init()
{
	Vec2 vResol = qEngine::GetInst()->GetResolution();
	m_LookAt = Vec2(vResol.x * 0.5f, vResol.y * 0.5f);

	//// 윈도우 해상도랑 동일한 크기의 검은색 텍스쳐를 생성
	m_FadeTex = qAssetMgr::GetInst()->CreateTexture(L"FadeTexture", (UINT)vResol.x, (UINT)vResol.y);

	//// 윈도우 해상도랑 동일한 크기의 붉은색 텍스쳐를 생성
	//m_RedTex = qAssetMgr::GetInst()->CreateTexture(L"RedTexture", (UINT)vResol.x, (UINT)vResol.y);

	//// Red Texture 에 Red Brush로 Rectangle 을 그린다.
	//USE_BRUSH(m_RedTex->GetDC(), BRUSH_TYPE::BRUSH_RED);
	//Rectangle(m_RedTex->GetDC(), -1, -1, (UINT)vResol.x + 1, (UINT)vResol.y + 1);

	//for (UINT Row = 0; Row < vResol.y; ++Row)
	//{
	//	for (UINT Col = 0; Col < vResol.x; ++Col)
	//	{
	//		SetPixel(m_RedTex->GetDC(), Col, Row, RGB(255, 0, 0));
	//	}
	//}
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
	if (m_EffectList.empty())
		return;

	CAM_EFFECT_INFO& info = m_EffectList.front();

	BLENDFUNCTION bf = {};

	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.SourceConstantAlpha = (int)info.Alpha;
	bf.AlphaFormat = 0;

	AlphaBlend(DC, 0, 0, m_FadeTex->GetWidth(), m_FadeTex->GetHeight()
		, m_FadeTex->GetDC(), 0, 0, m_FadeTex->GetWidth(), m_FadeTex->GetHeight(), bf);
}


void qCamera::Move()
{
	qLevel* pCurLevel = qLevelMgr::GetInst()->GetCurrentLevel();

	if (nullptr == pCurLevel)
		return;

	if(pCurLevel->GetName() == L"Editor")
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
	if (pCurLevel->GetName() == L"Stage1")
	{
		qBackground_stage1* BackGround = (qBackground_stage1*)pCurLevel->FindObjectByName(L"Stage1");
		
		if (nullptr == BackGround)
			return;
		
		if (!m_Owner)
			return;
		
		//m_LookAt = m_Owner->GetPos();
		
		UINT Width = BackGround->GetWidth();
		UINT Height = BackGround->GetHeight();
		
		// 카메라 벽 못넘게 하기
		Vec2 vPos = GetRealPos(m_Owner->GetPos());
		Vec2 vRenderPos = m_Owner->GetRenderPos();
		
		// 현재 위치 표시
		wchar_t szBuff[256] = {};
		static float fTime = 0.f;
		fTime += DT;
		if (fTime >= 1.f)
		{
			swprintf_s(szBuff, L"x : %f, y : %f", vPos.x, vPos.y);
			LOG(LOG_TYPE::DBG_ERROR, szBuff);
			fTime = 0.f;
		}
		
		if (vPos.x <= 800.f)
		{
			m_LookAt.x = 800.f;
		}

		// 스테이지 1 카메라 못넘게하기 (오른쪽) == 3535
		else if (vPos.x >= 3535.f)
		{
			m_LookAt.x = Width - 800;
		}
		else
		{
			m_LookAt.x = m_Owner->GetPos().x;
		}
		
		m_LookAt.y = 477.f;
		
}
	else if (pCurLevel->GetName() == L"Stage2")
	{
		qBackground_stage2* BackGround = (qBackground_stage2*)pCurLevel->FindObjectByName(L"Stage2");
		
		if (nullptr == BackGround)
			return;

		//m_LookAt.x = m_Owner->GetPos().x;
		//m_LookAt.y = m_Owner->GetPos().y;

		UINT Width = BackGround->GetWidth();
		UINT Height = BackGround->GetHeight();
		
		// 카메라 벽 못넘게 하기
		Vec2 vPos = GetRealPos(m_Owner->GetPos());
		Vec2 vRenderPos = m_Owner->GetRenderPos();
		
		//현재 위치 표시
		wchar_t szBuff[256] = {};
		static float fTime = 0.f;
		fTime += DT;
		if (fTime >= 1.f)
		{
			swprintf_s(szBuff, L"x : %f, y : %f", vPos.x, vPos.y);
			LOG(LOG_TYPE::DBG_ERROR, szBuff);
			fTime = 0.f;
		}
		// X 좌표 계산
		// 왼쪽 벽 못넘게 하기
		if (vPos.x <= 800.f)
		{
			m_LookAt.x = 800.f;
		}
		//스테이지 2 카메라 못넘게하기 (오른쪽) == 1561
		else if (vPos.x >= 1561.f)
		{
			m_LookAt.x = Width - 800;
		}
		else
		{
			m_LookAt.x = m_Owner->GetPos().x;
		}

		float vDist = m_LookAt.y - vPos.y;

		m_LookAt.y = 1190.f;

		// Y좌표 계산
		//if (vDist < -150.f)
		//{
		//	m_LookAt.y = Height * 0.7;
		//}
		//else if (vDist >= -150.f)
		//{
		//	m_LookAt.y = m_Owner->GetPos().y;
		//}
		//else if (vDist <= -150.f && vDist >= 60)
		//{
		//	m_LookAt.y = Height * 0.5;
		//}
		
		
	}
	else if (pCurLevel->GetName() == L"Boss1")
	{
		qBackground_stage2* BackGround = (qBackground_stage2*)pCurLevel->FindObjectByName(L"Boss1");

		if (nullptr == BackGround)
			return;


		UINT Width = BackGround->GetWidth();
		UINT Height = BackGround->GetHeight();

		// 카메라 벽 못넘게 하기
		Vec2 vPos = GetRealPos(m_Owner->GetPos());
		Vec2 vRenderPos = m_Owner->GetRenderPos();
		wchar_t szBuff[256] = {};
		static float fTime = 0.f;
		fTime += DT;
		if (fTime >= 1.f)
		{
			swprintf_s(szBuff, L"x : %f, y : %f", vPos.x, vPos.y);
			LOG(LOG_TYPE::DBG_ERROR, szBuff);
			fTime = 0.f;
		}
		if (vPos.x <= 800.f)
		{
			m_LookAt.x = 800.f;
		}
		// 보스 1 카메라 못넘게하기 (오른쪽) == 
		else if (vPos.x >= 1246.f)
		{
			m_LookAt.x = Width - 800;
		}
		else
		{
			m_LookAt.x = m_Owner->GetPos().x;
		}
		
		m_LookAt.y = 496.f;
	}

	else if (pCurLevel->GetName() == L"Boss2")
	{
		qBackground_stage2* BackGround = (qBackground_stage2*)pCurLevel->FindObjectByName(L"Boss2");

		if (nullptr == BackGround)
			return;


		UINT Width = BackGround->GetWidth();
		UINT Height = BackGround->GetHeight();

		// 카메라 벽 못넘게 하기
		Vec2 vPos = GetRealPos(m_Owner->GetPos());
		Vec2 vRenderPos = m_Owner->GetRenderPos();
		wchar_t szBuff[256] = {};
		static float fTime = 0.f;
		fTime += DT;
		if (fTime >= 1.f)
		{
			swprintf_s(szBuff, L"x : %f, y : %f", vPos.x, vPos.y);
			LOG(LOG_TYPE::DBG_ERROR, szBuff);
			fTime = 0.f;
		}
		if (vPos.x <= 800.f)
		{
			m_LookAt.x = 800.f;
		}
		// 보스 1 카메라 못넘게하기 (오른쪽) == 
		else if (vPos.x >= 1246.f)
		{
			m_LookAt.x = Width - 800;
		}

		else
		{
			m_LookAt.x = m_Owner->GetPos().x;
		}

		m_LookAt.y = 485.f;
	}
}

void qCamera::CameraEffect()
{
	while (true)
	{
		if (m_EffectList.empty())
			return;

		CAM_EFFECT_INFO& info = m_EffectList.front();
		info.Time += DT;

		if (info.Duration < info.Time)
		{
			m_EffectList.pop_front();
		}
		else
		{
			break;
		}
	}

	CAM_EFFECT_INFO& info = m_EffectList.front();

	if (CAM_EFFECT::FADE_IN == info.Effect)
	{
		info.Alpha = (1.f - (info.Time / info.Duration)) * 255.f;
	}
	else if (CAM_EFFECT::FADE_OUT == info.Effect)
	{
		info.Alpha = (info.Time / info.Duration) * 255.f;
	}
}

void qCamera::SetCameraEffect(CAM_EFFECT _Effect, float _Duration)
{
	CAM_EFFECT_INFO info = {};

	info.Effect = _Effect;
	info.Duration = _Duration;
	info.Time = 0.f;
	info.Alpha = 0.f;

	m_EffectList.push_back(info);
}
