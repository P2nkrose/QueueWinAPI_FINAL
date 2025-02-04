#pragma once

struct Vec2
{
public:
	float x;
	float y;


public:

	bool IsZero()
	{
		return x == 0.f && y == 0.f;
	}

	// 빗변 구하는 공식
	float GetDistance(Vec2 _Other)
	{
		return sqrtf(powf(x - _Other.x, 2) + powf(y - _Other.y, 2));
	}

	// Length (빗변)
	float Length()
	{
		return sqrtf(x * x + y * y);
	}

	// 정규화
	void Normalize()
	{
		// 0, 0 벡터에 정규화를 하면 문제
		assert(!(x == 0.f && y == 0.f));

		float fLen = Length();
		x /= fLen;
		y /= fLen;
	}


public:
	Vec2 operator +(float f) { return Vec2(x + f, y + f); }
	Vec2 operator -(float f) { return Vec2(x - f, y - f); }
	Vec2 operator *(float f) { return Vec2(x * f, y * f); }
	Vec2 operator /(float f) { assert(f); return Vec2(x / f, y / f); }

	Vec2 operator + (Vec2 _Other) { return Vec2(x + _Other.x, y + _Other.y); }
	Vec2 operator - (Vec2 _Other) { return Vec2(x - _Other.x, y - _Other.y); }
	Vec2 operator * (Vec2 _Other) { return Vec2(x * _Other.x, y * _Other.y); }
	Vec2 operator / (Vec2 _Other) { assert(!(0.f == _Other.x || 0.f == _Other.y));  return Vec2(x / _Other.x, y / _Other.y); }


	void operator +=(float _f)
	{
		x += _f;
		y += _f;
	}

	void operator +=(Vec2 _Other)
	{
		x += _Other.x;
		y += _Other.y;
	}

	void operator -=(float _f)
	{
		x -= _f;
		y -= _f;
	}

	void operator -=(Vec2 _Other)
	{
		x -= _Other.x;
		y -= _Other.y;
	}

	void operator *=(float _f)
	{
		x *= _f;
		y *= _f;
	}

	void operator *=(Vec2 _Other)
	{
		x *= _Other.x;
		y *= _Other.y;
	}

	void operator /=(float _f)
	{
		assert(_f);

		x /= _f;
		y /= _f;
	}

	void operator /=(Vec2 _Other)
	{
		assert(_Other.x && _Other.y);

		x /= _Other.x;
		y /= _Other.y;
	}




public:
	Vec2()
		: x(0.f)
		, y(0.f)
	{

	}

	Vec2(float _x, float _y)
		: x(_x)
		, y(_y)
	{

	}

	Vec2(int _x, int _y)
		: x(float(_x))
		, y(float(_y))
	{

	}

	Vec2(POINT _pt)
		: x((float)_pt.x)
		, y((float)_pt.y)
	{

	}

	~Vec2()
	{

	}
};


struct tDbgRenderInfo
{
	DBG_SHAPE	Shape;
	Vec2		Position;
	Vec2		Scale;
	PEN_TYPE	Color;

	float		Duration;
	float		Age;
};


struct tDbgLog
{
	LOG_TYPE	Type;		// 로그의 종류
	wstring		strLog;		// 로그 메세지
	float		Age;		// 로그가 출력된 시간
};



struct tTask
{
	TASK_TYPE	Type;
	DWORD_PTR	Param1;		// 레벨종류
	DWORD_PTR	Param2;		// 레이어 타입
	DWORD_PTR	Param3;		// 스폰할 오브젝트

};


struct tInfo
{
	Vec2		StartPos;
	Vec2		EndPos;
};

