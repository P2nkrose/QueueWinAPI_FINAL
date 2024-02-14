#pragma once
#include "qEntity.h"

struct tAnimFrm
{
    Vec2    StartPos;
    Vec2    SliceSize;
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

    void Reset()
    {
        m_Time = 0.f;
        m_CurFrmIdx = 0;
        m_bFinish = false;
    }



private:
    qAnimator*          m_Animator;     // Animation �� �����ϰ� �ִ� Animator
    qTexture*           m_Atlas;        // Animation �̹����� �����ϰ� �ִ� Atlas Texture
    vector<tAnimFrm>    m_vecFrm;       // �� ������ ����

    float               m_Time;         // �����ð� üũ
    int                 m_CurFrmIdx;    // ���� ������
    bool                m_bFinish;      // �ִϸ��̼� ����� ������� �˸�

};

