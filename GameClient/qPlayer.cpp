#include "pch.h"
#include "qPlayer.h"

#include "qLevelMgr.h"
#include "qLevel.h"

#include "qCollider.h"
#include "qAnimator.h"
#include "qAnimation.h"
#include "qDbgRender.h"
#include "qRigidbody.h"

#include "qRope.h"

#include "qFSM.h"

#include "qMissile.h"
#include "qGuideMissile.h"

#include "qSkill_attack_left.h"
#include "qSkill_attack_right.h"
#include "qSkill_missile_left.h"
#include "qSkill_missile_right.h"
#include "qSkill_missile_ball_left.h"
#include "qSkill_missile_ball_right.h"
#include "qSkill_slash_left.h"
#include "qSkill_slash_right.h"
#include "qSkill_special_left.h"
#include "qSkill_special_right.h"
#include "qSkill_buff.h"
#include "qSkill_doublejump_left.h"
#include "qSkill_doublejump_right.h"
#include "qSkill_highjump.h"

#include "qBossSkill_ball_left.h"

#include "qDamage_miss.h"

#include "qDbgRender.h"
#include "qCamera.h"

#include "qBossIdleState.h"
#include "qBossBallState.h"
#include "qBossGenesisState.h"
#include "qBossFirebirdState.h"
#include "qBossTornadoState.h"
#include "qBossDeadState.h"


void BeGround()
{
	LOG(LOG_TYPE::DBG_WARNING, L"Grounded!!!");
	LOG(LOG_TYPE::DBG_WARNING, L"Grounded!!!");
}

void BeAir()
{
	LOG(LOG_TYPE::DBG_WARNING, L"Air!!!");
	LOG(LOG_TYPE::DBG_WARNING, L"Air!!!");
}


