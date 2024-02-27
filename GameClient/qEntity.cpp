#include "pch.h"
#include "qEntity.h"

// ±¸Çö
UINT qEntity::g_NextID = 0;

qEntity::qEntity()
	: m_ID(g_NextID++)
{
}

qEntity::qEntity(const qEntity& _Other)
	: m_ID(g_NextID++)
	, m_strName(_Other.m_strName)
{
}

qEntity::~qEntity()
{
}
