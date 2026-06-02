#pragma once
#include <memory>
#include <vector>
#include "GameObject.h"

namespace dae
{
	class Scene final
	{
	public:
		void Add(std::unique_ptr<GameObject> object);
		void Remove(const GameObject& object);
		void RemoveAll();
		void MoveNewObjects();

		void Update(float elapsedSec);
		void FixedUpdate();
		void LateUpdate(float elapsedSec);
		void Cleanup();
		void Render() const;
		void RenderUI();

		template<typename T>
		std::vector<GameObject*> FindObjectsWithComponent()
		{
			std::vector<GameObject*> foundObjects{};
			for (const auto& go : m_objects)
			{
				if (go.get()->GetComponent<T>())
					foundObjects.push_back(go.get());
			}
			return foundObjects;
		}

		~Scene()= default;
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	private:
		friend class SceneManager;
		explicit Scene() = default;

		std::vector <std::unique_ptr<GameObject>> m_objects{};
		std::vector <std::unique_ptr<GameObject>> m_newObjects{};
	};

}
