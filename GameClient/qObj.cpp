#include "pch.h"
#include "qObj.h"
#include "qEngine.h"

#include "qTimeMgr.h"

qObj::qObj()
{
}

qObj::~qObj()
{
}


void qObj::begin()
{
	
}

void qObj::tick()
{
	
}

void qObj::finaltick()
{
}

void qObj::render()
{
	Rectangle(DC, m_Pos.x - m_Scale.x * 0.5f
				, m_Pos.y - m_Scale.y * 0.5f
				, m_Pos.x + m_Scale.x * 0.5f
				, m_Pos.y + m_Scale.y * 0.5f);
}


