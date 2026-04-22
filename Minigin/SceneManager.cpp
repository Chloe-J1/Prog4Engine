#include "SceneManager.h"
#include "Scene.h"
#include "InputManager.h"

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

dae::Scene& dae::SceneManager::CreateScene()
{
	InputManager::GetInstance().UnbindAllCommands();

	m_activeScene = std::unique_ptr<Scene>(new Scene());
	return *m_activeScene;

}

dae::Scene& dae::SceneManager::GetActiveScene()
{
	return *m_activeScene;
}
