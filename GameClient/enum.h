#pragma once


enum class PEN_TYPE
{
	PEN_RED,
	PEN_GREEN,
	PEN_BLUE,

	END,
};


enum class BRUSH_TYPE
{
	BRUSH_RED,
	BRUSH_GREEN,
	BRUSH_BLUE,
	BRUSH_GRAY,

	BRUSH_HOLLOW,
	BRUSH_BLACK,

	END,
};


enum class LEVEL_TYPE
{
	LOGO_START,
	EDITOR,
	
	STAGE_01,
	STAGE_02,

	BOSS_01,
	BOSS_02,

	END,
};


enum class PLAYER_STATE
{
	IDLE,
	MOVE,
	ATTACK,
	DOWN,
	DOWN_ATTACK,
	JUMP,
	ROPE,

	END,
};


enum class PLAYER_SKILL
{
	BUFF,		// Ʈ�����Ʈ (������)
	ATTACK,		// �ֶ󽽷��� (�⺻��)
	MISSILE,	// �糪 ����̵� (����ź)
	STRIKE,		// ���� ���� (�����ϼ�)
	SPECIAL,	// �����ÿ� (ũ�� �ѹ�)

	END,
};

enum class BOSS_SKILL
{
	MISSILE,	// �߻�
	DARK,		// ��ũ ���׽ý�
	FIRE,		// �һ�

	END,
};


enum class DBG_SHAPE
{
	CIRCLE,
	RECT,
	LINE
};


enum class LAYER_TYPE
{
	DEFAULT,
	BACKGROUND,
	TILE,
	PLATFORM,
	PLAYER,
	MONSTER,
	PLAYER_MISSILE,
	MONSTER_MISSILE,

	FORCE,

	UI = 15,
	END = 16,

	NONE = -1,

};


enum class TASK_TYPE
{
	SPAWN_OBJECT,		// 1 : Level,  2 : LAYER_TYPE,  3 : Object Adress
	DELETE_OBJECT,		// 1 : Object Adress
	CHANGE_LEVEL,
};


enum class LOG_TYPE
{
	DBG_LOG,
	DBG_WARNING,
	DBG_ERROR,
};