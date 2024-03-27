#include "pch.h"
#include "qLevel_Start.h"

#include "qLevelMgr.h"
#include "qPathMgr.h"
#include "qKeyMgr.h"

#include "qButton.h"
#include "qSound.h"


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
}

qLevel_Start::~qLevel_Start()
{
}

void qLevel_Start::begin()
{
	// 사운드 로딩
	//qSound* pSound = CAssetMgr::GetInst()->LoadSound(L"BGM_01", L"sound\\BGM_Stage1.wav");
	pSound = qAssetMgr::GetInst()->LoadSound(L"BGM_START", L"sound\\start.wav");
	pSound->SetVolume(50.f);
	pSound->Play();
}

void qLevel_Start::Enter()
{

	qCamera::GetInst()->SetCameraEffect(CAM_EFFECT::FADE_IN, 0.7f);

	// 화면 해상도
	Vec2 vResol = qEngine::GetInst()->GetResolution();

	// UI 추가
	qButton* pUI = new qButton;

	pUI->SetCallBack(&ButtonCallBackFunc);
	pUI->SetScale(Vec2(200.f, 100.f));
	pUI->SetPos(Vec2(vResol.x - (pUI->GetScale().x + 10), 10.f));
	AddObject(LAYER_TYPE::UI, pUI);
}

void qLevel_Start::Exit()
{
	// 사운드 끄기

	pSound->SetVolume(50.f);
	pSound->Stop();
}
