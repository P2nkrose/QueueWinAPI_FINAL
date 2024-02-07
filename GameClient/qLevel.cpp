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
	// 이전프레임 충돌체 등록 정보 Clear
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
		vector<qObj*>::iterator iter = m_arrObj[i].begin();

		for (; iter != m_arrObj[i].end(); )
		{
			if ((*iter)->IsDead())
			{
				iter = m_arrObj[i].erase(iter);
			}
			else
			{
				(*iter)->render();
				++iter;
			}
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


qObj* qLevel::FindObjectByName(const wstring& _Name)
{
	for (UINT i = 0; i < (UINT)LAYER_TYPE::END; ++i)
	{
		qObj* pFindObj = FindObjectByName((LAYER_TYPE)i, _Name);
		
		if (pFindObj)
		{
			return pFindObj;
		}
	}

	return nullptr;
}

qObj* qLevel::FindObjectByName(LAYER_TYPE _Type, const wstring& _Name)
{
	for (size_t i = 0; i < m_arrObj[(UINT)_Type].size(); ++i)
	{
		if (_Name == m_arrObj[(UINT)_Type][i]->GetName())
		{
			return m_arrObj[(UINT)_Type][i];
		}
	}

	return nullptr;
}

