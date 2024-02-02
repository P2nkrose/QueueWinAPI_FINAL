#include "pch.h"
#include "qPathMgr.h"

#include "resource.h"
#include "qEngine.h"

qPathMgr::qPathMgr()
{
}

qPathMgr::~qPathMgr()
{
}

void qPathMgr::init()
{
	// 실행경로를 얻어낸다
	wchar_t szBuffer[256] = {};
	GetCurrentDirectory(256, szBuffer);

	// bin 폴더의 상위폴더로 접근한다.
	GetParentPath(szBuffer);

	// \\Content\\ 를 붙여둔다
	m_Content = szBuffer;
	m_Content += L"\\content\\";

	// OutputFile 폴더의 상위폴더로 접근한다.
	GetParentPath(szBuffer);
	m_Solution = szBuffer;

	// String Table 에서 프로젝트 이름을 얻어온다.
	wchar_t szProjName[50] = {};
	LoadStringW(qEngine::GetInst()->GetProcessInstance(), IDS_APP_TITLE, szProjName, 50);

	// Solution 경로에서 프로젝트 이름을 붙인다.
	m_Proj = m_Solution + L"\\" + szProjName;
}

void qPathMgr::render()
{
	TextOut(DC, 10, 10, m_Solution.c_str(), (int)m_Solution.length());
	TextOut(DC, 10, 30, m_Proj.c_str(), (int)m_Proj.length());
	TextOut(DC, 10, 50, m_Content.c_str(), (int)m_Content.length());
}

void qPathMgr::GetParentPath(_Inout_ wchar_t* _Buffer)
{
	size_t len = wcslen(_Buffer);

	for (int i = len - 1; 0 < i; --i)
	{
		if (L'\\' == _Buffer[i])
		{
			_Buffer[i] = L'\0';
			break;
		}
	}
}
