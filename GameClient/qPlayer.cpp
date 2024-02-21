#include "pch.h"
#include "qPlayer.h"

#include "qLevelMgr.h"
#include "qLevel.h"

#include "qCollider.h"
#include "qAnimator.h"
#include "qAnimation.h"
#include "qDbgRender.h"
#include "qRigidbody.h"

#include "qMissile.h"
#include "qGuideMissile.h"


qPlayer::qPlayer()
	: m_Speed(500.f)
	, m_PlayerImg(nullptr)
{
	// Player�� ������Ʈ ����
	
	m_BodyCol = (qCollider*)AddComponent(new qCollider);
	m_Animator = (qAnimator*)AddComponent(new qAnimator);
	m_RigidBody = (qRigidbody*)AddComponent(new qRigidbody);

	m_BodyCol->SetName(L"Body Collider");
	m_BodyCol->SetOffsetPos(Vec2(0.f, 10.f));
	m_BodyCol->SetScale(Vec2(70.f, 110.f));
	m_BodyCol->SetActive(true);

	// Animation �߰�
	qTexture* pAtlas = qAssetMgr::GetInst()->LoadTexture(L"PlayerAtlasTex", L"texture\\link_32.bmp");

	//m_Animator->CreateAnimation(L"IDLE_DOWN", pAtlas, Vec2(0.f, 0.f), Vec2(120.f, 130.f), 3, 10);
	m_Animator->CreateAnimation(L"IDLE_LEFT", pAtlas, Vec2(0.f, 130.f), Vec2(120.f, 130.f), 3, 10);
	//m_Animator->CreateAnimation(L"IDLE_UP", pAtlas, Vec2(0.f, 260.f), Vec2(120.f, 130.f), 1, 1);
	m_Animator->CreateAnimation(L"IDLE_RIGHT", pAtlas, Vec2(0.f, 390.f), Vec2(120.f, 130.f), 3, 10);

	//m_Animator->CreateAnimation(L"WALK_DOWN", pAtlas, Vec2(0.f, 520.f), Vec2(120.f, 130.f), 10, 18);
	m_Animator->CreateAnimation(L"WALK_LEFT", pAtlas, Vec2(0.f, 650.f), Vec2(120.f, 130.f), 10, 18);
	//m_Animator->CreateAnimation(L"WALK_UP", pAtlas, Vec2(0.f, 780.f), Vec2(120.f, 130.f), 10, 18);
	m_Animator->CreateAnimation(L"WALK_RIGHT", pAtlas, Vec2(0.f, 910.f), Vec2(120.f, 130.f), 10, 18);

	//m_Animator->FindAnimation(L"IDLE_DOWN")->Save(L"animation\\player\\");
	//m_Animator->FindAnimation(L"IDLE_LEFT")->Save(L"animation\\player\\");
	//m_Animator->FindAnimation(L"IDLE_UP")->Save(L"animation\\player\\");
	//m_Animator->FindAnimation(L"IDLE_RIGHT")->Save(L"animation\\player\\");

	//m_Animator->FindAnimation(L"WALK_DOWN")->Save(L"animation\\player\\");
	//m_Animator->FindAnimation(L"WALK_LEFT")->Save(L"animation\\player\\");
	//m_Animator->FindAnimation(L"WALK_UP")->Save(L"animation\\player\\");
	//m_Animator->FindAnimation(L"WALK_RIGHT")->Save(L"animation\\player\\");

	m_Animator->LoadAnimation(L"animation\\player\\IDLE_DOWN.anim");
	m_Animator->Play(L"IDLE_LEFT", true);

	// ��ü ����
	m_RigidBody->SetMass(1.f);
	m_RigidBody->SetMaxWalkSpeed(300.f);
	m_RigidBody->SetFriction(2000.f);

	// �߷� ���� ����
	m_RigidBody->UseGravity(true);
	m_RigidBody->SetMaxGravitySpeed(1500.f);
	m_RigidBody->SetJumpSpeed(400.f);
}

