#pragma once
class qTimeMgr
{
	SINGLE(qTimeMgr)

private:
	LARGE_INTEGER		m_llCurCount;
	LARGE_INTEGER		m_llPrevCount;
	LARGE_INTEGER		m_llFrequency;

	UINT				m_FPS;

	float				m_DeltaTime;		// 프레임 간격 시간
	float				m_Time;				// 프로그램이 켜진 이후로 진행된 시간


public:
	void init();
	void tick();

public:
	float GetDeltaTime() { return m_DeltaTime; }
	float GetTime() { return m_Time; }
	UINT GetFPS() { return m_FPS; }
};