qPlayer::qPlayer()
	: m_State(PLAYER_STATE::IDLE)
	, m_Speed(150.f)
	, m_SlashSpeed(900.f)
	, m_SlashMaxRange(0.f)
	, m_Slash(true)
	, m_Hud(100.f)
	, m_Level(LEVEL_TYPE::END)
	, m_PlayerImg(nullptr)
	, m_DoubleJumpCount(2)
	, m_CurJumpCount(0)
	, m_bRope(false)
{

	m_Pos = GetPos();

	// Player의 컴포넌트 설정
	
	m_BodyCol = (qCollider*)AddComponent(new qCollider);
	m_Animator = (qAnimator*)AddComponent(new qAnimator);
	m_RigidBody = (qRigidbody*)AddComponent(new qRigidbody);


	m_BodyCol->SetName(L"Body Collider");
	m_BodyCol->SetOffsetPos(Vec2(0.f, 0.f));
	m_BodyCol->SetScale(Vec2(70.f, 70.f));
	m_BodyCol->SetActive(true);

	
	//// Animation 추가
	////IDLE
	//qTexture* pIdleLeft = qAssetMgr::GetInst()->LoadTexture(L"PlayerIdleLeft", L"texture\\character\\player\\idle\\idle_left.png");
	//qTexture* pIdleRight = qAssetMgr::GetInst()->LoadTexture(L"PlayerIdleRight", L"texture\\character\\player\\idle\\idle_right.png");

	//// MOVE
	//qTexture* pMoveLeft = qAssetMgr::GetInst()->LoadTexture(L"PlayerMoveLeft", L"texture\\character\\player\\move\\move_left.png");
	//qTexture* pMoveRight = qAssetMgr::GetInst()->LoadTexture(L"PlayerMoveRight", L"texture\\character\\player\\move\\move_right.png");

	//// DOWN
	//qTexture* pDownLeft = qAssetMgr::GetInst()->LoadTexture(L"PlayerDownLeft", L"texture\\character\\player\\down\\down_left.png");
	//qTexture* pDownRight = qAssetMgr::GetInst()->LoadTexture(L"PlayerDownRight", L"texture\\character\\player\\down\\down_right.png");

	//// DOWN ATTACK
	//qTexture* pDownAttackLeft = qAssetMgr::GetInst()->LoadTexture(L"PlayerDownAttackLeft", L"texture\\character\\player\\down_attack\\down_attack_left.png");
	//qTexture* pDownAttackRight = qAssetMgr::GetInst()->LoadTexture(L"PlayerDownAttackRight", L"texture\\character\\player\\down_attack\\down_attack_right.png");

	//// JUMP
	//qTexture* pJumpLeft = qAssetMgr::GetInst()->LoadTexture(L"PlayerJumpLeft", L"texture\\character\\player\\jump\\jump_left.png");
	//qTexture* pJumpRight = qAssetMgr::GetInst()->LoadTexture(L"PlayerJumpRight", L"texture\\character\\player\\jump\\jump_right.png");

	//// ROPE
	//qTexture* pRope = qAssetMgr::GetInst()->LoadTexture(L"PlayerRope", L"texture\\character\\player\\rope\\rope.png");

	//// ATTACK
	//qTexture* pAttackLeft = qAssetMgr::GetInst()->LoadTexture(L"PlayerAttackLeft", L"texture\\character\\player\\attack\\attack_left.png");
	//qTexture* pAttackRight = qAssetMgr::GetInst()->LoadTexture(L"PlayerAttackRight", L"texture\\character\\player\\attack\\attack_right.png");
	//
	//// MISSILE
	//qTexture* pMissileLeft = qAssetMgr::GetInst()->LoadTexture(L"PlayerMissileLeft", L"texture\\character\\player\\missile\\missile_left.png");
	//qTexture* pMissileRight = qAssetMgr::GetInst()->LoadTexture(L"PlayerMissileRight", L"texture\\character\\player\\missile\\missile_right.png");

	//// SLASH
	//qTexture* pSlashLeft = qAssetMgr::GetInst()->LoadTexture(L"PlayerSlashLeft", L"texture\\character\\player\\slash\\slash_left.png");
	//qTexture* pSlashRight = qAssetMgr::GetInst()->LoadTexture(L"PlayerSlashRight", L"texture\\character\\player\\slash\\slash_right.png");

	//// SPECIAL
	//qTexture* pSpecialLeft = qAssetMgr::GetInst()->LoadTexture(L"PlayerSpecialLeft", L"texture\\character\\player\\special\\special_left.png");
	//qTexture* pSpecialRight = qAssetMgr::GetInst()->LoadTexture(L"PlayerSpecialRight", L"texture\\character\\player\\special\\special_right.png");


	////애니메이션 CREATE
	////IDLE
	//m_Animator->CreateAnimation(L"PlayerIdleLeft", pIdleLeft, Vec2(0.f, 0.f), Vec2(114.f, 78.f), 3, 3);
	//m_Animator->CreateAnimation(L"PlayerIdleRight", pIdleRight, Vec2(0.f, 0.f), Vec2(114.f, 78.f), 3, 3);

	//// MOVE
	//m_Animator->CreateAnimation(L"PlayerMoveLeft", pMoveLeft, Vec2(0.f, 0.f), Vec2(110.f, 84.f), 4, 3);
	//m_Animator->CreateAnimation(L"PlayerMoveRight", pMoveRight, Vec2(0.f, 0.f), Vec2(110.f, 84.f), 4, 3);

	//// DOWN
	//m_Animator->CreateAnimation(L"PlayerDownLeft", pDownLeft, Vec2(0.f, 0.f), Vec2(132.f, 67.f), 1, 3);
	//m_Animator->CreateAnimation(L"PlayerDownRight", pDownRight, Vec2(0.f, 0.f), Vec2(132.f, 67.f), 1, 3);

	//// DOWN ATTACK
	//m_Animator->CreateAnimation(L"PlayerDownAttackLeft", pDownAttackLeft, Vec2(0.f, 0.f), Vec2(132.f, 67.f), 3, 3);
	//m_Animator->CreateAnimation(L"PlayerDownAttackRight", pDownAttackRight, Vec2(0.f, 0.f), Vec2(132.f, 67.f), 3, 3);

	//// JUMP
	//m_Animator->CreateAnimation(L"PlayerJumpLeft", pJumpLeft, Vec2(0.f, 0.f), Vec2(60.f, 100.f), 1, 3);
	//m_Animator->CreateAnimation(L"PlayerJumpRight", pJumpRight, Vec2(0.f, 0.f), Vec2(60.f, 100.f), 1, 3);

	//// ROPE
	//m_Animator->CreateAnimation(L"PlayerRope", pRope, Vec2(0.f, 0.f), Vec2(72.f, 81.f), 1, 3);

	//// ATTACK
	//m_Animator->CreateAnimation(L"PlayerAttackLeft", pAttackLeft, Vec2(0.f, 0.f), Vec2(223.f, 149.f), 3, 6);
	//m_Animator->CreateAnimation(L"PlayerAttackRight", pAttackRight, Vec2(0.f, 0.f), Vec2(223.f, 149.f), 3, 6);

	//// MISSILE
	//m_Animator->CreateAnimation(L"PlayerMissileLeft", pMissileLeft, Vec2(0.f, 0.f), Vec2(227.f, 140.f), 3, 8);
	//m_Animator->CreateAnimation(L"PlayerMissileRight", pMissileRight, Vec2(0.f, 0.f), Vec2(227.f, 140.f), 3, 8);

	//// SLASH
	//m_Animator->CreateAnimation(L"PlayerSlashLeft", pSlashLeft, Vec2(0.f, 0.f), Vec2(182.f, 78.f), 2, 5);
	//m_Animator->CreateAnimation(L"PlayerSlashRight", pSlashRight, Vec2(0.f, 0.f), Vec2(182.f, 78.f), 2, 5);

	//// SPECIAL
	//m_Animator->CreateAnimation(L"PlayerSpecialLeft", pSpecialLeft, Vec2(0.f, 0.f), Vec2(188.f, 148.f), 3, 6);
	//m_Animator->CreateAnimation(L"PlayerSpecialRight", pSpecialRight, Vec2(0.f, 0.f), Vec2(188.f, 148.f), 3, 6);



	//// 애니메이션 SAVE
	//// IDLE
	//m_Animator->FindAnimation(L"PlayerIdleLeft")->Save(L"animation\\player\\idle\\");
	//m_Animator->FindAnimation(L"PlayerIdleRight")->Save(L"animation\\player\\idle\\");

	//// MOVE
	//m_Animator->FindAnimation(L"PlayerMoveLeft")->Save(L"animation\\player\\move\\");
	//m_Animator->FindAnimation(L"PlayerMoveRight")->Save(L"animation\\player\\move\\");

	//// DOWN
	//m_Animator->FindAnimation(L"PlayerDownLeft")->Save(L"animation\\player\\down\\");
	//m_Animator->FindAnimation(L"PlayerDownRight")->Save(L"animation\\player\\down\\");

	//// DOWN_ATTACK
	//m_Animator->FindAnimation(L"PlayerDownAttackLeft")->Save(L"animation\\player\\down_attack\\");
	//m_Animator->FindAnimation(L"PlayerDownAttackRight")->Save(L"animation\\player\\down_attack\\");

	//// JUMP
	//m_Animator->FindAnimation(L"PlayerJumpLeft")->Save(L"animation\\player\\jump\\");
	//m_Animator->FindAnimation(L"PlayerJumpRight")->Save(L"animation\\player\\jump\\");

	//// ROPE
	//m_Animator->FindAnimation(L"PlayerRope")->Save(L"animation\\player\\rope\\");

	//// ATTACK
	//m_Animator->FindAnimation(L"PlayerAttackLeft")->Save(L"animation\\player\\attack\\");
	//m_Animator->FindAnimation(L"PlayerAttackRight")->Save(L"animation\\player\\attack\\");

	//// MISSILE
	//m_Animator->FindAnimation(L"PlayerMissileLeft")->Save(L"animation\\player\\missile\\");
	//m_Animator->FindAnimation(L"PlayerMissileRight")->Save(L"animation\\player\\missile\\");

	//// SLASH
	//m_Animator->FindAnimation(L"PlayerSlashLeft")->Save(L"animation\\player\\slash\\");
	//m_Animator->FindAnimation(L"PlayerSlashRight")->Save(L"animation\\player\\slash\\");

	//// SPECIAL
	//m_Animator->FindAnimation(L"PlayerSpecialLeft")->Save(L"animation\\player\\special\\");
	//m_Animator->FindAnimation(L"PlayerSpecialRight")->Save(L"animation\\player\\special\\");



	// Load Animation

	m_Animator->LoadAnimation(L"animation\\player\\idle\\PlayerIdleLeft.anim");
	m_Animator->LoadAnimation(L"animation\\player\\idle\\PlayerIdleRight.anim");


	m_Animator->LoadAnimation(L"animation\\player\\move\\PlayerMoveLeft.anim");
	m_Animator->LoadAnimation(L"animation\\player\\move\\PlayerMoveRight.anim");


	m_Animator->LoadAnimation(L"animation\\player\\down\\PlayerDownLeft.anim");
	m_Animator->LoadAnimation(L"animation\\player\\down\\PlayerDownRight.anim");


	m_Animator->LoadAnimation(L"animation\\player\\down_attack\\PlayerDownAttackLeft.anim");
	m_Animator->LoadAnimation(L"animation\\player\\down_attack\\PlayerDownAttackRight.anim");

	m_Animator->LoadAnimation(L"animation\\player\\jump\\PlayerJumpLeft.anim");
	m_Animator->LoadAnimation(L"animation\\player\\jump\\PlayerJumpRight.anim");

	m_Animator->LoadAnimation(L"animation\\player\\rope\\PlayerRope.anim");

	m_Animator->LoadAnimation(L"animation\\player\\attack\\PlayerAttackLeft.anim");
	m_Animator->LoadAnimation(L"animation\\player\\attack\\PlayerAttackRight.anim");

	m_Animator->LoadAnimation(L"animation\\player\\missile\\PlayerMissileLeft.anim");
	m_Animator->LoadAnimation(L"animation\\player\\missile\\PlayerMissileRight.anim");

	m_Animator->LoadAnimation(L"animation\\player\\slash\\PlayerSlashLeft.anim");
	m_Animator->LoadAnimation(L"animation\\player\\slash\\PlayerSlashRight.anim");

	m_Animator->LoadAnimation(L"animation\\player\\special\\PlayerSpecialLeft.anim");
	m_Animator->LoadAnimation(L"animation\\player\\special\\PlayerSpecialRight.anim");


	// 강체 설정
	m_RigidBody->SetMass(1.f);
	m_RigidBody->SetMaxWalkSpeed(300.f);
	m_RigidBody->SetFriction(2000.f);

	// 중력 관련 설정
	m_RigidBody->UseGravity(true);
	m_RigidBody->SetMaxGravitySpeed(1500.f);
	m_RigidBody->SetJumpSpeed(400.f);

	// CallBack 설정
	m_RigidBody->SetGroundFunc(&BeGround);
	m_RigidBody->SetAirFunc(&BeAir);

	// Delegate
	m_RigidBody->SetGroundDelegate(this, (DELEGATE)&qPlayer::RestoreJumpCount);
	m_RigidBody->SetGround(true);

	// 카메라
	qCamera::GetInst()->SetOwner(this);

	// FSM
	//m_FSM = (qFSM*)AddComponent(new qFSM);
	//m_FSM->AddState(L"IDLE", new qPlayerState);



	m_Animator->Play(L"PlayerIdleLeft", true);

}

