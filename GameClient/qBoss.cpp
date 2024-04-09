#include "pch.h"
#include "qBoss.h"

#include "qCollider.h"
#include "qRigidbody.h"
#include "qAnimator.h"
#include "qAnimation.h"

#include "qPlayer.h"

#include "qLevel.h"
#include "qLevelMgr.h"

#include "qFSM.h"

#include "qBossIdleState.h"
#include "qBossBallState.h"
#include "qBossGenesisState.h"
#include "qBossFirebirdState.h"
#include "qBossTornadoState.h"
#include "qBossDeadState.h"


qBoss::qBoss()
	: m_BossHP(63000000)
	, m_Dir(DIRECTION::LEFT)

{
	// 콜라이더 설정
	m_Collider = (qCollider*)AddComponent(new qCollider);
	m_Collider->SetScale(Vec2(100.f, 190.f));


	// 중력 설정
	m_Rigidbody = (qRigidbody*)AddComponent(new qRigidbody);
	m_Rigidbody->SetMass(1.f);
	m_Rigidbody->UseGravity(true);
	m_Rigidbody->SetMaxGravitySpeed(1500.f);
	//m_Rigidbody->SetGround(true);


	// State 설정
	m_FSM = (qFSM*)AddComponent(new qFSM);
	m_FSM->AddState(L"Idle", new qBossIdleState);
	m_FSM->AddState(L"Ball", new qBossBallState);
	m_FSM->AddState(L"Genesis", new qBossGenesisState);
	m_FSM->AddState(L"Firebird", new qBossFirebirdState);
	m_FSM->AddState(L"Tornado", new qBossTornadoState);
	m_FSM->AddState(L"Dead", new qBossDeadState);




	// 애니메이션 설정
	m_Animator = (qAnimator*)AddComponent(new qAnimator);


	// Animation Resister
	// IDLE
	//qTexture* pBossIdleLeft = qAssetMgr::GetInst()->LoadTexture(L"BossIdleLeft", L"texture\\character\\boss\\idle\\idle_left.png");
	//qTexture* pBossIdleRight = qAssetMgr::GetInst()->LoadTexture(L"BossIdleRight", L"texture\\character\\boss\\idle\\idle_right.png");

	// BALL (다크니스 볼)
	//qTexture* pBossBallLeft = qAssetMgr::GetInst()->LoadTexture(L"BossBallLeft", L"texture\\character\\boss\\ball\\ball_left.png");
	//qTexture* pBossBallRight = qAssetMgr::GetInst()->LoadTexture(L"BossBallRight", L"texture\\character\\boss\\ball\\ball_right.png");

	// GENESIS (다크 제네시스)
	//qTexture* pBossGenesisLeft = qAssetMgr::GetInst()->LoadTexture(L"BossGenesisLeft", L"texture\\character\\boss\\genesis\\genesis_left.png");
	//qTexture* pBossGenesisRight = qAssetMgr::GetInst()->LoadTexture(L"BossGenesisRight", L"texture\\character\\boss\\genesis\\genesis_right.png");

	// FIREBIRD (화염 장판)
	//qTexture* pBossFirebirdLeft = qAssetMgr::GetInst()->LoadTexture(L"BossFirebirdLeft", L"texture\\character\\boss\\firebird\\firebird_left.png");
	//qTexture* pBossFirebirdRight = qAssetMgr::GetInst()->LoadTexture(L"BossFirebirdRight", L"texture\\character\\boss\\firebird\\firebird_right.png");

	// TORNADO (어비스 토네이도)
	//qTexture* pBossTornadoLeft = qAssetMgr::GetInst()->LoadTexture(L"BossTornadoLeft", L"texture\\character\\boss\\tornado\\tornado_left.png");
	//qTexture* pBossTornadoRight = qAssetMgr::GetInst()->LoadTexture(L"BossTonardoRight", L"texture\\character\\boss\\tornado\\tornado_right.png");

	// DEAD
	//qTexture* pBossDeadLeft = qAssetMgr::GetInst()->LoadTexture(L"BossDeadLeft", L"texture\\character\\boss\\dead\\dead_left.png");
	//qTexture* pBossDeadRight = qAssetMgr::GetInst()->LoadTexture(L"BossDeadRight", L"texture\\character\\boss\\dead\\dead_right.png");


	// Animation Create
	// IDLE
	//m_Animator->CreateAnimation(L"BossIdleLeft", pBossIdleLeft, Vec2(0.f, 0.f), Vec2(145.f, 200.f), 8, 10);
	//m_Animator->CreateAnimation(L"BossIdleRight", pBossIdleRight, Vec2(0.f, 0.f), Vec2(145.f, 200.f), 8, 10);

	// BALL
	//m_Animator->CreateAnimation(L"BossBallLeft", pBossBallLeft, Vec2(0.f, 0.f), Vec2(550.f, 350.f), 17, 10);
	//m_Animator->CreateAnimation(L"BossBallRight", pBossBallRight, Vec2(0.f, 0.f), Vec2(550.f, 350.f), 17, 10);

	// GENESIS
	//m_Animator->CreateAnimation(L"BossGenesisLeft", pBossGenesisLeft, Vec2(0.f, 0.f), Vec2(420.f, 360.f), 32, 10);
	//m_Animator->CreateAnimation(L"BossGenesisRight", pBossGenesisRight, Vec2(0.f, 0.f), Vec2(420.f, 360.f), 32, 10);

	// FIREBIRD
	//m_Animator->CreateAnimation(L"BossFirebirdLeft", pBossFirebirdLeft, Vec2(0.f, 0.f), Vec2(200.f, 300.f), 23, 10);
	//m_Animator->CreateAnimation(L"BossFirebirdRight", pBossFirebirdRight, Vec2(0.f, 0.f), Vec2(200.f, 300.f), 23, 10);

	// TORNADO
	//m_Animator->CreateAnimation(L"BossTornadoLeft", pBossTornadoLeft, Vec2(0.f, 0.f), Vec2(400.f, 500.f), 26, 10);
	//m_Animator->CreateAnimation(L"BossTornadoRight", pBossTornadoRight, Vec2(0.f, 0.f), Vec2(400.f, 500.f), 26, 10);

	// DEAD
	//m_Animator->CreateAnimation(L"BossDeadLeft", pBossDeadLeft, Vec2(0.f, 0.f), Vec2(300.f, 310.f), 29, 8);
	//m_Animator->CreateAnimation(L"BossDeadRight", pBossDeadRight, Vec2(0.f, 0.f), Vec2(300.f, 310.f), 29, 8);


	// Animation Save
	// IDLE
	//m_Animator->FindAnimation(L"BossIdleLeft")->Save(L"animation\\boss\\idle\\");
	//m_Animator->FindAnimation(L"BossIdleRight")->Save(L"animation\\boss\\idle\\");

	// BALL
	//m_Animator->FindAnimation(L"BossBallLeft")->Save(L"animation\\boss\\ball\\");
	//m_Animator->FindAnimation(L"BossBallRight")->Save(L"animation\\boss\\ball\\");

	// GENESIS
	//m_Animator->FindAnimation(L"BossGenesisLeft")->Save(L"animation\\boss\\genesis\\");
	//m_Animator->FindAnimation(L"BossGenesisRight")->Save(L"animation\\boss\\genesis\\");

	// FIREBIRD
	//m_Animator->FindAnimation(L"BossFirebirdLeft")->Save(L"animation\\boss\\firebird\\");
	//m_Animator->FindAnimation(L"BossFirebirdRight")->Save(L"animation\\boss\\firebird\\");

	// TORNADO
	//m_Animator->FindAnimation(L"BossTornadoLeft")->Save(L"animation\\boss\\tornado\\");
	//m_Animator->FindAnimation(L"BossTornadoRight")->Save(L"animation\\boss\\tornado\\");

	// DEAD
	//m_Animator->FindAnimation(L"BossDeadLeft")->Save(L"animation\\boss\\dead\\");
	//m_Animator->FindAnimation(L"BossDeadRight")->Save(L"animation\\boss\\dead\\");


	// Animation Load
	m_Animator->LoadAnimation(L"animation\\boss\\idle\\BossIdleLeft.anim");
	m_Animator->LoadAnimation(L"animation\\boss\\idle\\BossIdleRight.anim");

	m_Animator->LoadAnimation(L"animation\\boss\\ball\\BossBallLeft.anim");
	m_Animator->LoadAnimation(L"animation\\boss\\ball\\BossBallRight.anim");

	m_Animator->LoadAnimation(L"animation\\boss\\genesis\\BossGenesisLeft.anim");
	m_Animator->LoadAnimation(L"animation\\boss\\genesis\\BossGenesisRight.anim");

	m_Animator->LoadAnimation(L"animation\\boss\\firebird\\BossFirebirdLeft.anim");
	m_Animator->LoadAnimation(L"animation\\boss\\firebird\\BossFirebirdRight.anim");

	m_Animator->LoadAnimation(L"animation\\boss\\tornado\\BossTornadoLeft.anim");
	m_Animator->LoadAnimation(L"animation\\boss\\tornado\\BossTornadoRight.anim");

	m_Animator->LoadAnimation(L"animation\\boss\\dead\\BossDeadLeft.anim");
	m_Animator->LoadAnimation(L"animation\\boss\\dead\\BossDeadRight.anim");

	
}

