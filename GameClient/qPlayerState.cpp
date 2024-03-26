#include "pch.h"
#include "qplayerstate.h"

#include "qobj.h"
#include "qlevelmgr.h"
#include "qlevel.h"

#include "qplayer.h"

#include "qcollider.h"
#include "qanimator.h"
#include "qanimation.h"
#include "qdbgrender.h"
#include "qrigidbody.h"
#include "qcomponent.h"

#include "qmissile.h"
#include "qguidemissile.h"

#include "qdbgrender.h"
#include "qcamera.h"

qPlayerState::qPlayerState()
	: m_State(PLAYER_STATE::IDLE)
	, m_Dir(DIRECTION::LEFT)
	, m_PlayerImg(nullptr)
	, m_Animator(nullptr)
	, m_RigidBody(nullptr)
	, m_Collider(nullptr)
	, m_DoubleJumpCount(2)
	, m_CurJumpCount(0)
	, m_Jump(false)
	, m_Player(nullptr)
	, m_Speed(0)
	, m_Hud(0)
{

}

qPlayerState::~qPlayerState()
{
}

void qPlayerState::Enter()
{
	if (DIRECTION::RIGHT == GetDirection())
	{
		SetDirection(DIRECTION::RIGHT);
		SetState(PLAYER_STATE::IDLE);
	}
	else if (DIRECTION::LEFT == GetDirection())
	{
		SetDirection(DIRECTION::LEFT);
		SetState(PLAYER_STATE::IDLE);
	}

}


void qPlayerState::FinalTick()
{
	// 블랙보드로 Player의 정보를 받아온다.
	m_Speed = GetBlackboardData<float>(L"pSpeed");
	m_Hud = GetBlackboardData<float>(L"pHud");
	m_Player = GetBlackboardData<qObj*>(L"pPlayer");


	if (nullptr == m_Animator && nullptr == m_RigidBody && nullptr == m_Collider)
	{
		m_Animator = GetObj()->GetComponent<qAnimator>();
		m_RigidBody = GetObj()->GetComponent<qRigidbody>();
		m_Collider = GetObj()->GetComponent<qCollider>();
	}


	m_Pos = m_Player->GetPos();

	switch (m_State)
	{
	case PLAYER_STATE::IDLE:
		Idle();
		break;
	case PLAYER_STATE::MOVE:
		Move();
		break;
	case PLAYER_STATE::BUFF:
		Buff();
	case PLAYER_STATE::ATTACK:
		Attack();
		break;
	case PLAYER_STATE::MISSILE:
		Missile();
		break;
	case PLAYER_STATE::SLASH:
		Slash();
		break;
	case PLAYER_STATE::SPECIAL:
		Special();
		break;
	case PLAYER_STATE::DOWN:
		Down();
		break;
	case PLAYER_STATE::DOWN_ATTACK:
		DownAttack();
		break;
	case PLAYER_STATE::JUMP:
		Jump();
		break;
	case PLAYER_STATE::ROPE:
		Rope();
		break;

	default:
		break;
	}
}



void qPlayerState::Idle()
{
	if (GetDirection() == DIRECTION::LEFT)
	{
		SetState(PLAYER_STATE::IDLE);
		SetDirection(DIRECTION::LEFT);
		m_Animator->Play(L"PlayerIdleLeft", true);
	}
	else if (m_Dir == DIRECTION::RIGHT)
	{
		SetState(PLAYER_STATE::IDLE);
		SetDirection(DIRECTION::RIGHT);
		m_Animator->Play(L"PlayerIdleRight", true);
	}

	if (KEY_PRESSED(KEY::LEFT))
	{
		SetDirection(DIRECTION::LEFT);
		SetState(PLAYER_STATE::MOVE);
		m_Animator->Play(L"PlayerMoveLeft", true);
	}
	else if (KEY_PRESSED(KEY::RIGHT))
	{
		SetDirection(DIRECTION::RIGHT);
		SetState(PLAYER_STATE::MOVE);
		m_Animator->Play(L"PlayerMoveRight", true);
	}
	else if (KEY_TAP(KEY::DOWN))
	{
		SetState(PLAYER_STATE::DOWN);
	}


	if (KEY_TAP(KEY::A))
	{
		SetState(PLAYER_STATE::BUFF);
	}
	else if (KEY_TAP(KEY::S))
	{
		SetState(PLAYER_STATE::ATTACK);
	}
	else if (KEY_TAP(KEY::D))
	{
		SetState(PLAYER_STATE::MISSILE);
	}
	else if (KEY_TAP(KEY::F))
	{
		SetState(PLAYER_STATE::SLASH);
	}
	else if (KEY_TAP(KEY::G))
	{
		SetState(PLAYER_STATE::SPECIAL);
	}

}

void qPlayerState::Move()
{
	m_State = PLAYER_STATE::MOVE;

	if (KEY_PRESSED(KEY::LEFT))
	{
		m_Pos += Vec2(-1.f, 0.f) * m_Speed * DT;
		SetDirection(DIRECTION::LEFT);
		m_Animator->Play(L"PlayerMoveLeft", true);
		GetObj()->SetPos(m_Pos);
	}
	else if (KEY_RELEASED(KEY::LEFT))
	{
		SetDirection(DIRECTION::LEFT);
		SetState(PLAYER_STATE::IDLE);
	}


	if (KEY_PRESSED(KEY::RIGHT))
	{
		m_Pos += Vec2(1.f, 0.f) * m_Speed * DT;
		SetDirection(DIRECTION::RIGHT);
		m_Animator->Play(L"PlayerMoveRight", true);
		GetObj()->SetPos(m_Pos);
	}
	else if (KEY_RELEASED(KEY::RIGHT))
	{
		SetDirection(DIRECTION::RIGHT);
		SetState(PLAYER_STATE::IDLE);
	}

	
}

void qPlayerState::Down()
{
	if (KEY_PRESSED(KEY::DOWN))
	{
		if (m_Dir == DIRECTION::LEFT)
		{
			m_Animator->Play(L"PlayerDownLeft", true);
		}
		else if (m_Dir == DIRECTION::RIGHT)
		{
			m_Animator->Play(L"PlayerDownRight", true);
		}

		if (KEY_TAP(KEY::SPACE))
		{
			m_State = PLAYER_STATE::DOWN_ATTACK;
		}
	}
	else if (KEY_RELEASED(KEY::DOWN))
	{
		m_State = PLAYER_STATE::IDLE;
	}
}

void qPlayerState::DownAttack()
{
	m_State = PLAYER_STATE::DOWN_ATTACK;

	if (m_Dir == DIRECTION::LEFT)
	{
		m_Animator->Play(L"PlayerDownAttackLeft", true);
	}
	else if (m_Dir == DIRECTION::RIGHT)
	{
		m_Animator->Play(L"PlayerDownAttackRight", true);
	}

}

void qPlayerState::Buff()
{

}

void qPlayerState::Attack()
{

}

void qPlayerState::Missile()
{
}

void qPlayerState::Slash()
{
}

void qPlayerState::Special()
{
}

void qPlayerState::Jump()
{
	qRigidbody* rb = GetObj()->GetComponent<qRigidbody>();
	
}

void qPlayerState::Rope()
{
}



void qPlayerState::Exit()
{
}