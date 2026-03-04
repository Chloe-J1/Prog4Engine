#include "GraphComponent.h"
#include "imgui.h"

#include <chrono>

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
    std::vector<float> vect(nrElements);

    ImGui::InputInt("#samples", &nrElements, m_samplesStep);
    
    if (ImGui::Button("Trash the cache"))
    {
        if (m_isFirstValuesCalc == false)
        {
            for (int stepsize = 1; stepsize <= 1024; stepsize *= 2)
            {
                auto start = std::chrono::high_resolution_clock::now();
                for (int i = 0; i < vect.size(); i += stepsize)
                {
                    vect[i] *= 2;
                }
                auto end = std::chrono::high_resolution_clock::now();
                auto elapsedTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
                m_timesFirstEx.push_back(float(elapsedTime));
            }
            m_isFirstValuesCalc = true;
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
    static int nrElementsGO{ 1000000 };
    std::vector<gameobject> vect(nrElementsGO);

    ImGui::InputInt("#samples", &nrElementsGO, m_samplesStep);

    // Non-ptr GO
    if (ImGui::Button("Trash the cache with GameObject3D"))
    {
        
        if (m_isGOValuesCalc == false)
        {

            for (int stepsize = 1; stepsize <= 1024; stepsize *= 2)
            {
                auto start = std::chrono::high_resolution_clock::now();
                for (int i = 0; i < vect.size(); i += stepsize)
                {
                    vect[i].id *= 2;
                }
                auto end = std::chrono::high_resolution_clock::now();
                auto elapsedTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
                m_timesGO.push_back(float(elapsedTime));
            }
            m_isGOValuesCalc = true;
        }
        m_isTrashCacheGoPressed = true;
    }
    if(m_isTrashCacheGoPressed)
        ImGui::PlotLines("", m_timesGO.data(), int(m_timesGO.size()), 0, nullptr, 0, FLT_MAX, ImVec2(330, 200));

    // Ptr GO
    static int nrElementsGOAlt{ 1000000 };
    std::vector<gameobjectAlt> vectAlt(nrElementsGOAlt);

    ImGui::InputInt("#samples", &nrElementsGOAlt, m_samplesStep);

    if (ImGui::Button("Trash the cache with GameObject3DAlt"))
    {

        if (m_isGOAltValuesCalc == false)
        {

            for (int stepsize = 1; stepsize <= 1024; stepsize *= 2)
            {
                auto start = std::chrono::high_resolution_clock::now();
                for (int i = 0; i < vectAlt.size(); i += stepsize)
                {
                    vectAlt[i].id *= 2;
                }
                auto end = std::chrono::high_resolution_clock::now();
                auto elapsedTimeAlt = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
                m_timesGOAlt.push_back(float(elapsedTimeAlt));
            }
            m_isGOAltValuesCalc = true;
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