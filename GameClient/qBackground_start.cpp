#include "pch.h"
#include "qBackground_start.h"

#include "qAnimator.h"
#include "qCamera.h"

#include "qTaskMgr.h"


qBackground_start::qBackground_start()
	: m_Animator(nullptr)
{
	m_Animator = (qAnimator*)AddComponent(new qAnimator);

	// Animation �߰�
	qTexture* Start = qAssetMgr::GetInst()->LoadTexture(L"Start", L"texture\\start\\start.png");

	//�ִϸ��̼� CREATE
	m_Animator->CreateAnimation(L"Start", Start, Vec2(0.f, 0.f), Vec2(1600.f, 900.f), 20, 5);

	// �ִϸ��̼� SAVE
	m_Animator->FindAnimation(L"Start")->Save(L"animation\\start\\");

	// �ִϸ��̼� LOAD
	m_Animator->LoadAnimation(L"animation\\start\\Start.anim");

	m_Animator->Play(L"Start", true);
}

qBackground_start::qBackground_start(const qBackground_start& _Other)
	: m_Animator(nullptr)
{
	m_Animator = GetComponent<qAnimator>();
}

qBackground_start::~qBackground_start()
{
}

void qBackground_start::tick()
{
	qObj::tick();
}
