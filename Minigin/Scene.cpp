#include "Scene.h"
#include <algorithm>

using namespace dae;

void Scene::Add(std::unique_ptr<GameObject> object)
{
	assert(object != nullptr && "Cannot add a null GameObject to the scene.");
	m_newObjects.emplace_back(std::move(object));
}

void dae::Scene::Remove(const GameObject& object)
{
	for (auto& obj : m_objects)
	{
		if (obj.get() == &object)
		{
			obj->SetIsAlive(false);
			return;
		}
	}
}

void Scene::RemoveAll()
{
	m_objects.clear();
	m_newObjects.clear();
}

void dae::Scene::MoveNewObjects()
{
	for (auto& obj : m_newObjects)
		m_objects.emplace_back(std::move(obj));
	m_newObjects.clear();
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

void dae::Scene::RenderUI()
{
	for (const auto& object : m_objects)
	{
		object->RenderUI();
	}
}

