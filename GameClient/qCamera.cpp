#include "pch.h"
#include "qCamera.h"

#include "qEngine.h"
#include "qKeyMgr.h"
#include "qTimeMgr.h"
#include "qPlayer.h"
#include "qLevelMgr.h"
#include "qLevel.h"

#include "qObj.h"
#include "qBackground.h"

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

	//// ������ �ػ󵵶� ������ ũ���� ������ �ؽ��ĸ� ����
	m_FadeTex = qAssetMgr::GetInst()->CreateTexture(L"FadeTexture", (UINT)vResol.x, (UINT)vResol.y);

	//// ������ �ػ󵵶� ������ ũ���� ������ �ؽ��ĸ� ����
	//m_RedTex = qAssetMgr::GetInst()->CreateTexture(L"RedTexture", (UINT)vResol.x, (UINT)vResol.y);

	//// Red Texture �� Red Brush�� Rectangle �� �׸���.
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
	// ī�޶� �̵�
	Move();
	
	// �ػ� �߽ɰ� ī�޶� �ٶ󺸰� �ִ� ���� ���� ���̰�
	Vec2 vResol = qEngine::GetInst()->GetResolution();
	m_Diff = m_LookAt - Vec2(vResol.x * 0.5f, vResol.y * 0.5f);

	// ī�޶� ȿ��
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

	if (nullptr == pCurLevel || nullptr == m_Owner)
		return;

	if(pCurLevel->GetName() == L"editor")
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
	if (pCurLevel->GetName() == L"stage1")
	{
		if (KEY_PRESSED(KEY::W))
			m_LookAt.y -= DT * m_CamSpeed;
		if (KEY_PRESSED(KEY::S))
			m_LookAt.y += DT * m_CamSpeed;
		if (KEY_PRESSED(KEY::A))
			m_LookAt.x -= DT * m_CamSpeed;
		if (KEY_PRESSED(KEY::D))
			m_LookAt.x += DT * m_CamSpeed;
		qBackground* BackGround = (qBackground*)pCurLevel->FindObjectByName(L"Stage1");

		if (nullptr == BackGround)
			return;

		
		UINT Width = BackGround->GetWidth();
		UINT Height = BackGround->GetHeight();

		m_LookAt.x = m_Owner->GetPos().x;
		
		Vec2 vPos = BackGround->GetPos() - Width * 0.5f;
		
		vPos.x = BackGround->GetPos().x - Width * 0.5f;
		vPos.y = BackGround->GetPos().y - Height * 0.5f;

		UINT StartWidth = Width - (Width - 1);
		UINT FinalHeigt;
		
		UINT CameraMinimumDist = StartWidth + 640.f;

		float CameraDistX = vPos.x + vPos.x + 640.f;
		float CameraDistY = vPos.y - vPos.y + 384.f;
		
		float ObjDist = vPos.x + m_Owner->GetPos().x;

		
		if (CameraDistX >= ObjDist)
		{
			m_LookAt.x = CameraDistX;
		}
		
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
