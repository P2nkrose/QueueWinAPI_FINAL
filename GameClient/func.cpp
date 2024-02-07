#include "pch.h"
#include "func.h"
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


#include "qTaskMgr.h"
void SpawnObject(qLevel* _Level, LAYER_TYPE _type, qObj* _pSpawned)
{
	tTask task = {};
	task.Type = TASK_TYPE::SPAWN_OBJECT;
	task.lParam = (DWORD_PTR)_Level;
	task.rParam = (DWORD_PTR)_pSpawned;
	task.wParam = (DWORD_PTR)_type;

	qTaskMgr::GetInst()->AddTask(task);
}