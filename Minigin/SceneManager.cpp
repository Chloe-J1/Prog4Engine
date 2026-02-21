#include "SceneManager.h"
#include "Scene.h"

void dae::SceneManager::Update(float elapsedSec)
{
	for(auto& scene : m_scenes)
	{
		scene->Update(elapsedSec);
	}
}

void dae::SceneManager::FixedUpdate()
{
	for (auto& scene : m_scenes)
	{
		scene->FixedUpdate();
	}
}

void dae::SceneManager::LateUpdate(float elapsedSec)
{
	for (auto& scene : m_scenes)
	{
		scene->LateUpdate(elapsedSec);
	}
}

void dae::SceneManager::Cleanup()
{
	for (auto& scene : m_scenes)
	{
		scene->Cleanup();
	}
}

void dae::SceneManager::Render()
{
	for (const auto& scene : m_scenes)
	{
		scene->Render();
	}
}

dae::Scene& dae::SceneManager::CreateScene()
{
	m_scenes.emplace_back(new Scene());
	return *m_scenes.back();
}
