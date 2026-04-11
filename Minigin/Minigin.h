#pragma once
#include <string>
#include <functional>
#include <filesystem>
#include <string>

namespace dae
{
	class Minigin final
	{
		bool m_quit{};
		float m_lag{ 0.f };
		const int m_wWidth{ 1024 };
		const int m_wHeight{ 576 };

		std::chrono::high_resolution_clock::time_point m_lastTime{};
	public:
		explicit Minigin(const std::filesystem::path& dataPath, int windowWidth, int windowHeight, const std::string& title);
		~Minigin();
		void Run(const std::function<void()>& load);
		void RunOneFrame();

		Minigin(const Minigin& other) = delete;
		Minigin(Minigin&& other) = delete;
		Minigin& operator=(const Minigin& other) = delete;
		Minigin& operator=(Minigin&& other) = delete;
	};
}