qPlayer::qPlayer(const qPlayer& _Other)
	: qObj(_Other)
	, m_Speed(_Other.m_Speed)
	, m_PlayerImg(_Other.m_PlayerImg)
	, m_BodyCol(nullptr)
	, m_Animator(nullptr)
	, m_RigidBody(nullptr)
	, m_DoubleJumpCount(_Other.m_DoubleJumpCount)
	, m_CurJumpCount(_Other.m_CurJumpCount)
{
	m_BodyCol = GetComponent<qCollider>();
	m_Animator = GetComponent<qAnimator>();
	m_RigidBody = GetComponent<qRigidbody>();

	m_RigidBody->SetGroundDelegate(this, (DELEGATE)&qPlayer::RestoreJumpCount);
}

qPlayer::~qPlayer()
{
	
}


void qPlayer::begin()
{
	qObj::begin();
	// CallBack 설정
	m_RigidBody->SetGroundFunc(&BeGround);
	m_RigidBody->SetAirFunc(&BeAir);


	// 플레이어 방향 설정
	qLevel* pCurLevel = qLevelMgr::GetInst()->GetCurrentLevel();

	if (pCurLevel->GetName() == L"Stage1")
	{
		SetDir(DIRECTION::LEFT);
		m_Animator->Play(L"PlayerIdleLeft", true);
	}
	else if (pCurLevel->GetName() == L"Stage2")
	{
		SetDir(DIRECTION::LEFT);
		m_Animator->Play(L"PlayerIdleLeft", true);
	}
	else if (pCurLevel->GetName() == L"Boss1")
	{
		SetDir(DIRECTION::RIGHT);
		m_Animator->Play(L"PlayerIdleRight", true);
	}
	else if (pCurLevel->GetName() == L"Boss2")
	{
		SetDir(DIRECTION::RIGHT); 
		m_Animator->Play(L"PlayerIdleRight", true);
	}


	// Delegate
	//m_RigidBody->SetGroundDelegate(this, (DELEGATE)&qPlayer::RestoreJumpCount);


	// 블랙보드
	//m_FSM->SetBlackboardData(L"Player", DATA_TYPE::OBJECT, this);

	// 블랙보드로 넘겨주기
	//m_FSM->SetBlackboardData(L"pHud", DATA_TYPE::FLOAT, &m_Hud);
	//m_FSM->SetBlackboardData(L"pSpeed", DATA_TYPE::FLOAT, &m_Speed);
	//m_FSM->SetBlackboardData(L"pPlayer", DATA_TYPE::OBJECT, this);

	//m_FSM->ChangeState(L"IDLE");

}

