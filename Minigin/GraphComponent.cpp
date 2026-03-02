#include "GraphComponent.h"
#include "imgui.h"
#include <cmath>
#include <cstdio>

dae::GraphComponent::GraphComponent(GameObject* owner):
	Component::Component(owner)
{
}

struct WindowData
{
	bool ShowMainMenuBar = false;
};

void dae::GraphComponent::ShowWindow(bool* p_open) const
{
	/*static WindowData wd;

    if (!ImGui::Begin("Graph one", p_open))
    {
        ImGui::End();
        return;
    }

    if (wd.ShowMainMenuBar)
        ImGui::ShowDebugLogWindow(&wd.ShowMainMenuBar);
    

    
    ImGui::End();*/

    if (!ImGui::Begin("Graph", p_open))
    {
        ImGui::End();
        return;
    }

    static float arr[] = { 0.6f, 0.1f, 1.0f, 0.5f, 0.92f, 0.1f, 0.2f };
    ImGui::PlotLines("Frame Times", arr, IM_ARRAYSIZE(arr)); 

    ImGui::PlotHistogram("Histogram", arr, IM_ARRAYSIZE(arr), 0, NULL, 0.0f, 1.0f, ImVec2(0, 80.0f));

    static float values[90] = {};
    static int values_offset = 0;
    static double refresh_time = 0.0;

    if (refresh_time == 0.0)
        refresh_time = ImGui::GetTime();

    while (refresh_time < ImGui::GetTime())
    {
        static float phase = 0.0f;
        values[values_offset] = sinf(phase);
        values_offset = (values_offset + 1) % IM_ARRAYSIZE(values);
        phase += 0.10f;
        refresh_time += 1.0f / 60.0f;
    }

    float average = 0.0f;
    for (int n = 0; n < IM_ARRAYSIZE(values); n++)
        average += values[n];
    average /= (float)IM_ARRAYSIZE(values);

    char overlay[32];
    sprintf_s(overlay, "avg %.3f", average);
    ImGui::PlotLines("Live Values", values, IM_ARRAYSIZE(values), values_offset, overlay, -1.0f, 1.0f, ImVec2(0, 80.0f));

    ImGui::End();
}


void dae::GraphComponent::RenderUI() const
{
	static bool open = true;
	ShowWindow(&open);
}