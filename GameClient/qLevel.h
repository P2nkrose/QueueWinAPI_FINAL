#pragma once
#include "qEntity.h"

class qObj;

class qLevel : public qEntity
{
private:

	vector<qObj*>		m_vecObj;

public:

	// ���� �Լ�
	virtual void begin();		// ������ ���۵� ��
	virtual void tick();		// �� �����Ӹ��� ȣ��
	virtual void finaltick();	// �� �����Ӹ��� ȣ��
	virtual void render();		// �� �����Ӹ��� ȣ��


public:
	void AddObject(qObj* _Obj) { m_vecObj.push_back(_Obj); }


public:
	qLevel();
	~qLevel();
};

