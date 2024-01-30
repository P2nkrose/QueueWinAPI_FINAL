#include "pch.h"
#include "qObj.h"

#include "qEngine.h"
#include "qTimeMgr.h"

#include "qComponent.h"

qObj::qObj()
{
}

qObj::~qObj()
{
	Save_Del_Vec(m_vecCom);
}


void qObj::begin()
{
	
}

void qObj::tick()
{
	
}

void qObj::finaltick()
{
	for (size_t i = 0; i < m_vecCom.size(); ++i)
	{
		m_vecCom[i]->finaltick();
	}
}

void qObj::render()
{
	Rectangle(DC, m_Pos.x - m_Scale.x * 0.5f
				, m_Pos.y - m_Scale.y * 0.5f
				, m_Pos.x + m_Scale.x * 0.5f
				, m_Pos.y + m_Scale.y * 0.5f);
}


qComponent* qObj::AddComponent(qComponent* _Component)
{
	m_vecCom.push_back(_Component);
	_Component->m_Owner = this;

	return _Component;
}