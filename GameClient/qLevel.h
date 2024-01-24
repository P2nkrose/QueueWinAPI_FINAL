#pragma once
#include "qEntity.h"

class qObj;

class qLevel : public qEntity
{
private:

	vector<qObj*>		m_vecObj;

public:

	// ���� �Լ�
	void begin();		// ������ ���۵� ��

	void tick();		// �� �����Ӹ��� ȣ��
	void finaltick();	// �� �����Ӹ��� ȣ��
	void render();		// �� �����Ӹ��� ȣ��


public:
	void AddObject(qObj* _Obj) { m_vecObj.push_back(_Obj); }


public:
	qLevel();
	~qLevel();
};

