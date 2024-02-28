#include "pch.h"
#include "qComponent.h"

qComponent::qComponent()
	: m_Owner(nullptr)
{
}

qComponent::qComponent(const qComponent& _Other)
	: m_Owner(nullptr)
{
}

qComponent::~qComponent()
{
}
