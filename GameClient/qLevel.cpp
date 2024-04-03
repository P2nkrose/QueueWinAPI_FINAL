#include "pch.h"
#include "qLevel.h"

#include "qObj.h"
#include "qCollider.h"
#include "qPathMgr.h"

#include "qPlatform.h"
#include "qRope.h"
#include "qPortal.h"
#include "qMonster_red.h"
#include "qMonster_blue.h"
#include "qDummy_blue.h"
#include "qDummy_red.h"

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

void qLevel::DeleteAllObjects()
{
	for (UINT i = 0; i < (UINT)LAYER_TYPE::END; ++i)
	{
		DeleteObjects((LAYER_TYPE)i);
	}
}

void qLevel::DeleteObjects(LAYER_TYPE _LayerType)
{
	vector<qObj*>& vecObjects = m_arrObj[(UINT)_LayerType];

	if (vecObjects.empty())
		return;

	for (size_t i = 0; i < vecObjects.size(); ++i)
	{
		delete vecObjects[i];
	}

	vecObjects.clear();
}





void qLevel::SavePlatform(const wstring& _strRelativePath)
{
	wstring strFullPath = qPathMgr::GetInst()->GetContentPath();
	if (STAGE_NAME::STAGE1 == m_stageName)
	{
		strFullPath += L"edit\\stage1\\";
	}
	else if (STAGE_NAME::STAGE2 == m_stageName)
	{
		strFullPath += L"edit\\stage2\\";
	}
	else if (STAGE_NAME::BOSS1 == m_stageName)
	{
		strFullPath += L"edit\\boss1\\";
	}
	else if (STAGE_NAME::BOSS2 == m_stageName)
	{
		strFullPath += L"edit\\boss2\\";
	}
	
	strFullPath += _strRelativePath;

	FILE* pFile = nullptr;


	_wfopen_s(&pFile, strFullPath.c_str(), L"wb");

	if (nullptr == pFile)
	{
		MessageBox(qEngine::GetInst()->GetMainWnd(), L"파일 저장 실패", L"Error", MB_OK);
		return;
	}

	size_t len = m_arrObj[(UINT)LAYER_TYPE::PLATFORM].size();

	fwrite(&len, sizeof(size_t), 1, pFile);

	for (size_t i = 0; i < m_arrObj[(UINT)LAYER_TYPE::PLATFORM].size(); ++i)
	{
		Vec2 vPos = m_arrObj[(UINT)LAYER_TYPE::PLATFORM][i]->GetPos();
		Vec2 vScale = m_arrObj[(UINT)LAYER_TYPE::PLATFORM][i]->GetScale();

		fwrite(&vPos, sizeof(Vec2), 1, pFile);
		fwrite(&vScale, sizeof(Vec2), 1, pFile);
	}

	fclose(pFile);

	//for (size_t i = 0; i < m_arrObj[(UINT)LAYER_TYPE::PLATFORM].size(); ++i)
	//{
	//	delete m_arrObj[(UINT)LAYER_TYPE::PLATFORM][i];
	//}
	//m_arrObj[(UINT)LAYER_TYPE::PLATFORM].resize(0);
}

void qLevel::SaveRope(const wstring& _strRelativePath)
{
	wstring strFullPath = qPathMgr::GetInst()->GetContentPath();
	
	if (STAGE_NAME::STAGE1 == m_stageName)
	{
		strFullPath += L"edit\\stage1\\";
	}
	else if (STAGE_NAME::STAGE2 == m_stageName)
	{
		strFullPath += L"edit\\stage2\\";
	}
	else if (STAGE_NAME::BOSS1 == m_stageName)
	{
		strFullPath += L"edit\\boss1\\";
	}
	else if (STAGE_NAME::BOSS2 == m_stageName)
	{
		strFullPath += L"edit\\boss2\\";
	}

	strFullPath += _strRelativePath;

	FILE* pFile = nullptr;


	_wfopen_s(&pFile, strFullPath.c_str(), L"wb");

	if (nullptr == pFile)
	{
		MessageBox(qEngine::GetInst()->GetMainWnd(), L"파일 저장 실패", L"Error", MB_OK);
		return;
	}

	size_t len = m_arrObj[(UINT)LAYER_TYPE::ROPE].size();

	fwrite(&len, sizeof(size_t), 1, pFile);

	for (size_t i = 0; i < m_arrObj[(UINT)LAYER_TYPE::ROPE].size(); ++i)
	{
		Vec2 vPos = m_arrObj[(UINT)LAYER_TYPE::ROPE][i]->GetPos();
		Vec2 vScale = m_arrObj[(UINT)LAYER_TYPE::ROPE][i]->GetScale();

		fwrite(&vPos, sizeof(Vec2), 1, pFile);
		fwrite(&vScale, sizeof(Vec2), 1, pFile);
	}

	fclose(pFile);

	//for (size_t i = 0; i < m_arrObj[(UINT)LAYER_TYPE::ROPE].size(); ++i)
	//{
	//	delete m_arrObj[(UINT)LAYER_TYPE::ROPE][i];
	//}
	//m_arrObj[(UINT)LAYER_TYPE::ROPE].resize(0);
}

