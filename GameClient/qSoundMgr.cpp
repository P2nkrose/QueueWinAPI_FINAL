#include "pch.h"
#include "qSoundMgr.h"

#include "qEngine.h"
#include "qSound.h"


qSoundMgr::qSoundMgr()
	: m_pSound(nullptr)
{}


qSoundMgr::~qSoundMgr()
{
	// DirectSound8 객체 메모리 해제
	m_pSound->Release();
}


int qSoundMgr::init()
{
	if (FAILED(DirectSoundCreate8(NULL, &m_pSound, NULL)))
	{
		MessageBox(NULL, L"사운드 디바이스 생성 실패", L"SYSTEM ERROR", MB_OK);
		return false;
	}

	// 사운드 협조레벨 설정
	HWND hWnd = qEngine::GetInst()->GetMainWnd();
	if (FAILED(m_pSound->SetCooperativeLevel(hWnd, DISCL_EXCLUSIVE)))
	{
		MessageBox(NULL, L"사운드 매니저 초기화 실패", L"SYSTEM ERROR", MB_OK);
		return false;
	}

	return true;
}

void qSoundMgr::RegisterToBGM(qSound* _pSound)
{
	if (m_pBGM != nullptr)
		m_pBGM->Stop(true);

	m_pBGM = _pSound;
}
