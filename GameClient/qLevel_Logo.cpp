#include "pch.h"
#include "qLevel_Logo.h"

#include "qLevelMgr.h"
#include "qPathMgr.h"
#include "qKeyMgr.h"

#include "qSound.h"
#include "qAssetMgr.h"

#include "qAnimator.h"
#include "qAnimation.h"

#include "qObj.h"
#include "qLogo.h"
 

qLevel_Logo::qLevel_Logo()
{
	SetName(L"logo");

}

qLevel_Logo::~qLevel_Logo()
{
}

void qLevel_Logo::begin()
{
	qLevel::begin();

	pSound = qAssetMgr::GetInst()->LoadSound(L"BGM_START", L"sound\\level\\logo.wav");
	pSound->SetVolume(30.f);
	pSound->Play();
}

void qLevel_Logo::tick()
{
	qLevel::tick();

	//if (KEY_TAP(KEY::ENTER))
	//{
	//	ChangeLevel(LEVEL_TYPE::START);
	//}

}


void qLevel_Logo::Enter()
{
	qObj* pLogo = new qLogo;
	pLogo->SetName(L"Logo");
	pLogo->SetPos(800.f, 450.f);
	pLogo->SetScale(1600.f, 900.f);
	AddObject(LAYER_TYPE::BACKGROUND, pLogo);


}

void qLevel_Logo::Exit()
{
	// ÆäÀÌµå ¾Æ¿ô
	//qCamera::GetInst()->SetCameraEffect(CAM_EFFECT::FADE_OUT, 1.f);

	// »ç¿îµå ²ô±â
	pSound->SetVolume(30.f);
	pSound->Stop();

	DeleteAllObjects();
}
