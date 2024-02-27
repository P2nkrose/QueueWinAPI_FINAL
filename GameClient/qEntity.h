#pragma once

// ���� ����
// 1. �Լ� ��
// 2. ����
// 3. Ŭ����

class qEntity
{

private:
	// ���� ��� ����
	static UINT g_NextID;	// Ư�� Ŭ���� ���� ����� ���������� ����


private:
	UINT		m_ID;		// ��ü�� ���� ID
	wstring		m_strName;


public:
	UINT GetID() { return m_ID; }

	void SetName(const wstring& _Name) { m_strName = _Name; }
	const wstring& GetName() { return m_strName; }

public:
	// qEntity Ŭ������ �߻�Ŭ�����̴�.
	virtual qEntity* Clone() = 0;

public:
	qEntity();
	qEntity(const qEntity& _Other);
	virtual ~qEntity();
};

