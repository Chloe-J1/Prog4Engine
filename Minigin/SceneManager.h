#pragma once
#include <memory>
#include "Scene.h"
#include "Singleton.h"

namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene& CreateScene();
		Scene& GetActiveScene();

		void Update(float elapsedSec);
		void FixedUpdate();
		void LateUpdate(float elapsedSec);
		void Cleanup();
		void Render();
		void RenderUI();
	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::unique_ptr<Scene> m_activeScene{ nullptr };
	};
}
