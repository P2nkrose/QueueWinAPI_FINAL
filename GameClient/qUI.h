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
	virtual void LButtonDown();			// UI �� ���콺 ���ʹ�ư ���� ���
	virtual void LButtonUp();			// UI �� ���콺 ���ʹ�ư �� ���
	virtual void LButtonClicked();		// UI �� ���콺 ���� ��ư�� ������, �� ���


private:
	virtual void CheckMouseOn();

private:
	bool		m_MouseOn;
	bool		m_MouseOnPrev;

	bool		m_MouseLbtnDown;
};

