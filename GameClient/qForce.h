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
	float	m_Force;	// 힘의 크기
	float	m_Range;	// 힘의 범위
	float	m_Time;		// 힘이 유지되는 시간

	float	m_Age;

};

