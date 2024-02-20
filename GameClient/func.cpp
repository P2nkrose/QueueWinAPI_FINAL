#include "pch.h"

#include "qDbgRender.h"

void DrawDebugRect(PEN_TYPE _Type, Vec2 _Pos, Vec2 _Scale, float _Time)
{
	tDbgRenderInfo info{};
	info.Shape = DBG_SHAPE::RECT;
	info.Color = _Type;
	info.Position = _Pos;
	info.Scale = _Scale;
	info.Duration = _Time;
	info.Age = 0.f;

	qDbgRender::GetInst()->AddDbgRenderInfo(info);
}

void DrawDebugCircle(PEN_TYPE _Type, Vec2 _Pos, Vec2 _Scale, float _Time)
{
	tDbgRenderInfo info{};
	info.Shape = DBG_SHAPE::CIRCLE;
	info.Color = _Type;
	info.Position = _Pos;
	info.Scale = _Scale;
	info.Duration = _Time;
	info.Age = 0.f;

	qDbgRender::GetInst()->AddDbgRenderInfo(info);
}

void DrawDebugLine(PEN_TYPE _Type, Vec2 _Start, Vec2 _End, float _Time)
{
	tDbgRenderInfo info{};
	info.Shape = DBG_SHAPE::LINE;
	info.Color = _Type;
	info.Position = _Start;
	info.Scale = _End;
	info.Duration = _Time;
	info.Age = 0.f;

	qDbgRender::GetInst()->AddDbgRenderInfo(info);
}

void DebugLog(LOG_TYPE _Type, const WCHAR* _LogMgs)
{
	tDbgLog log = {};
	log.Type = _Type;
	log.strLog = _LogMgs;

	qDbgRender::GetInst()->AddDbgLog(log);
}


float Saturate(float _Ratio)
{
	if (_Ratio < 0.f)
		_Ratio = 0.f;

	if (1.f < _Ratio)
		_Ratio = 1.f;

	return _Ratio;
}



#include "qObj.h"
bool IsValid(qObj*& _Object)
{
	if (nullptr == _Object)
	{
		return false;
	}
	else if (_Object->IsDead())
	{
		_Object = nullptr;
		return false;
	}

	return true;
}



void SaveWString(const wstring& _str, FILE* _File)
{
	size_t len = _str.length();
	fwrite(&len, sizeof(size_t), 1, _File);
	fwrite(_str.c_str(), sizeof(wchar_t), len, _File);
}


void LoadWString(wstring& _str, FILE* _File)
{
	wchar_t buff[256] = {};
	size_t len = 0;
	fread(&len, sizeof(size_t), 1, _File);
	fread(buff, sizeof(wchar_t), len, _File);
	_str = buff;
}




#include "qTaskMgr.h"
void SpawnObject(qLevel* _Level, LAYER_TYPE _type, qObj* _pSpawned)
{
	tTask task = {};
	task.Type = TASK_TYPE::SPAWN_OBJECT;
	task.Param1 = (DWORD_PTR)_Level;
	task.Param2 = (DWORD_PTR)_type;
	task.Param3 = (DWORD_PTR)_pSpawned;

	qTaskMgr::GetInst()->AddTask(task);
}