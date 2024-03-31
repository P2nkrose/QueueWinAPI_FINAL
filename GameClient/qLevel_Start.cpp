#include "pch.h"
#include "qLevel_Start.h"

#include "qLevelMgr.h"
#include "qPathMgr.h"
#include "qKeyMgr.h"

#include "qSound.h"
#include "qButton.h"
#include "qAssetMgr.h"

#include "qAnimation.h"
#include "qAnimator.h"

#include "qObj.h"
#include "qBackground_start.h"



void ButtonCallBackFunc()
{
	//qLevel* pLevel = qLevelMgr::GetInst()->GetCurrentLevel();
	//qStart* pStart = dynamic_cast<qStart*>(pLevel);
	//if (nullptr == pStart)
	//	return;

	ChangeLevel(LEVEL_TYPE::STAGE_01);
}


qLevel_Start::qLevel_Start()
{
	SetName(L"Start");

	if (KEY_TAP(KEY::E))
	{
		ChangeLevel(LEVEL_TYPE::EDITOR);
	}
}

qLevel_Start::~qLevel_Start()
{
}

void qLevel_Start::begin()
{
	// 사운드 로딩
	//qSound* pSound = CAssetMgr::GetInst()->LoadSound(L"BGM_01", L"sound\\BGM_Stage1.wav");
	pSound = qAssetMgr::GetInst()->LoadSound(L"BGM_START", L"sound\\start.wav");
	pSound->SetVolume(30.f);
	pSound->Play();
}

void qLevel_Start::Enter()
{

	qCamera::GetInst()->SetCameraEffect(CAM_EFFECT::FADE_IN, 0.7f);

	qBackground_start* pStartBack = new qBackground_start;
	pStartBack->SetName(L"Start");
	pStartBack->SetPos(800.f, 450.f);
	pStartBack->SetScale(1600.f, 900.f);
	AddObject(LAYER_TYPE::BACKGROUND, pStartBack);

	// 화면 해상도
	Vec2 vResol = qEngine::GetInst()->GetResolution();

	// UI 추가
	qButton* pUI = new qButton;
	m_NormalImg = qAssetMgr::GetInst()->FindTexture(L"normal");
	m_HoverImg = qAssetMgr::GetInst()->FindTexture(L"hover");
	m_DownImg = qAssetMgr::GetInst()->FindTexture(L"down");

	if (pUI->IsMouseOn())
	{
		pUI->SetHoverImage(m_HoverImg);
	}
	else if (pUI->IsLbtnDowned())
	{
		pUI->SetDownImage(m_DownImg);
	}
	else
	{
		pUI->SetNormalImage(m_NormalImg);
	}


	pUI->SetCallBack(&ButtonCallBackFunc);
	pUI->SetScale(Vec2(90.f, 30.f));
	pUI->SetPos(Vec2(vResol.x - (pUI->GetScale().x + 30), 30.f));
	
	AddObject(LAYER_TYPE::UI, pUI);





}

void qLevel_Start::Exit()
{
	// 사운드 끄기

	pSound->SetVolume(30.f);
	pSound->Stop();
}