qPlayer::~qPlayer()
{
}


void qPlayer::begin()
{
}

void qPlayer::tick()
{
	qObj::tick();

	// GetAsyncKeyState
	// 0x0000 : �������� �������� ����, ȣ�� �������� �ȴ���������
	// 0x0001 : ������ �������� �ְ�, ȣ�� ������ �ȴ��������� (����)
	// 0x8000 : ������ �������� ����, ȣ�� ������ ���������� (������)
	// 0x8001 : ������ �����ְ�, ȣ�� ������ ���������� (��Ӵ�����)

	Vec2 vPos = GetPos();

	if (KEY_PRESSED(KEY::LEFT))
	{
		//vPos.x -= m_Speed * DT;
		m_RigidBody->AddForce(Vec2(-1000.f, 0.f));
	}
	else if (KEY_TAP(KEY::LEFT))
	{
		m_Animator->Play(L"WALK_LEFT", true);
	}
	else if (KEY_RELEASED(KEY::LEFT))
	{
		m_Animator->Play(L"IDLE_LEFT", true);
	}


	if (KEY_PRESSED(KEY::RIGHT))
	{
		//vPos.x += m_Speed * DT;
		m_RigidBody->AddForce(Vec2(1000.f, 0.f));
	}
	else if (KEY_TAP(KEY::RIGHT))
	{
		m_Animator->Play(L"WALK_RIGHT", true);
	}
	else if (KEY_RELEASED(KEY::RIGHT))
	{
		m_Animator->Play(L"IDLE_RIGHT", true);
	}



	if (KEY_PRESSED(KEY::UP))
	{
		//vPos.y -= m_Speed * DT;
		m_RigidBody->AddForce(Vec2(0.f, -1000.f));
	}
	else if (KEY_TAP(KEY::UP))
	{
		m_Animator->Play(L"WALK_UP", true);
	}
	else if (KEY_RELEASED(KEY::UP))
	{
		m_Animator->Play(L"IDLE_UP", true);
	}



	if (KEY_PRESSED(KEY::DOWN))
	{
		//vPos.y += m_Speed * DT;
		m_RigidBody->AddForce(Vec2(0.f, 1000.f));
	}
	else if (KEY_TAP(KEY::DOWN))
	{
		m_Animator->Play(L"WALK_DOWN", true);
	}
	else if (KEY_RELEASED(KEY::DOWN))
	{
		m_Animator->Play(L"IDLE_DOWN", true);
	}

	// SPACE ������ ����!
	if (KEY_TAP(KEY::SPACE))
	{
		//Shoot();
		Jump();
	}


	SetPos(vPos);
}





void qPlayer::BeginOverlap(qCollider* _OwnCollider, qObj* _OtherObj, qCollider* _OtherCollider)
{
	int a = 0;
}


void qPlayer::OnOverlap(qCollider* _OwnCollider, qObj* _OtherObj, qCollider* _OtherCollider)
{

}


void qPlayer::EndOverlap(qCollider* _OwnCollider, qObj* _OtherObj, qCollider* _OtherCollider)
{
	int a = 0;
}


void qPlayer::Shoot()
{
	qMissile* pMissile = new qGuideMissile;
	pMissile->SetName(L"Missile");

	Vec2 vMissilePos = GetPos();
	vMissilePos.y -= GetScale().y / 2.f;

	pMissile->SetPos(vMissilePos);
	pMissile->SetScale(Vec2(20.f, 20.f));

	// TASK
	SpawnObject(qLevelMgr::GetInst()->GetCurrentLevel(), LAYER_TYPE::PLAYER_MISSILE, pMissile);

	// LOG
	LOG(LOG_TYPE::DBG_LOG, L"�̻��� �߻�!");
}

void qPlayer::Jump()
{
	m_RigidBody->jump();
}




