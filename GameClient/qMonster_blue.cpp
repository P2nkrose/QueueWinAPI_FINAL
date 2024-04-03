#include "pch.h"
#include "qMonster_blue.h"

#include "qCollider.h"
#include "qRigidbody.h"
#include "qAnimator.h"
#include "qAnimation.h"

#include "qLevel.h"
#include "qLevelMgr.h"

#include "qFSM.h"
#include "qBlueIdleState.h"
#include "qBlueMoveState.h"
#include "qBlueDeadState.h"



qMonster_blue::qMonster_blue(DIRECTION _Dir)
	: m_BlueHP(10)
	, m_Speed(100.f)
	, m_MaxDistance(100.f)

{
	SetDir(_Dir);

	
	//// 난수 생성
	//srand((unsigned int)time(NULL));

	//int num = rand() % 1;

	//if (num == 0)
	//{
	//	SetDir(DIRECTION::LEFT);
	//}

	//else if (1 == num)
	//{
	//	SetDir(DIRECTION::RIGHT);
	//}

	// 콜라이더 설정
	m_Collider = (qCollider*)AddComponent(new qCollider);
	m_Collider->SetScale(Vec2(65.f, 85.f));


	// 중력 설정
	m_Rigidbody = (qRigidbody*)AddComponent(new qRigidbody);
	m_Rigidbody->SetMass(1.f);
	m_Rigidbody->UseGravity(true);
	m_Rigidbody->SetMaxGravitySpeed(1500.f);
	//m_Rigidbody->SetGround(false);
	

	m_FSM = (qFSM*)AddComponent(new qFSM);
	m_FSM->AddState(L"Idle", new qBlueIdleState);
	m_FSM->AddState(L"Move", new qBlueMoveState);
	m_FSM->AddState(L"Dead", new qBlueDeadState);

	
	// 애니메이션 설정
	m_Animator = (qAnimator*)AddComponent(new qAnimator);
	
	//// Animation Register
	//// IDLE
	//qTexture* pBlueIdleRight = qAssetMgr::GetInst()->LoadTexture(L"BlueIdleRight", L"texture\\character\\monster\\blue\\idle\\blue_idle_right.png");
	//qTexture* pBlueIdleLeft = qAssetMgr::GetInst()->LoadTexture(L"BlueIdleLeft", L"texture\\character\\monster\\blue\\idle\\blue_idle_left.png");
	//
	//// MOVE
	//qTexture* pBlueMoveRight = qAssetMgr::GetInst()->LoadTexture(L"BlueMoveRight", L"texture\\character\\monster\\blue\\move\\blue_move_right.png");
	//qTexture* pBlueMoveLeft = qAssetMgr::GetInst()->LoadTexture(L"BlueMoveLeft", L"texture\\character\\monster\\blue\\move\\blue_move_left.png");

	//// DEAD
	//qTexture* pBlueDeadRight = qAssetMgr::GetInst()->LoadTexture(L"BlueDeadRight", L"texture\\character\\monster\\blue\\dead\\blue_dead_right.png");
	//qTexture* pBlueDeadLeft = qAssetMgr::GetInst()->LoadTexture(L"BlueDeadLeft", L"texture\\character\\monster\\blue\\dead\\blue_dead_left.png");


	//// Animation Create
	//// IDLE
	//m_Animator->CreateAnimation(L"BlueIdleRight", pBlueIdleRight, Vec2(0.f, 0.f), Vec2(60.f, 82.f), 6, 5);
	//m_Animator->CreateAnimation(L"BlueIdleLeft", pBlueIdleLeft, Vec2(0.f, 0.f), Vec2(60.f, 82.f), 6, 5);

	//// MOVE
	//m_Animator->CreateAnimation(L"BlueMoveRight", pBlueMoveRight, Vec2(0.f, 0.f), Vec2(65.f, 91.f), 6, 7);
	//m_Animator->CreateAnimation(L"BlueMoveLeft", pBlueMoveLeft, Vec2(0.f, 0.f), Vec2(65.f, 91.f), 6, 7);

	//// DEAD
	//m_Animator->CreateAnimation(L"BlueDeadRight", pBlueDeadRight, Vec2(0.f, 0.f), Vec2(93.f, 93.f), 12, 10);
	//m_Animator->CreateAnimation(L"BlueDeadLeft", pBlueDeadLeft, Vec2(0.f, 0.f), Vec2(93.f, 93.f), 12, 10);
	//

	//// Animation Save
	//// IDLE
	//m_Animator->FindAnimation(L"BlueIdleRight")->Save(L"animation\\monster\\blue\\idle\\");
	//m_Animator->FindAnimation(L"BlueIdleLeft")->Save(L"animation\\monster\\blue\\idle\\");

	//// MOVE
	//m_Animator->FindAnimation(L"BlueMoveRight")->Save(L"animation\\monster\\blue\\move\\");
	//m_Animator->FindAnimation(L"BlueMoveLeft")->Save(L"animation\\monster\\blue\\move\\");

	//// DEAD
	//m_Animator->FindAnimation(L"BlueDeadRight")->Save(L"animation\\monster\\blue\\dead\\");
	//m_Animator->FindAnimation(L"BlueDeadLeft")->Save(L"animation\\monster\\blue\\dead\\");



	// Animation Load
	m_Animator->LoadAnimation(L"animation\\monster\\blue\\idle\\BlueIdleRight.anim");
	m_Animator->LoadAnimation(L"animation\\monster\\blue\\idle\\BlueIdleLeft.anim");

	m_Animator->LoadAnimation(L"animation\\monster\\blue\\move\\BlueMoveRight.anim");
	m_Animator->LoadAnimation(L"animation\\monster\\blue\\move\\BlueMoveLeft.anim");

	m_Animator->LoadAnimation(L"animation\\monster\\blue\\dead\\BlueDeadRight.anim");
	m_Animator->LoadAnimation(L"animation\\monster\\blue\\dead\\BlueDeadLeft.anim");

	
}

