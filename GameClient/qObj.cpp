#include "pch.h"
#include "qObj.h"

#include "qEngine.h"
#include "qTimeMgr.h"
#include "qTaskMgr.h"

#include "qComponent.h"
#include "qAnimator.h"

qObj::qObj()
	: m_Type(LAYER_TYPE::NONE)
	, m_bDead(false)
	, m_Animator(nullptr)
	, m_AttackDamage(1500000)
	, m_MissileDamage(1600000)
	, m_SlashDamage(1700000)
	, m_SpecialDamage(2600000)
{
}

qObj::qObj(const qObj& _Other)
	: qEntity(_Other)
	, m_PrevPos(_Other.m_PrevPos)
	, m_Scale(_Other.m_Scale)
	, m_Animator(nullptr)
	, m_Type(_Other.m_Type)
	, m_CenterPos(_Other.m_CenterPos)
	, m_bDead(false)
	, m_Dir(_Other.m_Dir)
	, m_AttackDamage(_Other.m_AttackDamage)
	, m_MissileDamage(_Other.m_MissileDamage)
	, m_SlashDamage(_Other.m_SlashDamage)
	, m_SpecialDamage(_Other.m_SpecialDamage)
{
	for (size_t i = 0; i < _Other.m_vecCom.size(); ++i)
	{
		AddComponent(_Other.m_vecCom[i]->Clone());
	}

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
	if (nullptr == m_Animator)
		return;

	m_Animator->render();
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

	if (m_Animator == nullptr)
	{
		// 오브젝트에 추가된 컴포넌트가 Animator 면 별도의 포인터로 따로 가리킨다.
		m_Animator = dynamic_cast<qAnimator*>(_Component);
	}

	return _Component;
}