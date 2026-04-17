#include "SceneManager.h"
#include "Scene.h"
#include <iostream>

void dae::SceneManager::Update(float elapsedSec)
{

	m_activeScene->Update(elapsedSec);

}

void dae::SceneManager::FixedUpdate()
{

	m_activeScene->FixedUpdate();

}

void dae::SceneManager::LateUpdate(float elapsedSec)
{
	m_activeScene->LateUpdate(elapsedSec);
}

void dae::SceneManager::Cleanup()
{
	m_activeScene->Cleanup();

}

void dae::SceneManager::Render()
{
	m_activeScene->Render();
}

void dae::SceneManager::RenderUI()
{
	m_activeScene->RenderUI();
}

#include "InputManager.h"
dae::Scene& dae::SceneManager::CreateScene(const std::string& name)
{
	InputManager::GetInstance().UnbindAllCommands(); // TODO: event

	m_scenes[name] = std::unique_ptr<Scene>(new Scene());
	m_activeScene = m_scenes[name].get();

	return *m_scenes[name];

}

dae::Scene& dae::SceneManager::LoadScene(const std::string& name)
{
	auto itr = m_scenes.find(name);

	if (itr != m_scenes.end())
	{
		m_activeScene = itr->second.get();
	}
	else
	{
		std::cerr << "Scene not created yet\n";
	}
	return *m_activeScene;
}

dae::Scene& dae::SceneManager::GetActiveScene()
{
	return *m_activeScene;
}
