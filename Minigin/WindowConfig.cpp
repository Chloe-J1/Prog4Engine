#include "WindowConfig.h"

int dae::WindowConfig::GetWidth() const
{
	return m_width;
}

int dae::WindowConfig::GetHeight() const
{
	return m_height;
}

const std::string& dae::WindowConfig::GetTitle() const
{
	return m_title;
}

void dae::WindowConfig::Init(int width, int height, const std::string& title)
{
	m_width = width;
	m_height = height;
	m_title = title;
}
