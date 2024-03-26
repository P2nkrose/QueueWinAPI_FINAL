#pragma once

class qSound;

class qSoundMgr
{
	SINGLE(qSoundMgr);

public:
	int init();
	LPDIRECTSOUND8 GetSoundDevice() { return m_pSound; }
	void RegisterToBGM(qSound* _pSound);


private:
	LPDIRECTSOUND8	m_pSound;	// ���� ī�� ����
	qSound* m_pBGM;		// BGM Sound

};

