#pragma once
#include "qEntity.h"

#include "qEngine.h"
#include "qTimeMgr.h"
#include "qKeyMgr.h"

class qComponent;
class qCollider;
class qAnimator;
class qFSM;


class qObj : public qEntity
{
private:
	
	Vec2				m_Pos;		// ��ġ
	Vec2				m_Scale;	// ũ��
	vector<qComponent*>	m_vecCom;	// ���� ������Ʈ��
	

public:
	void SetPos(Vec2 _Pos) { m_Pos = _Pos; }
	void SetScale(Vec2 _Scale) { m_Scale = _Scale; }

	void SetPos(float _x, float _y) { m_Pos.x = _x; m_Pos.y = _y; }
	void SetScale(float _width, float _height) { m_Scale.x = _width; m_Scale.y = _height; }

	Vec2 GetPos() { return m_Pos; }
	Vec2 GetScale() { return m_Scale; }

	qComponent* AddComponent(qComponent* _Component);

	template<typename T>
	T* GetComponent()
	{
		for (size_t i = 0; i < m_vecCom.size(); ++i)
		{
			T* pComponent = dynamic_cast<T*>(m_vecCom[i]);

			if (pComponent)
			{
				return pComponent;
			}
		}

		return nullptr;
	}

public:
	virtual void begin();		
	virtual void tick();		// ������Ʈ�� �� �����Ӹ��� �ؾ��� �۾��� ����
	virtual void finaltick();	// ������Ʈ�� ������ ������Ʈ���� �� �����Ӹ��� �ؾ��� �۾��� ����
	virtual void render();

public:
	virtual qObj* Clone() = 0;	// { return new qObj(*this); }


public:
	qObj();
	~qObj();
};

