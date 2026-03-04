#pragma once
#include "Component.h"
#include <vector>
#include <memory>
struct transform
{
	float matrix[16] = {
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1
	};
};

class gameobject
{
public:
	transform local;
	int id;
};
class gameobjectAlt
{
public:
	transform* local;
	int id;
};

namespace dae
{
	class GraphComponent : public Component
	{
	public:
		GraphComponent(GameObject* owner);

		virtual void RenderUI() override;

	private:
		void ShowExOneWindow(bool* p_open);
		void ShowExTwoWindow(bool* p_open);

		bool m_isTrashCachePressed{ false };
		bool m_isTrashCacheGoPressed{ false };
		bool m_isTrashCacheGoAltPressed{ false };
		std::vector<float> m_timesFirstEx;
		std::vector<float> m_timesGO;
		std::vector<float> m_timesGOAlt;
		const int m_samplesStep{ 10000 };
		std::vector<float> m_vectFirstEx;
		std::vector<gameobject> m_vectGO;
		std::vector<std::unique_ptr<gameobject>> m_vectGOAlt;
	};
}