void qPlayer::tick()
{

	qObj::tick();

	GetExp();

	GetPlayerHP();

	GetPhysicalCount();
	GetMagicCount();

	qLevel* pCurLevel = qLevelMgr::GetInst()->GetCurrentLevel();

	m_Pos = GetPos();

	wchar_t szBuff[256] = {};
	static float Time = 0.f;

	Time += DT;
	if (Time >= 1.f)
	{
		swprintf_s(szBuff, L"%f, %f", m_Pos.x, m_Pos.y);
		LOG(LOG_TYPE::DBG_WARNING, szBuff);
		Time = 0.f;
	}


	// ======
	//  ROPE
	// ======
	qRope* pRope = (qRope*)pCurLevel->FindObjectByName(L"Rope");

	if (m_bRope)
	{
		if (KEY_PRESSED(KEY::UP))
		{
			SetPos(m_Rope->GetPos().x, m_Pos.y);
			m_RigidBody->SetRope(true);
			m_Animator->Play(L"PlayerRope", true);
			m_Pos += Vec2(0.f, -1.f) * 200.f * DT;
			SetPos(m_Rope->GetPos().x, m_Pos.y);
			return;
		}
		if (KEY_PRESSED(KEY::DOWN))
		{
			SetPos(m_Rope->GetPos().x, m_Pos.y);
			m_RigidBody->SetRope(true);
			m_Animator->Play(L"PlayerRope", true);
			m_Pos += Vec2(0.f, 1.f) * 200.f * DT;
			SetPos(m_Rope->GetPos().x, m_Pos.y);
			return;
		}
	}
	else
	{

	}

	
	
	

	// ======
	//  MOVE
	// ======
	

	if (KEY_PRESSED(KEY::LEFT) && m_RigidBody->IsGround() 
		&& PLAYER_STATE::ATTACK != m_State && PLAYER_STATE::MISSILE != m_State && PLAYER_STATE::SLASH != m_State
		&& PLAYER_STATE::SPECIAL != m_State)
	{
		m_State = PLAYER_STATE::MOVE;
		SetDir(DIRECTION::LEFT);
		m_Pos += Vec2(-1.f, 0.f) * m_Speed * DT;
		//m_RigidBody->AddForce(Vec2(-1000.f, 0.f));
	}
	else if (KEY_TAP(KEY::LEFT) && m_RigidBody->IsGround())
	{
		m_State = PLAYER_STATE::MOVE;
		SetDir(DIRECTION::LEFT);
		m_Animator->Play(L"PlayerMoveLeft", true);
	}
	else if (KEY_RELEASED(KEY::LEFT) && m_RigidBody->IsGround())
	{
		m_State = PLAYER_STATE::IDLE;
		SetDir(DIRECTION::LEFT);
		m_Slash = true;
		m_Animator->Play(L"PlayerIdleLeft", true);
	}


	if (KEY_PRESSED(KEY::RIGHT) && m_RigidBody->IsGround()
		&& PLAYER_STATE::ATTACK != m_State && PLAYER_STATE::MISSILE != m_State && PLAYER_STATE::SLASH != m_State
		&& PLAYER_STATE::SPECIAL != m_State)
	{
		m_State = PLAYER_STATE::MOVE;
		SetDir(DIRECTION::RIGHT);
		m_Pos += Vec2(1.f, 0.f) * m_Speed * DT;
		//m_RigidBody->AddForce(Vec2(1000.f, 0.f));
	}
	else if (KEY_TAP(KEY::RIGHT) && m_RigidBody->IsGround())
	{
		m_State = PLAYER_STATE::MOVE;
		SetDir(DIRECTION::RIGHT);
		m_Animator->Play(L"PlayerMoveRight", true);
	}
	else if (KEY_RELEASED(KEY::RIGHT) && m_RigidBody->IsGround())
	{
		m_State = PLAYER_STATE::IDLE;
		SetDir(DIRECTION::RIGHT);
		m_Slash = true;
		m_Animator->Play(L"PlayerIdleRight", true);
	}

	// ======
	//  DOWN
	// ======

	if (KEY_TAP(KEY::DOWN) && m_RigidBody->IsGround() && PLAYER_STATE::IDLE == GetState())
	{
		if (GetDir() == DIRECTION::LEFT)
		{
			m_State = PLAYER_STATE::DOWN;
			m_Animator->Play(L"PlayerDownLeft", true);

		}
		else if (GetDir() == DIRECTION::RIGHT)
		{
			m_State = PLAYER_STATE::DOWN;
			m_Animator->Play(L"PlayerDownRight", true);
		}
	}

	// =============
	//  DOWN ATTACK
	// =============


	else if (KEY_PRESSED(KEY::DOWN))
	{
		if (KEY_TAP(KEY::CTRL))
		{
			m_State = PLAYER_STATE::DOWN_ATTACK;
			
			if (GetDir() == DIRECTION::LEFT)
			{
				m_Animator->Play(L"PlayerDownAttackLeft", false);
			}
			else if (GetDir() == DIRECTION::RIGHT)
			{
				m_Animator->Play(L"PlayerDownAttackRight", false);
			}
		}
	}


	else if (KEY_RELEASED(KEY::DOWN) && m_RigidBody->IsGround())
	{
		m_State = PLAYER_STATE::IDLE;
		m_Slash = true;

		if (GetDir() == DIRECTION::LEFT)
		{
			m_Animator->Play(L"PlayerIdleLeft", true);
		}
		else if (GetDir() == DIRECTION::RIGHT)
		{
			m_Animator->Play(L"PlayerIdleRight", true);
		}
	}

	// =======================
	//    솔라슬래시 / ATTACK
	// =======================

	if (KEY_TAP(KEY::A) && m_RigidBody->IsGround())
	{
		m_State = PLAYER_STATE::ATTACK;

		if (GetDir() == DIRECTION::LEFT)
		{
			m_Animator->Play(L"PlayerAttackLeft", false);
			
			// 솔라 슬래시 스킬 이펙트

			qSkill_attack_left* pAttackLeft = new qSkill_attack_left;
			pAttackLeft->SetName(L"AttackLeft");
			

			Vec2 vAttackLeftPos = GetPos() + Vec2(-100.f, 0.f);
			Vec2 vAttackLeftScale = Vec2(410.f, 240.f);

			pAttackLeft->SetPos(vAttackLeftPos);
			pAttackLeft->SetScale(vAttackLeftScale);

			if (L"AttackLeft" == pAttackLeft->GetName())
			{
				SpawnObject(qLevelMgr::GetInst()->GetCurrentLevel(), LAYER_TYPE::PLAYER_SKILL, pAttackLeft);
			}


		}
		else if (GetDir() == DIRECTION::RIGHT)
		{
			m_Animator->Play(L"PlayerAttackRight", false);

			// 솔라 슬래시 스킬 이펙트

			qSkill_attack_right* pAttackRight = new qSkill_attack_right;
			pAttackRight->SetName(L"AttackRight");
			
			Vec2 vAttackRightPos = GetPos() + Vec2(100.f, 0.f);
			Vec2 vAttackRightScale = Vec2(410.f, 240.f);

			pAttackRight->SetPos(vAttackRightPos);
			pAttackRight->SetScale(vAttackRightScale);

			if (L"AttackRight" == pAttackRight->GetName())
			{
				SpawnObject(qLevelMgr::GetInst()->GetCurrentLevel(), LAYER_TYPE::PLAYER_SKILL, pAttackRight);
			}
		}
	}

	if (L"PlayerAttackLeft" == m_Animator->GetCurAnim()->GetName())
	{
		if (m_Animator->IsFinish())
		{
			m_State = PLAYER_STATE::IDLE;
			m_Slash = true;
			m_Animator->Play(L"PlayerIdleLeft", true);
		}
	}
	else if (L"PlayerAttackRight" == m_Animator->GetCurAnim()->GetName())
	{
		if (m_Animator->IsFinish())
		{
			m_State = PLAYER_STATE::IDLE;
			m_Slash = true;
			m_Animator->Play(L"PlayerIdleRight", true);
		}
	}

	// ============================
	//    루나 디바이드 / MISSILE
	// ============================

	if (KEY_TAP(KEY::S) && m_RigidBody->IsGround())
	{
		m_State = PLAYER_STATE::MISSILE;

		if (GetDir() == DIRECTION::LEFT)
		{
			m_Animator->Play(L"PlayerMissileLeft", false);


			// 루나 디바이드 스킬 이펙트
			qSkill_missile_left* pMissileLeft = new qSkill_missile_left;
			pMissileLeft->SetName(L"MissileLeft");
			

			Vec2 vMissileLeftPos = GetPos() + Vec2(-50.f, 0.f);
			Vec2 vMissileLeftScale = Vec2(240.f, 195.f);

			pMissileLeft->SetPos(vMissileLeftPos);
			pMissileLeft->SetScale(vMissileLeftScale);

			if (L"MissileLeft" == pMissileLeft->GetName())
			{
				SpawnObject(qLevelMgr::GetInst()->GetCurrentLevel(), LAYER_TYPE::PLAYER_SKILL, pMissileLeft);
			}

			// 루나 디바이드 미사일
			qSkill_missile_ball_left* pBallLeft = new qSkill_missile_ball_left;
			pBallLeft->SetName(L"BallLeft");
			

			Vec2 vBallLeftPos = GetPos() + Vec2(-50.f, 0.f);
			Vec2 vBallLeftScale = Vec2(100.f, 70.f);

			pBallLeft->SetPos(vBallLeftPos);
			pBallLeft->SetScale(vBallLeftScale);

			if (L"BallLeft" == pBallLeft->GetName())
			{
				SpawnObject(qLevelMgr::GetInst()->GetCurrentLevel(), LAYER_TYPE::PLAYER_SKILL, pBallLeft);
			}

		}
		else if (GetDir() == DIRECTION::RIGHT)
		{
			m_Animator->Play(L"PlayerMissileRight", false);

			// 루나 디바이드 스킬 이펙트
			qSkill_missile_right* pMissileRight = new qSkill_missile_right;
			pMissileRight->SetName(L"MissileRight");
			

			Vec2 vMissileRightPos = GetPos() + Vec2(50.f, 0.f);
			Vec2 vMissileRightScale = Vec2(240.f, 195.f);

			pMissileRight->SetPos(vMissileRightPos);
			pMissileRight->SetScale(vMissileRightScale);

			if (L"MissileRight" == pMissileRight->GetName())
			{
				SpawnObject(qLevelMgr::GetInst()->GetCurrentLevel(), LAYER_TYPE::PLAYER_SKILL, pMissileRight);
			}


			// 루나 디바이드 미사일
			qSkill_missile_ball_right* pBallRight = new qSkill_missile_ball_right;
			pBallRight->SetName(L"BallRight");
			

			Vec2 vBallRightPos = GetPos() + Vec2(50.f, 0.f);
			Vec2 vBallRightScale = Vec2(100.f, 70.f);

			pBallRight->SetPos(vBallRightPos);
			pBallRight->SetScale(vBallRightScale);

			if (L"BallRight" == pBallRight->GetName())
			{
				SpawnObject(qLevelMgr::GetInst()->GetCurrentLevel(), LAYER_TYPE::PLAYER_SKILL, pBallRight);
			}
		}
	}

	if (L"PlayerMissileLeft" == m_Animator->GetCurAnim()->GetName())
	{
		if (m_Animator->IsFinish())
		{
			m_State = PLAYER_STATE::IDLE;
			m_Slash = true;
			m_Animator->Play(L"PlayerIdleLeft", true);
		}
	}
	else if (L"PlayerMissileRight" == m_Animator->GetCurAnim()->GetName())
	{
		if (m_Animator->IsFinish())
		{
			m_State = PLAYER_STATE::IDLE;
			m_Slash = true;
			m_Animator->Play(L"PlayerIdleRight", true);
		}
	}

	// =========================
	//     라우드러시 / SLASH
	// =========================

	if (m_Slash)
	{
		if (KEY_TAP(KEY::D) && m_RigidBody->IsGround())
		{
			if (DIRECTION::LEFT == GetDir())
			{
				m_CenterPos = GetPos();

				// 라우드 러쉬 스킬 이펙트
				qSkill_slash_left* pSlashLeft = new qSkill_slash_left;
				pSlashLeft->SetName(L"SlashLeft");
				

				Vec2 vSlashLeftPos = GetPos();
				Vec2 vSlashLeftScale = Vec2(675.f, 215.f);

				pSlashLeft->SetOwner(this);
				pSlashLeft->SetPos(vSlashLeftPos);
				pSlashLeft->SetScale(vSlashLeftScale);

				if (L"SlashLeft" == pSlashLeft->GetName())
				{
					SpawnObject(qLevelMgr::GetInst()->GetCurrentLevel(), LAYER_TYPE::PLAYER_SKILL, pSlashLeft);
				}
			}
			else if (DIRECTION::RIGHT == GetDir())
			{
				m_CenterPos = GetPos();

				// 라우드 러쉬 스킬 이펙트
				qSkill_slash_right* pSlashRight = new qSkill_slash_right;
				pSlashRight->SetName(L"SlashRight");
				

				Vec2 vSlashRightPos = GetPos();
				Vec2 vSlashRightScale = Vec2(675.f, 215.f);

				pSlashRight->SetOwner(this);
				pSlashRight->SetPos(vSlashRightPos);
				pSlashRight->SetScale(vSlashRightScale);

				if (L"SlashRight" == pSlashRight->GetName())
				{
					SpawnObject(qLevelMgr::GetInst()->GetCurrentLevel(), LAYER_TYPE::PLAYER_SKILL, pSlashRight);
				}
			}
		}

		if (KEY_PRESSED(KEY::D) && m_RigidBody->IsGround())
		{
			SetState(PLAYER_STATE::SLASH);

			if (GetDir() == DIRECTION::LEFT)
			{	
				m_SlashMaxRange += m_SlashSpeed * DT;
				m_Pos += Vec2(-1.f, 0.f) * m_SlashSpeed * DT;

				m_Animator->Play(L"PlayerSlashLeft", false);
			}
			else if (GetDir() == DIRECTION::RIGHT)
			{
				m_SlashMaxRange += m_SlashSpeed * DT;
				m_Pos += Vec2(1.f, 0.f) * m_SlashSpeed * DT;


				m_Animator->Play(L"PlayerSlashRight", false);

			}
		}

		if (350.f < m_SlashMaxRange)
		{
			m_SlashMaxRange = 0.f;
			m_Slash = false;
		}
	}


	if (L"PlayerSlashLeft" == m_Animator->GetCurAnim()->GetName())
	{
		if (m_Animator->IsFinish())
		{
			m_State = PLAYER_STATE::IDLE;
			m_Slash = true;
			m_Animator->Play(L"PlayerIdleLeft", true);
		}
	}
	else if (L"PlayerSlashRight" == m_Animator->GetCurAnim()->GetName())
	{
		if (m_Animator->IsFinish())
		{
			m_State = PLAYER_STATE::IDLE;
			m_Slash = true;
			m_Animator->Play(L"PlayerIdleRight", true);
		}
	}


	// ==============================
	//    크로스 더 스틱스 / SPECIAL
	// ==============================



	if (KEY_TAP(KEY::F) && m_RigidBody->IsGround())
	{
		m_State = PLAYER_STATE::SPECIAL;

		if (GetDir() == DIRECTION::LEFT)
		{
			m_Animator->Play(L"PlayerSpecialLeft", false);

			// 크로스 더 스틱스 스킬 이펙트

			qSkill_special_left* pSpecialLeft = new qSkill_special_left;
			pSpecialLeft->SetName(L"SpecialLeft");
			

			Vec2 vSpecialLeftPos = GetPos() + Vec2(-100.f, -130.f);
			Vec2 vSpecialLeftScale = Vec2(500.f, 400.f);

			pSpecialLeft->SetPos(vSpecialLeftPos);
			pSpecialLeft->SetScale(vSpecialLeftScale);

			if (L"SpecialLeft" == pSpecialLeft->GetName())
			{
				SpawnObject(qLevelMgr::GetInst()->GetCurrentLevel(), LAYER_TYPE::PLAYER_SKILL, pSpecialLeft);
			}

		}
		else if (GetDir() == DIRECTION::RIGHT)
		{
			m_Animator->Play(L"PlayerSpecialRight", false);

			// 크로스 더 스틱스 스킬 이펙트

			qSkill_special_right* pSpecialRight = new qSkill_special_right;
			pSpecialRight->SetName(L"SpecialRight");
			

			Vec2 vSpecialRightPos = GetPos() + Vec2(100.f, -130.f);
			Vec2 vSpecialRightScale = Vec2(500.f, 400.f);

			pSpecialRight->SetPos(vSpecialRightPos);
			pSpecialRight->SetScale(vSpecialRightScale);

			if (L"SpecialRight" == pSpecialRight->GetName())
			{
				SpawnObject(qLevelMgr::GetInst()->GetCurrentLevel(), LAYER_TYPE::PLAYER_SKILL, pSpecialRight);
			}
		}
	}

	if (L"PlayerSpecialLeft" == m_Animator->GetCurAnim()->GetName())
	{
		if (m_Animator->IsFinish())
		{
			m_State = PLAYER_STATE::IDLE;
			m_Slash = true;
			m_Animator->Play(L"PlayerIdleLeft", true);
		}
	}
	else if (L"PlayerSpecialRight" == m_Animator->GetCurAnim()->GetName())
	{
		if (m_Animator->IsFinish())
		{
			m_State = PLAYER_STATE::IDLE;
			m_Slash = true;
			m_Animator->Play(L"PlayerIdleRight", true);
		}
	}

	// ======================
	//     트루사이트 / BUFF
	// ======================

	if (KEY_TAP(KEY::G) && m_RigidBody->IsGround())
	{
		// 트루 사이트 스킬 이펙트
		qSkill_buff* pBuff = new qSkill_buff;
		pBuff->SetName(L"Buff");

		Vec2 vBuffPos = GetPos() + Vec2(0.f, -100.f);
		Vec2 vBuffScale = Vec2(400.f, 400.f);

		pBuff->SetPos(vBuffPos);
		pBuff->SetScale(vBuffScale);

		
		if (L"Buff" == pBuff->GetName())
		{
			SpawnObject(qLevelMgr::GetInst()->GetCurrentLevel(), LAYER_TYPE::PLAYER_SKILL, pBuff);
		}
	}

	//SPACE 누르면 점프!

	if (L"PlayerJumpLeft" == m_Animator->GetCurAnim()->GetName())
	{
		if (m_RigidBody->IsGround())
		{
			if (KEY_PRESSED(KEY::LEFT))
			{
				m_State = PLAYER_STATE::MOVE;
				m_Slash = true;
				m_Animator->Play(L"PlayerMoveLeft", true);
			}
			else
			{
				m_State = PLAYER_STATE::IDLE;
				m_Slash = true;
				m_Animator->Play(L"PlayerIdleLeft", true);
			}
		}
		else
		{
			if (KEY_PRESSED(KEY::LEFT))
			{
				m_Pos += Vec2(-1.f, 0.f) * m_Speed * DT;
			}

			if (KEY_PRESSED(KEY::LEFT) && KEY_TAP(KEY::SPACE))
			{
				if (m_DoubleJumpCount > m_CurJumpCount)
				{
					DoubleJump();
					m_CurJumpCount += 1;
				}
			}
		}

	}
	else if (L"PlayerJumpRight" == m_Animator->GetCurAnim()->GetName())
	{
		if (m_RigidBody->IsGround())
		{
			if (KEY_PRESSED(KEY::RIGHT))
			{
				m_State = PLAYER_STATE::MOVE;
				m_Animator->Play(L"PlayerMoveRight", true);
			}
			else
			{
				m_State = PLAYER_STATE::IDLE;
				m_Slash = true;
				m_Animator->Play(L"PlayerIdleRight", true);
			}
		}
		else
		{
			if (KEY_PRESSED(KEY::RIGHT))
			{
				m_Pos += Vec2(1.f, 0.f) * m_Speed * DT;
			}

			if (KEY_PRESSED(KEY::RIGHT) && KEY_TAP(KEY::SPACE))
			{
				if (m_DoubleJumpCount > m_CurJumpCount)
				{
					DoubleJump();
					m_CurJumpCount += 1;
				}

			}
			
		}
	}

	if (KEY_TAP(KEY::SPACE))
	{
		//Shoot();

		if (m_DoubleJumpCount > m_CurJumpCount)
		{
			Jump();

			if (m_CurJumpCount == 1)
			{
				qSkill_highjump* pHighJump = new qSkill_highjump;
				pHighJump->SetName(L"Highjump");

				Vec2 vHighJumpPos = GetPos() + Vec2(0.f, 50.f);
				Vec2 vHighJumpScale = Vec2(185.f, 255.f);

				pHighJump->SetPos(vHighJumpPos);
				pHighJump->SetScale(vHighJumpScale);

				if (L"Highjump" == pHighJump->GetName())
				{
					// TASK
					SpawnObject(qLevelMgr::GetInst()->GetCurrentLevel(), LAYER_TYPE::PLAYER_SKILL, pHighJump);
				}
			}

			m_CurJumpCount += 1;
		}

		if (GetDir() == DIRECTION::LEFT)
		{
			m_Animator->Play(L"PlayerJumpLeft", true);

		}
		else if (GetDir() == DIRECTION::RIGHT)
		{
			m_Animator->Play(L"PlayerJumpRight", true);
		}

	}

	SetPos(m_Pos);

	
	if (m_Portal)
	{
		if (pCurLevel->GetName() == L"Stage1")
		{
			if (KEY_TAP(KEY::UP))
			{
				ChangeLevel(LEVEL_TYPE::STAGE_02);
			}
		}
		if (pCurLevel->GetName() == L"Stage2")
		{
			if (KEY_TAP(KEY::UP))
			{
				ChangeLevel(LEVEL_TYPE::BOSS_01);
			}
		}
		if (pCurLevel->GetName() == L"Boss1")
		{
			if (KEY_TAP(KEY::UP))
			{
				ChangeLevel(LEVEL_TYPE::BOSS_02);
			}
		}
	}

}





