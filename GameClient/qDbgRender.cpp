#include "pch.h"
#include "qDbgRender.h"

#include "qEngine.h"
#include "qTimeMgr.h"
#include "qKeyMgr.h"

qDbgRender::qDbgRender()
	: m_bRender(true)
	, m_LogLife(2.f)
	, m_LogSpace(18)
	, m_LogStartPos(Vec2(10.f, 10.f))
{
	
}

qDbgRender::~qDbgRender()
{

}

void qDbgRender::tick()
{
	if (KEY_TAP(KEY::_0))
	{
		m_bRender ? m_bRender = false : m_bRender = true;
	}
}

void qDbgRender::render()
{
	list<tDbgRenderInfo>::iterator iter = m_RenderList.begin();

	for (; iter != m_RenderList.end();)
	{
		USE_BRUSH(DC, BRUSH_TYPE::BRUSH_HOLLOW);
		qSelectObj SelectPen(DC, qEngine::GetInst()->GetPen(iter->Color));

		// DBG 가 Rect 면 사각형을 그린다.
		if (m_bRender && DBG_SHAPE::RECT == iter->Shape)
		{
			Rectangle(DC,
				  (int)(iter->Position.x - iter->Scale.x / 2.f)
				, (int)(iter->Position.y - iter->Scale.y / 2.f)
				, (int)(iter->Position.x + iter->Scale.x / 2.f)
				, (int)(iter->Position.y + iter->Scale.y / 2.f));
		}

		// DBG 가 Circle 면 원을 그린다.
		else if(m_bRender && DBG_SHAPE::CIRCLE == iter->Shape)
		{
			Ellipse(DC,
				  (int)(iter->Position.x - iter->Scale.x / 2.f)
				, (int)(iter->Position.y - iter->Scale.y / 2.f)
				, (int)(iter->Position.x + iter->Scale.x / 2.f)
				, (int)(iter->Position.y + iter->Scale.y / 2.f));
		}
		// DBG 가 Line 이면 선을 그린다.
		else if (m_bRender && DBG_SHAPE::LINE == iter->Shape)
		{
			// MoveToEx 현재 위치를 지정된 시점으로 옮긴다.
			MoveToEx(DC, (int)iter->Position.x, (int)iter->Position.y, nullptr);

			// 현재 위치에서 지정된 시점까지 선을 그린다.
			LineTo(DC, (int)iter->Scale.x, (int)iter->Scale.y);
		}

		// 해당 디버그렌더 정보가 수명을 다하면 리스트에서 제거한다.
		(*iter).Age += DT;
		if (iter->Duration < iter->Age)
		{
			iter = m_RenderList.erase(iter);
		}
		else
		{
			++iter;
		}
	}


	// 로그 정보 출력
	list<tDbgLog>::iterator logiter = m_LogList.begin();

	SetBkMode(DC, TRANSPARENT);

	int i = 0;
	for (; logiter != m_LogList.end();)
	{
		if (m_bRender)
		{
			// 오래된 로그일수록 아래쪽에 출력이 되어야 함
			// 로그의 y 축 offset 위치를 구함
			int yoffset = ((int)m_LogList.size() - (i + 1)) * m_LogSpace;

			switch (logiter->Type)
			{
			case LOG_TYPE::DBG_LOG:
				SetTextColor(DC, RGB(255, 255, 255));
				break;
			case LOG_TYPE::DBG_WARNING:
				SetTextColor(DC, RGB(240, 240, 20));
				break;
			case LOG_TYPE::DBG_ERROR:
				SetTextColor(DC, RGB(240, 20, 20));
				break;
			}

			TextOut(DC
					, (int)m_LogStartPos.x
					, (int)m_LogStartPos.y + yoffset
					, logiter->strLog.c_str()
					, (int)logiter->strLog.length());
		}

		// 로그 나이 계산
		logiter->Age += DT;

		// 수명이 넘은 로그는 삭제
		if (m_LogLife <= logiter->Age)
		{
			logiter = m_LogList.erase(logiter);
		}
		else
		{
			++logiter;
		}

		++i;
	}

	SetBkMode(DC, OPAQUE);
	SetTextColor(DC, RGB(0, 0, 0));

}
