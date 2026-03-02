#pragma once
#include "Component.h"
namespace dae
{
	class GraphComponent : public Component
	{
	public:
		GraphComponent(GameObject* owner);

		virtual void RenderUI() const override;

	private:
		void ShowWindow(bool* p_open) const;
	};
}