qMonster_blue::qMonster_blue(const qMonster_blue& _Other)
	: qObj(_Other)
	, m_BlueHP(100)
	, m_Speed(50.f)

{
	m_Collider = GetComponent<qCollider>();
	m_Animator = GetComponent<qAnimator>();
	m_Rigidbody = GetComponent<qRigidbody>();
}

qMonster_blue::~qMonster_blue()
{
	
}

void qMonster_blue::begin()
{
	qObj::begin();

	
	SetCenterPos(GetPos());

	m_FSM->SetBlackboardData(L"BlueSpeed", DATA_TYPE::FLOAT, &m_Speed);
	m_FSM->SetBlackboardData(L"BlueHP", DATA_TYPE::INT, &m_BlueHP);
	m_FSM->SetBlackboardData(L"MaxDist", DATA_TYPE::FLOAT, &m_MaxDistance);
	m_FSM->SetBlackboardData(L"Blue", DATA_TYPE::OBJECT, this);


	m_FSM->ChangeState(L"Idle");
}

void qMonster_blue::tick()
{
	qObj::tick();
	Vec2 vPos = GetPos();

	

	
		

}


void qMonster_blue::BeginOverlap(qCollider* _OwnCollider, qObj* _OtherObj, qCollider* _OtherCollider)
{
	if (LAYER_TYPE::PLAYER_SKILL == _OtherObj->GetLayerType())
	{
		m_FSM->ChangeState(L"Dead");


		//--m_HP;
		//
		//if (0 >= m_HP)
		//{
		//	
		//}
	}


}

void qMonster_blue::OnOverlap(qCollider* _OwnCollider, qObj* _OtherObj, qCollider* _OtherCollider)
{
	if (LAYER_TYPE::PLAYER_SKILL == _OtherObj->GetLayerType())
	{
		m_FSM->ChangeState(L"Dead");

	}
}







