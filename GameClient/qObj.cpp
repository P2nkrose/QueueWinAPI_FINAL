#include "pch.h"
#include "qObj.h"

#include "qEngine.h"
#include "qTimeMgr.h"
#include "qTaskMgr.h"

#include "qComponent.h"

qObj::qObj()
	: m_Type(LAYER_TYPE::NONE)
	, m_bDead(false)
{
}

qObj::~qObj()
{
	Safe_Del_Vec(m_vecCom);
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
	Rectangle(DC, (int)(m_Pos.x - m_Scale.x * 0.5f)
				, (int)(m_Pos.y - m_Scale.y * 0.5f)
				, (int)(m_Pos.x + m_Scale.x * 0.5f)
				, (int)(m_Pos.y + m_Scale.y * 0.5f));
}


void qObj::Destroy()
{
	tTask task = {};
	task.Type = TASK_TYPE::DELETE_OBJECT;
	task.Param1 = (DWORD_PTR)this;

	qTaskMgr::GetInst()->AddTask(task);
}

qComponent* qObj::AddComponent(qComponent* _Component)
{
	m_vecCom.push_back(_Component);
	_Component->m_Owner = this;

	return _Component;
}