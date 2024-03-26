#pragma once
#include "qAsset.h"


class qSound : public qAsset
{
public:
	friend class qAssetMgr;

	CLONE_DISABLE(qSound);

public:
	qSound();
	~qSound();

public:
	virtual int Load(const wstring& _strFilePath);

public:
    // ���� ���
    void Play(bool _bLoop = false);

    // ����������� ���
    void PlayToBGM(bool _bLoop = false);

    // ����
    void Stop(bool _bReset = false);

    // ���� ���� (0 ~ 100)
    void SetVolume(float _fVolume);

    // ���� ��� ��ġ (0 ~ 100)
    void SetPosition(float _fPosition); // 0 ~ 100 


    int GetDecibel(float _fVolume);



private:
    bool LoadWaveSound(const wstring& _strPath);


private:
    LPDIRECTSOUNDBUFFER		m_pSoundBuffer;
    DSBUFFERDESC			m_tBuffInfo;
    int						m_iVolume;
};

