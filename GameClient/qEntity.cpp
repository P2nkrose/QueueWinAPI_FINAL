#include "pch.h"
#include "qEntity.h"

// ±¸Çö
UINT qEntity::g_NextID = 0;

qEntity::qEntity()
	: m_ID(g_NextID++)
{
}

qEntity::~qEntity()
{
}
