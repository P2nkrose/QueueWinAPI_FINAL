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
	Vec2 GetFinalPos() { return m_vFinalPos; }

	bool IsMouseOn() { return m_MouseOn; }
	bool IsLbtnDowned() { return m_MouseLbtnDown; }

	void AddChildUI(qUI* _UI)
	{
		m_vecChildUI.push_back(_UI);
		_UI->m_ParentUI = this;
	}


public:
	virtual void LButtonDown();			// UI �� ���콺 ���ʹ�ư ���� ���
	virtual void LButtonUp();			// UI �� ���콺 ���ʹ�ư �� ���
	virtual void LButtonClicked();		// UI �� ���콺 ���� ��ư�� ������, �� ���


private:
	virtual void CheckMouseOn();

private:

	qUI*			m_ParentUI;
	vector<qUI*>	m_vecChildUI;

	Vec2			m_vFinalPos;

	bool			m_MouseOn;
	bool			m_MouseOnPrev;
	bool			m_MouseLbtnDown;
};

