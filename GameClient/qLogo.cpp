#include "pch.h"
#include "qLogo.h"

#include "qAnimator.h"
#include "qCamera.h"

#include "qTaskMgr.h"


qLogo::qLogo()
	: m_Animator(nullptr)
{
	m_Animator = (qAnimator*)AddComponent(new qAnimator);

	// Animation �߰�
	qTexture* Logo = qAssetMgr::GetInst()->LoadTexture(L"Logo", L"texture\\logo\\logo.png");

	//�ִϸ��̼� CREATE
	m_Animator->CreateAnimation(L"Logo", Logo, Vec2(0.f, 0.f), Vec2(1600.f, 900.f), 48, 14);

	// �ִϸ��̼� SAVE
	m_Animator->FindAnimation(L"Logo")->Save(L"animation\\logo\\");

	// �ִϸ��̼� LOAD
	m_Animator->LoadAnimation(L"animation\\logo\\Logo.anim");

	m_Animator->Play(L"Logo", false);



	
}

qLogo::qLogo(const qLogo& _Other)
	: m_Animator(nullptr)
{
	m_Animator = GetComponent<qAnimator>();
}

qLogo::~qLogo()
{
}

void qLogo::tick()
{
	qObj::tick();


	if (L"Logo" == m_Animator->GetCurAnim()->GetName())
	{
		if (m_Animator->IsFinish())
		{
			ChangeLevel(LEVEL_TYPE::START);
		}
	}
}


