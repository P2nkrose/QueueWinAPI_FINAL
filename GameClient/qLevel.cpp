#include "pch.h"
#include "qLevel.h"

#include "qObj.h"
#include "qCollider.h"

qLevel::qLevel()
{

}

qLevel::~qLevel()
{
	for (UINT i = 0; i < (UINT)LAYER_TYPE::END; ++i)
	{
		Safe_Del_Vec(m_arrObj[i]);
	}
	
}


void qLevel::begin()
{
	for (int i = 0; i < (UINT)LAYER_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); ++j)
		{
			m_arrObj[i][j]->begin();
		}
	}

	
}

void qLevel::tick()
{
	for (int i = 0; i < (UINT)LAYER_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); ++j)
		{
			m_arrObj[i][j]->tick();
		}
	}
}

void qLevel::finaltick()
{
	// ���������� �浹ü ��� ���� Clear
	for (UINT i = 0; i < (UINT)LAYER_TYPE::END; ++i)
	{
		m_arrCollider[i].clear();
	}


	for (int i = 0; i < (UINT)LAYER_TYPE::END; i++)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); ++j)
		{
			m_arrObj[i][j]->finaltick();
		}
	}
}

void qLevel::render()
{
	for (int i = 0; i < (UINT)LAYER_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); ++j)
		{
			m_arrObj[i][j]->render();
		}
	}
}

void qLevel::AddObject(LAYER_TYPE _Layer, qObj* _Obj)
{
	m_arrObj[(UINT)_Layer].push_back(_Obj);
	_Obj->m_Type = _Layer;
}


void qLevel::RegisterCollider(qCollider* _Collider)
{
	LAYER_TYPE Layer = _Collider->GetOwner()->GetLayerType();
	m_arrCollider[(UINT)Layer].push_back(_Collider);
}

