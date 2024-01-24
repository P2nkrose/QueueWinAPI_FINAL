#pragma once


enum PEN_TYPE
{
	RED_PEN,
	BLUE_PEN,
	GREEN_PEN,



	PEN_END,
};


enum class LEVEL_TYPE
{
	LOGO_START,
	EDITOR,
	
	STAGE_01,
	STAGE_02,

	BOSS_01,

	END,
};


enum class PLAYER_STATE
{
	IDLE,
	RUN,
	MOVE,
	DASH,
	ATTACK,
	HIT,
	DEAD,

	END,
};