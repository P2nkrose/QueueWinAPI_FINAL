#include "pch.h"
#include "qMonster_red.h"

#include "qCollider.h"
#include "qRigidbody.h"
#include "qAnimator.h"
#include "qAnimation.h"

#include "qLevel.h"
#include "qLevelMgr.h"

#include "qFSM.h"

#include "qRedIdleState.h"
#include "qRedMoveState.h"
#include "qRedDeadState.h"

#include "qLevelMgr.h"

qMonster_red::qMonster_red(DIRECTION _Dir)
	: m_RedHP(10)
	, m_Speed(100)
	, m_MaxDistance(100.f)
{
	SetDir(_Dir);

	// 콜라이더 설정
	m_Collider = (qCollider*)AddComponent(new qCollider);
	m_Collider->SetScale(Vec2(57.f, 70.f));

	// 중력 설정
	m_Rigidbody = (qRigidbody*)AddComponent(new qRigidbody);
	m_Rigidbody->SetMass(1.f);
	m_Rigidbody->UseGravity(true);
	m_Rigidbody->SetMaxGravitySpeed(1500.f);

	m_FSM = (qFSM*)AddComponent(new qFSM);
	m_FSM->AddState(L"RedIdle", new qRedIdleState);
	m_FSM->AddState(L"RedMove", new qRedMoveState);
	m_FSM->AddState(L"RedDead", new qRedDeadState);


	// 애니메이션 설정
	m_Animator = (qAnimator*)AddComponent(new qAnimator);

	//// Animation Register
	//// IDLE
	//qTexture* pRedIdleRight = qAssetMgr::GetInst()->LoadTexture(L"RedIdleRight", L"texture\\character\\monster\\red\\idle\\red_idle_right.png");
	//qTexture* pRedIdleLeft = qAssetMgr::GetInst()->LoadTexture(L"RedIdleLeft", L"texture\\character\\monster\\red\\idle\\red_idle_left.png");

	//// MOVE
	//qTexture* pRedMoveRight = qAssetMgr::GetInst()->LoadTexture(L"RedMoveRight", L"texture\\character\\monster\\red\\move\\red_move_right.png");
	//qTexture* pRedMoveLeft = qAssetMgr::GetInst()->LoadTexture(L"RedMoveLeft", L"texture\\character\\monster\\red\\move\\red_move_left.png");

	//// DEAD
	//qTexture* pRedDeadRight = qAssetMgr::GetInst()->LoadTexture(L"RedDeadRight", L"texture\\character\\monster\\red\\dead\\red_dead_right.png");
	//qTexture* pRedDeadLeft = qAssetMgr::GetInst()->LoadTexture(L"RedDeadLeft", L"texture\\character\\monster\\red\\dead\\red_dead_left.png");


	//// Animation Create
	//// IDLE
	//m_Animator->CreateAnimation(L"RedIdleRight", pRedIdleRight, Vec2(0.f, 0.f), Vec2(57.f, 70.f), 6, 5);
	//m_Animator->CreateAnimation(L"RedIdleLeft", pRedIdleLeft, Vec2(0.f, 0.f), Vec2(57.f, 70.f), 6, 5);

	//// MOVE
	//m_Animator->CreateAnimation(L"RedMoveRight", pRedMoveRight, Vec2(0.f, 0.f), Vec2(61.f, 82.f), 6, 7);
	//m_Animator->CreateAnimation(L"RedMoveLeft", pRedMoveLeft, Vec2(0.f, 0.f), Vec2(61.f, 82.f), 6, 7);

	//// DEAD
	//m_Animator->CreateAnimation(L"RedDeadRight", pRedDeadRight, Vec2(0.f, 0.f), Vec2(82.f, 93.f), 12, 10);
	//m_Animator->CreateAnimation(L"RedDeadLeft", pRedDeadLeft, Vec2(0.f, 0.f), Vec2(82.f, 93.f), 12, 10);


	//// Animation Save
	//// IDLE
	//m_Animator->FindAnimation(L"RedIdleRight")->Save(L"animation\\monster\\red\\idle\\");
	//m_Animator->FindAnimation(L"RedIdleLeft")->Save(L"animation\\monster\\red\\idle\\");

	//// MOVE
	//m_Animator->FindAnimation(L"RedMoveRight")->Save(L"animation\\monster\\red\\move\\");
	//m_Animator->FindAnimation(L"RedMoveLeft")->Save(L"animation\\monster\\red\\move\\");

	//// DEAD
	//m_Animator->FindAnimation(L"RedDeadRight")->Save(L"animation\\monster\\red\\dead\\");
	//m_Animator->FindAnimation(L"RedDeadLeft")->Save(L"animation\\monster\\red\\dead\\");



	// Animation Load
	m_Animator->LoadAnimation(L"animation\\monster\\red\\idle\\RedIdleRight.anim");
	m_Animator->LoadAnimation(L"animation\\monster\\red\\idle\\RedIdleLeft.anim");

	m_Animator->LoadAnimation(L"animation\\monster\\red\\move\\RedMoveRight.anim");
	m_Animator->LoadAnimation(L"animation\\monster\\red\\move\\RedMoveLeft.anim");

	m_Animator->LoadAnimation(L"animation\\monster\\red\\dead\\RedDeadRight.anim");
	m_Animator->LoadAnimation(L"animation\\monster\\red\\dead\\RedDeadLeft.anim");


}

qMonster_red::qMonster_red(const qMonster_red& _Other)
	: qObj(_Other)
	, m_RedHP(10)
	, m_Speed(100)
	, m_MaxDistance(100.f)
{
	SetName(L"Red");

	m_Collider = GetComponent<qCollider>();
	m_Animator = GetComponent<qAnimator>();
	m_Rigidbody = GetComponent<qRigidbody>();

}

qMonster_red::~qMonster_red()
{
}

void qMonster_red::begin()
{
	qObj::begin();

	SetCenterPos(GetPos());

	m_FSM->SetBlackboardData(L"RedSpeed", DATA_TYPE::FLOAT, &m_Speed);
	m_FSM->SetBlackboardData(L"RedHP", DATA_TYPE::INT, &m_RedHP);
	m_FSM->SetBlackboardData(L"MaxDist", DATA_TYPE::FLOAT, &m_MaxDistance);
	m_FSM->SetBlackboardData(L"Red", DATA_TYPE::OBJECT, this);

	m_FSM->ChangeState(L"RedIdle");
}

void qMonster_red::tick()
{
	qObj::tick();
}



void qMonster_red::BeginOverlap(qCollider* _OwnCollider, qObj* _OtherObj, qCollider* _OtherCollider)
{
	if (LAYER_TYPE::PLAYER_SKILL == _OtherObj->GetLayerType())
	{
		m_FSM->ChangeState(L"RedDead");

		//--m_HP;
		//
		//if (0 >= m_HP)
		//{
		//	
		//}
	}
}

void qMonster_red::OnOverlap(qCollider* _OwnCollider, qObj* _OtherObj, qCollider* _OtherCollider)
{
	//if (LAYER_TYPE::PLAYER_SKILL == _OtherObj->GetLayerType())
	//{
	//	m_FSM->ChangeState(L"RedDead");

	//	//--m_HP;
	//	//
	//	//if (0 >= m_HP)
	//	//{
	//	//	
	//	//}
	//}
}
