#include <algorithm>
#include "Scene.h"
#include "RenderComponent.h"

using namespace dae;

void Scene::Add(std::unique_ptr<GameObject> object)
{
	assert(object != nullptr && "Cannot add a null GameObject to the scene.");
	m_objects.emplace_back(std::move(object));
}

void Scene::RemoveAll()
{
	m_objects.clear();
}

void Scene::Update(float elapsedSec)
{
	for(auto& object : m_objects)
	{
		object->Update(elapsedSec);
	}
}

void dae::Scene::FixedUpdate()
{
	for (auto& object : m_objects)
	{
		object->FixedUpdate();
	}
}

void dae::Scene::LateUpdate(float elapsedSec)
{
	for (auto& object : m_objects)
	{
		object->LateUpdate(elapsedSec);
	}
}

void dae::Scene::Cleanup()
{
	for (auto& object : m_objects)
	{
		object->Cleanup();
	}
	// Remove death gameObjects
	m_objects.erase(
		std::remove_if(m_objects.begin(), m_objects.end(),
			[](std::unique_ptr<GameObject>& go) {
				return !go->GetIsAlive();
			}),
		m_objects.end()
	);
}

void Scene::Render() const
{
	for (const auto& object : m_objects)
	{
		object->Render();
	}
}

