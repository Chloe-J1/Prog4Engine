#pragma once
#include "Singleton.h"
#include <string>
namespace dae
{
	class WindowConfig final : public Singleton<WindowConfig>
	{
	public:

		int GetWidth() const;

		int GetHeight() const;

		const std::string& GetTitle() const;

		void Init(int width, int height, const std::string& title);
	private:
		int m_width{ 1024 };
		int m_height{ 576 };
		std::string m_title{"title"};
	};
}