void qLevel::SavePortal(const wstring& _strRelativePath)
{
	wstring strFullPath = qPathMgr::GetInst()->GetContentPath();

	if (STAGE_NAME::STAGE1 == m_stageName)
	{
		strFullPath += L"edit\\stage1\\";
	}
	else if (STAGE_NAME::STAGE2 == m_stageName)
	{
		strFullPath += L"edit\\stage2\\";
	}
	else if (STAGE_NAME::BOSS1 == m_stageName)
	{
		strFullPath += L"edit\\boss1\\";
	}
	else if (STAGE_NAME::BOSS2 == m_stageName)
	{
		strFullPath += L"edit\\boss2\\";
	}

	strFullPath += _strRelativePath;

	FILE* pFile = nullptr;


	_wfopen_s(&pFile, strFullPath.c_str(), L"wb");

	if (nullptr == pFile)
	{
		MessageBox(qEngine::GetInst()->GetMainWnd(), L"파일 저장 실패", L"Error", MB_OK);
		return;
	}

	size_t len = m_arrObj[(UINT)LAYER_TYPE::PORTAL].size();

	fwrite(&len, sizeof(size_t), 1, pFile);

	for (size_t i = 0; i < m_arrObj[(UINT)LAYER_TYPE::PORTAL].size(); ++i)
	{
		Vec2 vPos = m_arrObj[(UINT)LAYER_TYPE::PORTAL][i]->GetPos();
		Vec2 vScale = m_arrObj[(UINT)LAYER_TYPE::PORTAL][i]->GetScale();

		fwrite(&vPos, sizeof(Vec2), 1, pFile);
		fwrite(&vScale, sizeof(Vec2), 1, pFile);
	}

	fclose(pFile);
}



void qLevel::SaveMonster_blue(const wstring& _strRelativePath)
{
	wstring strFullPath = qPathMgr::GetInst()->GetContentPath();

	if (STAGE_NAME::STAGE1 == m_stageName)
	{
		strFullPath += L"edit\\stage1\\";
	}
	else if (STAGE_NAME::STAGE2 == m_stageName)
	{
		strFullPath += L"edit\\stage2\\";
	}
	else if (STAGE_NAME::BOSS1 == m_stageName)
	{
		strFullPath += L"edit\\boss1\\";
	}
	else if (STAGE_NAME::BOSS2 == m_stageName)
	{
		strFullPath += L"edit\\boss2\\";
	}

	 strFullPath += _strRelativePath;

	FILE* pFile = nullptr;

	_wfopen_s(&pFile, strFullPath.c_str(), L"wb");

	if (nullptr == pFile)
	{
		MessageBox(qEngine::GetInst()->GetMainWnd(), L"파일 저장 실패", L"Error", MB_OK);
		return;
	}

	size_t len = m_arrObj[(UINT)LAYER_TYPE::DUMMY_BLUE].size();

	fwrite(&len, sizeof(size_t), 1, pFile);

	for (size_t i = 0; i < m_arrObj[(UINT)LAYER_TYPE::DUMMY_BLUE].size(); ++i)
	{
		Vec2 vPos = m_arrObj[(UINT)LAYER_TYPE::DUMMY_BLUE][i]->GetPos();
		Vec2 vScale = m_arrObj[(UINT)LAYER_TYPE::DUMMY_BLUE][i]->GetScale();

		fwrite(&vPos, sizeof(Vec2), 1, pFile);
		fwrite(&vScale, sizeof(Vec2), 1, pFile);
	}

	fclose(pFile);
}


