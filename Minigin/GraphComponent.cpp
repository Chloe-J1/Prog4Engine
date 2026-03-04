#include "GraphComponent.h"
#include "imgui.h"

#include <chrono>



dae::GraphComponent::GraphComponent(GameObject* owner):
	Component::Component(owner)
{
}

struct WindowData
{
	bool ShowMainMenuBar = false;
};

void dae::GraphComponent::ShowExOneWindow(bool* p_open)
{
    if (!ImGui::Begin("Exercise 1", p_open))
    {
        ImGui::End();
        return;
    }
    static int nrElements{ 100000000 };

    ImGui::InputInt("#samples", &nrElements, m_samplesStep);
    
    if (ImGui::Button("Trash the cache"))
    {
        m_vectFirstEx.resize(nrElements);
        m_timesFirstEx.clear();
        for (int stepsize = 1; stepsize <= 1024; stepsize *= 2)
        {
            auto start = std::chrono::high_resolution_clock::now();
            for (int i = 0; i < m_vectFirstEx.size(); i += stepsize)
            {
                m_vectFirstEx[i] *= 2;
            }
            auto end = std::chrono::high_resolution_clock::now();
            auto elapsedTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
            m_timesFirstEx.push_back(float(elapsedTime));
        }
        m_isTrashCachePressed = true;
    }
    
    if(m_isTrashCachePressed)
        ImGui::PlotLines("", m_timesFirstEx.data(), int(m_timesFirstEx.size()),0,nullptr,0,FLT_MAX,ImVec2(330,200));

   



    ImGui::End();
}

void dae::GraphComponent::ShowExTwoWindow(bool* p_open)
{
    if (!ImGui::Begin("Exercise 2", p_open))
    {
        ImGui::End();
        return;
    }
    static int nrElements{ 1000000 };

    ImGui::InputInt("#samples", &nrElements, m_samplesStep);

    // Non-ptr GO
    if (ImGui::Button("Trash the cache with GameObject3D"))
    {
        m_vectGO.resize(nrElements);
        m_timesGO.clear();
        for (int stepsize = 1; stepsize <= 1024; stepsize *= 2)
        {
            auto start = std::chrono::high_resolution_clock::now();
            for (int i = 0; i < m_vectGO.size(); i += stepsize)
            {
                m_vectGO[i].id *= 2;
            }
            auto end = std::chrono::high_resolution_clock::now();
            auto elapsedTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
            m_timesGO.push_back(float(elapsedTime));
        }
        m_isTrashCacheGoPressed = true;
    }
    if(m_isTrashCacheGoPressed)
        ImGui::PlotLines("", m_timesGO.data(), int(m_timesGO.size()), 0, nullptr, 0, FLT_MAX, ImVec2(330, 200));

    // Ptr GO

    if (ImGui::Button("Trash the cache with GameObject3DAlt"))
    {
        m_vectGOAlt.resize(nrElements);
        m_timesGOAlt.clear();
        for (int stepsize = 1; stepsize <= 1024; stepsize *= 2)
        {
            auto start = std::chrono::high_resolution_clock::now();
            for (int i = 0; i < m_vectGOAlt.size(); i += stepsize)
            {
                if (m_vectGOAlt[i] == nullptr) continue;
                m_vectGOAlt[i]->id *= 2;
            }
            auto end = std::chrono::high_resolution_clock::now();
            auto elapsedTimeAlt = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
            m_timesGOAlt.push_back(float(elapsedTimeAlt));
        }
        m_isTrashCacheGoAltPressed = true;
    }

    if (m_isTrashCacheGoAltPressed)
        ImGui::PlotLines("", m_timesGOAlt.data(), int(m_timesGOAlt.size()), 0, nullptr, 0, FLT_MAX, ImVec2(330, 200));

    
    
    ImGui::End();
}



void dae::GraphComponent::RenderUI()
{
	static bool open = true;
	ShowExOneWindow(&open);
    ShowExTwoWindow(&open);
}