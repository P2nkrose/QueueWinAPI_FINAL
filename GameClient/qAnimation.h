#pragma once
#include "qEntity.h"

struct tAnimFrm
{
    Vec2    StartPos;
    Vec2    SliceSize;

    Vec2    Offset;

    float   Duration;
};

class qAnimator;
class qTexture;

class qAnimation : public qEntity
{
    friend class qAnimator;

public:
    CLONE(qAnimation);

public:
    qAnimation();
    ~qAnimation();


    void finaltick();
    void render();
    void Create(qTexture* _AtlasTex, Vec2 _StartPos, Vec2 _SliceSize, int _FrameCount, int _FPS);
    bool IsFinish() { return m_bFinish; }
    void SetAtlasTexture(qTexture* _Atlas) { m_Atlas = _Atlas; }

    void Save(const wstring& _strRelativeFolderPath);
    int Load(const wstring& _strRelativeFilePath);

public:
    void Reset()
    {
        m_Time = 0.f;
        m_CurFrmIdx = 0;
        m_bFinish = false;
    }

    tAnimFrm& GetFrame(int _Idx) { return m_vecFrm[_Idx]; }

    
private:
    qAnimator*          m_Animator;     // Animation 을 소유하고 있는 Animator
    qTexture*           m_Atlas;        // Animation 이미지를 보유하고 있는 Atlas Texture
    vector<tAnimFrm>    m_vecFrm;       // 각 프레임 정보

    float               m_Time;         // 누적시간 체크
    int                 m_CurFrmIdx;    // 현재 프레임
    bool                m_bFinish;      // 애니메이션 재생이 종료됨을 알림

};