void qPlayer::BeginOverlap(qCollider* _OwnCollider, qObj* _OtherObj, qCollider* _OtherCollider)
{
	if (LAYER_TYPE::MONSTER_BLUE == _OtherObj->GetLayerType() || LAYER_TYPE::MONSTER_RED == _OtherObj->GetLayerType()
		|| LAYER_TYPE::BOSS == _OtherObj->GetLayerType())
	{
		qDamage_miss* pDamageMiss = new qDamage_miss();
		pDamageMiss->SetName(L"DamageMiss");

		Vec2 vDamageMissPos = GetPos() + Vec2(0.f, -50.f);
		Vec2 vDamageMissScale = Vec2(140.f, 60.f);

		pDamageMiss->SetPos(vDamageMissPos);
		pDamageMiss->SetScale(vDamageMissScale);

		if (L"DamageMiss" == pDamageMiss->GetName())
		{
			// TASK
			SpawnObject(qLevelMgr::GetInst()->GetCurrentLevel(), LAYER_TYPE::EFFECT, pDamageMiss);
		}
	}

	if (L"BossSkillBallRight" == _OtherObj->GetName() || L"BossSkillBallLeft" == _OtherObj->GetName()
		|| L"BossSkillTornado" == _OtherObj->GetName())
	{
		SetPlayerHP(GetPlayerHP() - GetPhysicalDamage());

		PlusPhysicalCount();
	}

	if (L"BossSkillGenesis1" == _OtherObj->GetName() || L"BossSkillGenesis2" == _OtherObj->GetName()
		|| L"BossSkillGenesis3" == _OtherObj->GetName() || L"BossSkillGenesis4" == _OtherObj->GetName() || L"BossSkillFirebird" == _OtherObj->GetName())
	{
		SetPlayerHP(GetPlayerHP() - GetMagicDamage());

		PlusMagicCount();
	}



}


