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

void qLevel_Stage01::tick()
{
	qLevel::tick();

	if (KEY_TAP(KEY::LBTN))
	{
		Vec2 vMousePos = qKeyMgr::GetInst()->GetMousePos();

		qForce* pForce = new qForce();
		pForce->SetPos(vMousePos);
		pForce->SetForce(1000.f, 500.f, 2.f);
		SpawnObject(this, LAYER_TYPE::FORCE, pForce);
	}
}
