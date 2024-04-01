#include "pch.h"
#include "qSkill_missile_ball_left.h"

#include "qCollider.h"
#include "qAnimator.h"
#include "qCamera.h"

#include "qTaskMgr.h"

qSkill_missile_ball_left::qSkill_missile_ball_left()
	: m_Animator(nullptr)
{
	m_Animator = (qAnimator*)AddComponent(new qAnimator);

	// Animation �߰�
	qTexture* MissileBallLeft = qAssetMgr::GetInst()->LoadTexture(L"MissileBallLeft", L"texture\\skill\\missile\\missile_ball_left.png");

	// �ִϸ��̼� CREATE
	m_Animator->CreateAnimation(L"MissileBallLeft", MissileBallLeft, Vec2(0.f, 0.f), Vec2(100.f, 70.f), 4, 5);

	// �ִϸ��̼� SAVE
	m_Animator->FindAnimation(L"MissileBallLeft")->Save(L"animation\\skill\\missile\\");

	// �ִϸ��̼� LOAD
	m_Animator->LoadAnimation(L"animation\\skill\\missile\\MissileBallLeft.anim");

	m_Animator->Play(L"MissileBallLeft", true);


	// �ݶ��̴�

	m_Collider = (qCollider*)AddComponent(new qCollider);

	m_Collider->SetOffsetPos(Vec2(0.f, 0.f));
	m_Collider->SetScale(Vec2(100.f, 70.f));
}

qSkill_missile_ball_left::qSkill_missile_ball_left(const qSkill_missile_ball_left& _Other)
	: m_Animator(nullptr)
{
	m_Animator = GetComponent<qAnimator>();
}

qSkill_missile_ball_left::~qSkill_missile_ball_left()
{
}

void qSkill_missile_ball_left::tick()
{
	qObj::tick();
}


void qSkill_missile_ball_left::BeginOverlap(qCollider* _OwnCollider, qObj* _OtherObj, qCollider* _OtherCollider)
{
	// ���� �ε������� Destroy();
}
