#include "pch.h"
#include "qUIMgr.h"

#include "qLevelMgr.h"
#include "qLevel.h"
#include "qUI.h"

qUIMgr::qUIMgr()
{
}


qUIMgr::~qUIMgr()
{
}

void qUIMgr::tick()
{
	// 마우스 상태 확인
	bool LBtnTap = KEY_TAP(KEY::LBTN);
	bool LBtnReleased = KEY_RELEASED(KEY::LBTN);

	// 현재 레벨에 있는 UI 들의 이벤트를 처리한다.
	qLevel* pCurLevel = qLevelMgr::GetInst()->GetCurrentLevel();
	if (nullptr == pCurLevel)
		return;

	const vector<qObj*>& vecUI = pCurLevel->GetObjects(LAYER_TYPE::UI);

	for (size_t i = 0; i < vecUI.size(); ++i) 
	{
		qUI* pUI = (qUI*)vecUI[i];

		//pUI = GetPriorityUI(pUI);

		// 왼쪽 버튼이 눌렸고, 그게 해당 UI 안에서 라면
		if (LBtnTap && pUI->IsMouseOn())
		{
			pUI->LButtonDown();
		}

		else if (LBtnReleased && pUI->IsMouseOn())
		{
			pUI->LButtonUp();

			if (pUI->IsLbtnDowned())
			{
				pUI->LButtonClicked();
			}
		}
	}




}
