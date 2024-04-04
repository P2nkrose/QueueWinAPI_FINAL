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
	LOGO,
	START,
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
	MISSILE,
	SLASH,
	SPECIAL,
	BUFF,
	DOWN,
	DOWN_ATTACK,
	JUMP,
	ROPE,

	END,
};

enum class DIRECTION
{
	RIGHT,
	LEFT,
	DOWN,
};


enum class PLAYER_SKILL
{
	ATTACK,		// 솔라슬래시 (기본기)
	MISSILE,	// 루나 디바이드 (유도탄)
	SLASH,		// 라우드 러쉬 (벽력일섬)
	SPECIAL,	// 크로스 더 스틱스 (크게 한방)
	BUFF,		// 트루사이트 (버프기)
	DOUBLEJUMP,	// 더블점프

	END,
};

enum class BOSS_SKILL
{
	MISSILE,	// 발사
	DARK,		// 다크 제네시스
	FIRE,		// 불새

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

	PLATFORM,
	ROPE,
	PORTAL,

	PLAYER,
	
	MONSTER_BLUE,
	MONSTER_RED,

	DUMMY_BLUE,
	DUMMY_RED,

	BOSS,

	PLAYER_SKILL,
	EFFECT,

	BOSS_SKILL,

	UI,
	END,

	NONE = -1,

};


enum class TASK_TYPE
{
	SPAWN_OBJECT,		// 1 : Level,  2 : LAYER_TYPE,  3 : Object Adress
	DELETE_OBJECT,		// 1 : Object Adress
	CHANGE_LEVEL,
	UI_LBTN_DOWN,		// 1 : UI Object Adress, 2 : true or false
};


enum class LOG_TYPE
{
	DBG_LOG,
	DBG_WARNING,
	DBG_ERROR,
};


enum class EDIT_TYPE
{
	PLATFORM,
	ROPE,
	PORTAL,
	//MONSTER_BLUE,
	//MONSTER_RED,
	DUMMY_BLUE,
	DUMMY_RED,
	END,
};

enum class STAGE_NAME
{
	STAGE1,
	STAGE2,
	BOSS1,
	BOSS2,
};