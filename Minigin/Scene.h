#pragma once
#include <memory>
#include <string>
#include <vector>
#include "GameObject.h"

namespace dae
{
	class Scene final
	{
	public:
		void Add(std::unique_ptr<GameObject> object);
		template<typename T>
		void Remove()
		{
			for (auto&& object : m_objects)
			{
				if (T* removeObject = dynamic_cast<T*>(object.get()))
				{
					object->SetIsAlive(false);
				}
			}
		}
		void RemoveAll();

		void Update(float elapsedSec);
		void FixedUpdate();
		void LateUpdate(float elapsedSec);
		void Cleanup();
		void Render() const;

		~Scene() = default;
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	private:
		friend class SceneManager;
		explicit Scene() = default;

		std::vector < std::unique_ptr<GameObject>> m_objects{};
	};

}
