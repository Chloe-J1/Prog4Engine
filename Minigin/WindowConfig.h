#pragma once
#include "Singleton.h"
#include <string>
namespace dae
{
	class WindowConfig : public Singleton<WindowConfig>
	{
	public:

		int GetWidth() const
		{
			return m_width;
		}

		int GetHeight() const
		{
			return m_height;
		}

		const std::string& GetTitle() const
		{
			return m_title;
		}

		void Init(int width, int height, const std::string& title)
		{
			m_width = width;
			m_height = height;
			m_title = title;
		}
	private:
		int m_width{ 1024 };
		int m_height{ 576 };
		std::string m_title{"title"};
	};
}