void qLevel::SaveMonster_red(const wstring& _strRelativePath)
{
	wstring strFullPath = qPathMgr::GetInst()->GetContentPath();

	if (STAGE_NAME::STAGE1 == m_stageName)
	{
		strFullPath += L"edit\\stage1\\";
	}
	else if (STAGE_NAME::STAGE2 == m_stageName)
	{
		strFullPath += L"edit\\stage2\\";
	}
	else if (STAGE_NAME::BOSS1 == m_stageName)
	{
		strFullPath += L"edit\\boss1\\";
	}
	else if (STAGE_NAME::BOSS2 == m_stageName)
	{
		strFullPath += L"edit\\boss2\\";
	}

	strFullPath += _strRelativePath;

	FILE* pFile = nullptr;

	_wfopen_s(&pFile, strFullPath.c_str(), L"wb");

	if (nullptr == pFile)
	{
		MessageBox(qEngine::GetInst()->GetMainWnd(), L"파일 저장 실패", L"Error", MB_OK);
		return;
	}

	size_t len = m_arrObj[(UINT)LAYER_TYPE::DUMMY_RED].size();

	fwrite(&len, sizeof(size_t), 1, pFile);

	for (size_t i = 0; i < m_arrObj[(UINT)LAYER_TYPE::DUMMY_RED].size(); ++i)
	{
		Vec2 vPos = m_arrObj[(UINT)LAYER_TYPE::DUMMY_RED][i]->GetPos();
		Vec2 vScale = m_arrObj[(UINT)LAYER_TYPE::DUMMY_RED][i]->GetScale();

		fwrite(&vPos, sizeof(Vec2), 1, pFile);
		fwrite(&vScale, sizeof(Vec2), 1, pFile);
	}

	fclose(pFile);
}



void qLevel::LoadPlatform(const wstring& _strRelativePath)
{
	wstring strFullPath = qPathMgr::GetInst()->GetContentPath();
	if (L"Stage1" == GetName())
	{
		strFullPath += L"edit\\stage1\\";
	}
	else if (L"Stage2" == GetName())
	{
		strFullPath += L"edit\\stage2\\";
	}
	else if (L"Boss1" == GetName())
	{
		strFullPath += L"edit\\boss1\\";
	}
	else if (L"Boss2" == GetName())
	{
		strFullPath += L"edit\\boss2\\";
	}

	strFullPath += _strRelativePath;

	FILE* pFile = nullptr;

	_wfopen_s(&pFile, strFullPath.c_str(), L"rb");

	if (nullptr == pFile)
		return;

	size_t len = 0;

	fread(&len, sizeof(size_t), 1, pFile);

	for (size_t i = 0; i < len; ++i)
	{
		Vec2 vPos;
		Vec2 vScale;

		fread(&vPos, sizeof(Vec2), 1, pFile);
		fread(&vScale, sizeof(Vec2), 1, pFile);

		qPlatform* pPlatform = new qPlatform(vPos, vScale);
		AddObject(LAYER_TYPE::PLATFORM, pPlatform);
	}

	fclose(pFile);
}

void qLevel::LoadRope(const wstring& _strRelativePath)
{
	wstring strFullPath = qPathMgr::GetInst()->GetContentPath();

	if (L"Stage1" == GetName())
	{
		strFullPath += L"edit\\stage1\\";
	}
	else if (L"Stage2" == GetName())
	{
		strFullPath += L"edit\\stage2\\";
	}
	else if (L"Boss1" == GetName())
	{
		strFullPath += L"edit\\boss1\\";
	}
	else if (L"Boss2" == GetName())
	{
		strFullPath += L"edit\\boss2\\";
	}

	strFullPath += _strRelativePath;

	FILE* pFile = nullptr;

	_wfopen_s(&pFile, strFullPath.c_str(), L"rb");

	if (nullptr == pFile)
		return;

	size_t len = 0;

	fread(&len, sizeof(size_t), 1, pFile);

	for (size_t i = 0; i < len; ++i)
	{
		Vec2 vPos;
		Vec2 vScale;

		fread(&vPos, sizeof(Vec2), 1, pFile);
		fread(&vScale, sizeof(Vec2), 1, pFile);

		qRope* pRope = new qRope(vPos, vScale);
		AddObject(LAYER_TYPE::ROPE, pRope);
	}

	fclose(pFile);
}

