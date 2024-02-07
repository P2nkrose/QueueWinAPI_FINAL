#include "pch.h"
#include "qTaskMgr.h"

#include "qLevelMgr.h"
#include "qLevel.h"
#include "qObj.h"

qTaskMgr::qTaskMgr()
{

}

qTaskMgr::~qTaskMgr()
{

}


void qTaskMgr::tick()
{
	for (size_t i = 0; i < m_vecTask.size(); ++i)
	{
		switch (m_vecTask[i].Type)
		{
		case TASK_TYPE::SPAWN_OBJECT:
		{
			qLevel* pSpawnLevel = (qLevel*)m_vecTask[i].Param1;
			LAYER_TYPE Layer = (LAYER_TYPE)m_vecTask[i].Param2;
			qObj* pObj = (qObj*)m_vecTask[i].Param3;

			if (qLevelMgr::GetInst()->GetCurrentLevel() != pSpawnLevel)
			{
				delete pObj;
			}
			pSpawnLevel->AddObject(Layer, pObj);
		}
			break;
		case TASK_TYPE::DELETE_OBJECT:

			break;
		case TASK_TYPE::CHANGE_LEVEL:
			break;
		default:
			break;
		}
	}

	m_vecTask.clear();
}
