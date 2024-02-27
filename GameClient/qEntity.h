#pragma once

// 정적 변수
// 1. 함수 내
// 2. 파일
// 3. 클래스

class qEntity
{

private:
	// 정적 멤버 선언
	static UINT g_NextID;	// 특정 클래스 내에 멤버로 정적변수를 선언


private:
	UINT		m_ID;		// 객체별 고유 ID
	wstring		m_strName;


public:
	UINT GetID() { return m_ID; }

	void SetName(const wstring& _Name) { m_strName = _Name; }
	const wstring& GetName() { return m_strName; }

public:
	// qEntity 클래스는 추상클래스이다.
	virtual qEntity* Clone() = 0;

public:
	qEntity();
	qEntity(const qEntity& _Other);
	virtual ~qEntity();
};

