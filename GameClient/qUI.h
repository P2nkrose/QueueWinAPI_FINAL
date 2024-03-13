#pragma once
#include "qObj.h"



class qUI : public qObj
{
public:
	friend class qTaskMgr;

	CLONE(qUI);

public:
	qUI();
	~qUI();

public:
	virtual void tick() override;
	virtual void render() override;

public:
	bool IsMouseOn() { return m_MouseOn; }
	bool IsLbtnDowned() { return m_MouseLbtnDown; }

public:
	virtual void LButtonDown();			// UI 에 마우스 왼쪽버튼 누른 경우
	virtual void LButtonUp();			// UI 에 마우스 왼쪽버튼 뗀 경우
	virtual void LButtonClicked();		// UI 에 마우스 왼쪽 버튼을 누르고, 뗀 경우


private:
	virtual void CheckMouseOn();

private:
	bool		m_MouseOn;
	bool		m_MouseOnPrev;

	bool		m_MouseLbtnDown;
};