void qPlayer::OnOverlap(qCollider* _OwnCollider, qObj* _OtherObj, qCollider* _OtherCollider)
{

}


void qPlayer::EndOverlap(qCollider* _OwnCollider, qObj* _OtherObj, qCollider* _OtherCollider)
{
	int a = 0;
}



//void qPlayer::Shoot()
//{
//	qMissile* pMissile = new qGuideMissile;
//	pMissile->SetName(L"Missile");
//
//	Vec2 vMissilePos = GetPos();
//	vMissilePos.y -= GetScale().y / 2.f;
//
//	pMissile->SetPos(vMissilePos);
//	pMissile->SetScale(Vec2(20.f, 20.f));
//
//	// TASK
//	SpawnObject(qLevelMgr::GetInst()->GetCurrentLevel(), LAYER_TYPE::PLAYER_MISSILE, pMissile);
//
//	// LOG
//	LOG(LOG_TYPE::DBG_LOG, L"미사일 발사!");
//}

void qPlayer::Jump()
{
	m_RigidBody->jump();

	
}

void qPlayer::DoubleJump()
{
	m_RigidBody->doublejump();

	if (DIRECTION::LEFT == GetDir())
	{
		// 더블점프 스킬 이펙트
		qSkill_doublejump_left* pDoubleJumpLeft = new qSkill_doublejump_left;
		pDoubleJumpLeft->SetName(L"DoubleJumpLeft");

		Vec2 vDoubleJumpLeftPos = GetPos() + Vec2(30.f, 0.f);
		Vec2 vDoubleJumpLeftScale = Vec2(255.f, 185.f);

		pDoubleJumpLeft->SetPos(vDoubleJumpLeftPos);
		pDoubleJumpLeft->SetScale(vDoubleJumpLeftScale);
		
		if (L"DoubleJumpLeft" == pDoubleJumpLeft->GetName())
		{
			// TASK
			SpawnObject(qLevelMgr::GetInst()->GetCurrentLevel(), LAYER_TYPE::PLAYER_SKILL, pDoubleJumpLeft);
		}
	}
	else if (DIRECTION::RIGHT == GetDir())
	{
		// 더블점프 스킬 이펙트
		qSkill_doublejump_right* pDoubleJumpRight = new qSkill_doublejump_right;
		pDoubleJumpRight->SetName(L"DoubleJumpRight");

		Vec2 vDoubleJumpRightPos = GetPos() + Vec2(-30.f, 0.f);
		Vec2 vDoubleJumpRightScale = Vec2(255.f, 185.f);

		pDoubleJumpRight->SetPos(vDoubleJumpRightPos);
		pDoubleJumpRight->SetScale(vDoubleJumpRightScale);

		if (L"DoubleJumpRight" == pDoubleJumpRight->GetName())
		{
			// TASK
			SpawnObject(qLevelMgr::GetInst()->GetCurrentLevel(), LAYER_TYPE::PLAYER_SKILL, pDoubleJumpRight);
		}
	}
}





