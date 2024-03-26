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
	LPDIRECTSOUND8	m_pSound;	// 사운드 카드 제어
	qSound* m_pBGM;		// BGM Sound

};

