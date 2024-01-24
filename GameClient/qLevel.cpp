#include "pch.h"
#include "qLevel.h"

#include "qObj.h"

qLevel::qLevel()
{

}

qLevel::~qLevel()
{

}


void qLevel::begin()
{
	for (size_t i = 0; i < m_vecObj.size(); ++i)
	{
		m_vecObj[i]->begin();
	}
}

void qLevel::tick()
{
	for (size_t i = 0; i < m_vecObj.size(); ++i)
	{
		m_vecObj[i]->tick();
	}
}

void qLevel::finaltick()
{
	for (size_t i = 0; i < m_vecObj.size(); ++i)
	{
		m_vecObj[i]->finaltick();
	}
}

void qLevel::render()
{
	for (size_t i = 0; i < m_vecObj.size(); ++i)
	{
		m_vecObj[i]->render();
	}
}