void qLevel::LoadPortal(const wstring& _strRelativePath)
{
	wstring strFullPath = qPathMgr::GetInst()->GetContentPath();
	if (L"Stage1" == GetName())
	{
		strFullPath += L"edit\\stage1\\";
	}
	else if (L"Stage2" == GetName())
	{
		strFullPath += L"edit\\stage2\\";
	}
	else if (L"Boss1" == GetName())
	{
		strFullPath += L"edit\\boss1\\";
	}
	else if (L"Boss2" == GetName())
	{
		strFullPath += L"edit\\boss2\\";
	}

	strFullPath += _strRelativePath;

	FILE* pFile = nullptr;

	_wfopen_s(&pFile, strFullPath.c_str(), L"rb");

	if (nullptr == pFile)
		return;

	size_t len = 0;

	fread(&len, sizeof(size_t), 1, pFile);

	for (size_t i = 0; i < len; ++i)
	{
		Vec2 vPos;
		Vec2 vScale;

		fread(&vPos, sizeof(Vec2), 1, pFile);
		fread(&vScale, sizeof(Vec2), 1, pFile);

		qPortal* pPortal = new qPortal(vPos, vScale);
		AddObject(LAYER_TYPE::PORTAL, pPortal);
	}

	fclose(pFile);
}

void qLevel::LoadMonster_blue(const wstring& _strRelativePath)
{
	wstring strFullPath = qPathMgr::GetInst()->GetContentPath();

	if (L"Stage1" == GetName())
	{
		strFullPath += L"edit\\stage1\\";
	}
	else if (L"Stage2" == GetName())
	{
		strFullPath += L"edit\\stage2\\";
	}
	else if (L"Boss1" == GetName())
	{
		strFullPath += L"edit\\boss1\\";
	}
	else if (L"Boss2" == GetName())
	{
		strFullPath += L"edit\\boss2\\";
	}


	strFullPath += _strRelativePath;

	FILE* pFile = nullptr;

	_wfopen_s(&pFile, strFullPath.c_str(), L"rb");

	size_t len = 0;

	fread(&len, sizeof(size_t), 1, pFile);

	for (size_t i = 0; i < len; ++i)
	{
		Vec2 vPos;
		Vec2 vScale;

		fread(&vPos, sizeof(Vec2), 1, pFile);
		fread(&vScale, sizeof(Vec2), 1, pFile);

		qDummy_blue* pMonster = new qDummy_blue;
		pMonster->SetPos(vPos.x, vPos.y);
		pMonster->SetScale(vScale.x, vScale.y);
		pMonster->SetDir(DIRECTION::LEFT);
		AddObject(LAYER_TYPE::DUMMY_BLUE, pMonster);
	}

	fclose(pFile);
}

void qLevel::LoadMonster_red(const wstring& _strRelativePath)
{
	wstring strFullPath = qPathMgr::GetInst()->GetContentPath();

	if (L"Stage1" == GetName())
	{
		strFullPath += L"edit\\stage1\\";
	}
	else if (L"Stage2" == GetName())
	{
		strFullPath += L"edit\\stage2\\";
	}
	else if (L"Boss1" == GetName())
	{
		strFullPath += L"edit\\boss1\\";
	}
	else if (L"Boss2" == GetName())
	{
		strFullPath += L"edit\\boss2\\";
	}


	strFullPath += _strRelativePath;

	FILE* pFile = nullptr;

	_wfopen_s(&pFile, strFullPath.c_str(), L"rb");

	size_t len = 0;

	fread(&len, sizeof(size_t), 1, pFile);

	for (size_t i = 0; i < len; ++i)
	{
		Vec2 vPos;
		Vec2 vScale;

		fread(&vPos, sizeof(Vec2), 1, pFile);
		fread(&vScale, sizeof(Vec2), 1, pFile);

		qDummy_red* pMonster = new qDummy_red;
		AddObject(LAYER_TYPE::DUMMY_RED, pMonster);
	}

	fclose(pFile);
}



