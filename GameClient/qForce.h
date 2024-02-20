#pragma once
#include "qObj.h"


class qForce : public qObj
{

	CLONE(qForce);

public: 
	qForce();
	~qForce();

	virtual void tick() override;

public:
	void SetForce(float _Force, float _Range, float _Time)
	{
		m_Force = _Force;
		m_Range = _Range;
		m_Time = _Time;
	}

private:
	void AddForce(LAYER_TYPE _type);


private:
	float	m_Force;	// ���� ũ��
	float	m_Range;	// ���� ����
	float	m_Time;		// ���� �����Ǵ� �ð�

	float	m_Age;

};

