#pragma once
#include "Component.h"
#include <vector>
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

		bool m_isFirstValuesCalc{ false };
		bool m_isGOValuesCalc{ false };
		bool m_isGOAltValuesCalc{ false };
		bool m_isTrashCachePressed{ false };
		bool m_isTrashCacheGoPressed{ false };
		bool m_isTrashCacheGoAltPressed{ false };
		std::vector<float> m_timesFirstEx;
		std::vector<float> m_timesGO;
		std::vector<float> m_timesGOAlt;
		const int m_samplesStep{ 10000 };
	};
}
