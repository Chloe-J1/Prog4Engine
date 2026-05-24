#pragma once
#include <string>
#include <functional>
#include <filesystem>
#include <string>
#include "InputManager.h"
#include "SceneManager.h"
#include "CollisionManager.h"
#include "EventQueue.h"
#include "Renderer.h"

namespace dae
{
	class Minigin final
	{
		bool m_quit{};
		float m_lag{ 0.f };

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

		SceneManager& m_sceneManager{ dae::SceneManager::GetInstance() };
		CollisionManager& m_collisionManager{ dae::CollisionManager::GetInstance() };
		EventQueue& m_eventQueue{ dae::EventQueue::GetInstance() };
		Renderer& m_renderer{ dae::Renderer::GetInstance() };
	};
}