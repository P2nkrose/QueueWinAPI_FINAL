#include "pch.h"
#include "qLevel_Stage01.h"

#include "qKeyMgr.h"
#include "qForce.h"

qLevel_Stage01::qLevel_Stage01()
{
}

qLevel_Stage01::~qLevel_Stage01()
{
}

void qLevel_Stage01::begin()
{
	qLevel::begin();

	qCamera::GetInst()->SetCameraEffect(CAM_EFFECT::FADE_IN, 2.f);
	qCamera::GetInst()->SetCameraEffect(CAM_EFFECT::FADE_OUT, 2.f);
}

void qLevel_Stage01::tick()
{
	qLevel::tick();

	if (KEY_TAP(KEY::LBTN))
	{
		Vec2 vMousePos = qKeyMgr::GetInst()->GetMousePos();
		Vec2 vPos = qCamera::GetInst()->GetRenderPos(vMousePos);

		qForce* pForce = new qForce();
		pForce->SetPos(vPos);
		pForce->SetForce(1000.f, 500.f, 2.f);
		SpawnObject(this, LAYER_TYPE::FORCE, pForce);
	}
}