qBoss::qBoss(const qBoss& _Other)
	: qObj(_Other)
	, m_BossHP(63000000)
	, m_Dir(_Other.m_Dir)
	, m_Animator(nullptr)
{
	m_Collider = GetComponent<qCollider>();
	m_Animator = GetComponent<qAnimator>();
	m_Rigidbody = GetComponent<qRigidbody>();
}

qBoss::~qBoss()
{
}

void qBoss::begin()
{
	qObj::begin();

	SetCenterPos(GetPos());

	qObj* pPlayer = qLevelMgr::GetInst()->FindObjectByName(L"Player");
	m_FSM->SetBlackboardData(L"Player", DATA_TYPE::OBJECT, pPlayer);

	qObj* pBossBallLeft = qLevelMgr::GetInst()->FindObjectByName(L"BossBallLeft");
	m_FSM->SetBlackboardData(L"BossBallLeft", DATA_TYPE::OBJECT, pBossBallLeft);

	m_FSM->SetBlackboardData(L"BossHP", DATA_TYPE::INT, &m_BossHP);
	m_FSM->SetBlackboardData(L"Boss", DATA_TYPE::OBJECT, this);

	m_FSM->ChangeState(L"Idle");
}

void qBoss::tick()
{
	qObj::tick();

}

void qBoss::BeginOverlap(qCollider* _OwnCollider, qObj* _OtherObj, qCollider* _OtherCollider)
{
}

void qBoss::OnOverlap(qCollider* _OwnCollider, qObj* _OtherObj, qCollider* _OtherCollider)
{
}
