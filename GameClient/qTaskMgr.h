#pragma once


class qTaskMgr
{
	SINGLE(qTaskMgr)

private:

	vector<tTask>	m_vecTask;

public:

	void tick();
	void AddTask(const tTask& _Task) { m_vecTask.push_back(_Task); }

};

