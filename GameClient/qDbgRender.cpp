#include "pch.h"
#include "qDbgRender.h"

#include "qEngine.h"
#include "qTimeMgr.h"
#include "qKeyMgr.h"

qDbgRender::qDbgRender()
	: m_bRender(true)
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
		USE_BRUSH(DC, BRUSH_HOLLOW);
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

		// DBG 가 Circle 면 사각형을 그린다.
		else if(m_bRender && DBG_SHAPE::CIRCLE == iter->Shape)
		{
			Ellipse(DC,
				  (int)(iter->Position.x - iter->Scale.x / 2.f)
				, (int)(iter->Position.y - iter->Scale.y / 2.f)
				, (int)(iter->Position.x + iter->Scale.x / 2.f)
				, (int)(iter->Position.y + iter->Scale.y / 2.f));
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
}
