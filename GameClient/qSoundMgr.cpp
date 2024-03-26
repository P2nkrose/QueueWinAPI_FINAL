#include "pch.h"
#include "qSoundMgr.h"

#include "qEngine.h"
#include "qSound.h"


qSoundMgr::qSoundMgr()
	: m_pSound(nullptr)
{}


qSoundMgr::~qSoundMgr()
{
	// DirectSound8 ��ü �޸� ����
	m_pSound->Release();
}


int qSoundMgr::init()
{
	if (FAILED(DirectSoundCreate8(NULL, &m_pSound, NULL)))
	{
		MessageBox(NULL, L"���� ����̽� ���� ����", L"SYSTEM ERROR", MB_OK);
		return false;
	}

	// ���� �������� ����
	HWND hWnd = qEngine::GetInst()->GetMainWnd();
	if (FAILED(m_pSound->SetCooperativeLevel(hWnd, DISCL_EXCLUSIVE)))
	{
		MessageBox(NULL, L"���� �Ŵ��� �ʱ�ȭ ����", L"SYSTEM ERROR", MB_OK);
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
