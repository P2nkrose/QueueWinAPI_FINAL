#pragma once
#include "qObj.h"
class qMissile : public qObj
{
public:
	qMissile();
	~qMissile();


public:
	virtual void tick() override;
	virtual void render() override;

protected:
	void SetSpeed(float _Speed) { m_Speed = _Speed; }
	void SetAngle(float _Angle) { m_Angle = _Angle; }

	float GetSpeed() { return m_Speed; }
	float GetAngle() { return m_Angle; }

	qCollider* GetCollider() { return m_Collider; }


private:
	virtual qMissile* Clone() { return new qMissile(*this); }


private:
	float		m_Speed;
	float		m_Angle;	// ¶óµð¾È

	qCollider*	m_Collider;

};

