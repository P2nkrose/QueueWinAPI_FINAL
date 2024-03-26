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
	// ���콺 ���� Ȯ��
	bool LBtnTap = KEY_TAP(KEY::LBTN);
	bool LBtnReleased = KEY_RELEASED(KEY::LBTN);

	// ���� ������ �ִ� UI ���� �̺�Ʈ�� ó���Ѵ�.
	qLevel* pCurLevel = qLevelMgr::GetInst()->GetCurrentLevel();
	if (nullptr == pCurLevel)
		return;

	const vector<qObj*>& vecUI = pCurLevel->GetObjects(LAYER_TYPE::UI);

	for (size_t i = 0; i < vecUI.size(); ++i) 
	{
		qUI* pUI = (qUI*)vecUI[i];

		//pUI = GetPriorityUI(pUI);

		// ���� ��ư�� ���Ȱ�, �װ� �ش� UI �ȿ��� ���
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
