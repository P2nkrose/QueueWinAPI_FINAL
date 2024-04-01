#include "pch.h"
#include "qSkill_missile_ball_right.h"

#include "qCollider.h"
#include "qAnimator.h"
#include "qCamera.h"

#include "qTaskMgr.h"

qSkill_missile_ball_right::qSkill_missile_ball_right()
	: m_Animator(nullptr)
	, m_Collider(nullptr)
{
	m_Animator = (qAnimator*)AddComponent(new qAnimator);

	// Animation �߰�
	qTexture* MissileBallRight = qAssetMgr::GetInst()->LoadTexture(L"MissileBallRight", L"texture\\skill\\missile\\missile_ball_right.png");

	// �ִϸ��̼� CREATE
	m_Animator->CreateAnimation(L"MissileBallRight", MissileBallRight, Vec2(0.f, 0.f), Vec2(100.f, 70.f), 4, 5);

	// �ִϸ��̼� SAVE
	m_Animator->FindAnimation(L"MissileBallRight")->Save(L"animation\\skill\\missile\\");

	// �ִϸ��̼� LOAD
	m_Animator->LoadAnimation(L"animation\\skill\\missile\\MissileBallRight.anim");

	m_Animator->Play(L"MissileBallRight", true);


	// �ݶ��̴�

	m_Collider = (qCollider*)AddComponent(new qCollider);

	m_Collider->SetOffsetPos(Vec2(0.f, 0.f));
	m_Collider->SetScale(Vec2(100.f, 70.f));
}

qSkill_missile_ball_right::qSkill_missile_ball_right(const qSkill_missile_ball_right& _Other)
	: m_Animator(nullptr)
	, m_Collider(nullptr)
{
	m_Animator = GetComponent<qAnimator>();
}

qSkill_missile_ball_right::~qSkill_missile_ball_right()
{
}

void qSkill_missile_ball_right::tick()
{
	qObj::tick();
}


void qSkill_missile_ball_right::BeginOverlap(qCollider* _OwnCollider, qObj* _OtherObj, qCollider* _OtherCollider)
{
	// ���� �ε������� Destroy();
}
