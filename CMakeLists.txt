cmake_minimum_required(VERSION 3.26)
project(Minigin)

if(EMSCRIPTEN)
  message("Using Emscripten!")
endif()

set(GAME_TARGET pacman)
if(EMSCRIPTEN)
  set(TARGET_PARAM )
else()
  set(TARGET_PARAM WIN32)
endif()

set(ENGINE_TARGET Minigin)
include(FetchContent)

# Add SDL3
find_package(SDL3 3.4 CONFIG QUIET)
if(NOT SDL3_FOUND)
  if (WIN32)
    FetchContent_Declare(
      SDL3
      URL https://www.libsdl.org/release/SDL3-devel-3.4.0-VC.zip
      DOWNLOAD_NO_PROGRESS ON
      DOWNLOAD_DIR ${CMAKE_BINARY_DIR}/downloads
    )
    FetchContent_MakeAvailable(SDL3)
    list(PREPEND CMAKE_PREFIX_PATH "${sdl3_SOURCE_DIR}")
    find_package(SDL3 CONFIG REQUIRED)
  else()
    FetchContent_Declare(
      SDL3
      GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
      GIT_TAG release-3.4.0
      GIT_SHALLOW TRUE
      GIT_PROGRESS TRUE
    )
    FetchContent_MakeAvailable(SDL3)
  endif()
endif()

# Add SDL3_ttf
find_package(SDL3_ttf 3.2.2 CONFIG QUIET)
if(NOT SDL3_ttf_FOUND)
  if (WIN32)
    FetchContent_Declare(
      SDL3_ttf
      URL https://www.libsdl.org/projects/SDL_ttf/release/SDL3_ttf-devel-3.2.2-VC.zip
      DOWNLOAD_NO_PROGRESS ON
      DOWNLOAD_DIR ${CMAKE_BINARY_DIR}/downloads
    )
    FetchContent_MakeAvailable(SDL3_ttf)
    list(PREPEND CMAKE_PREFIX_PATH "${sdl3_ttf_SOURCE_DIR}")
    find_package(SDL3_ttf CONFIG REQUIRED)
  else()
    FetchContent_Declare(
      SDL3_ttf
      GIT_REPOSITORY https://github.com/libsdl-org/SDL_ttf.git
      GIT_TAG release-3.2.2
      GIT_SHALLOW TRUE
      GIT_PROGRESS TRUE
    )
    set(SDL3TTF_INSTALL OFF)
    if(EMSCRIPTEN)
      list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/emscripten")
      set(SDL3TTF_USE_SYSTEM_FREETYPE ON)
      set(SDL3TTF_VENDORED OFF)
      set(SDLTTF_PLUTOSVG OFF)
      add_compile_options(-sUSE_FREETYPE=1 -sUSE_HARFBUZZ=1)
      add_link_options(-sUSE_FREETYPE=1 -sUSE_HARFBUZZ=1)
    endif()
    FetchContent_MakeAvailable(SDL3_ttf)
  endif()
endif()

# add sdl3_mixer
find_package(SDL3_mixer 3.2.0 CONFIG QUIET)
if(NOT SDL3_mixer_FOUND)
    FetchContent_Declare(
        SDL3_mixer
        GIT_REPOSITORY https://github.com/libsdl-org/SDL_mixer.git
        GIT_TAG release-3.2.0
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE
    )
    set(GLM_BUILD_LIBRARY OFF)
    FetchContent_MakeAvailable(SDL3_mixer)
endif()

# add glm
find_package(glm CONFIG QUIET)
if(NOT glm_FOUND)
  FetchContent_Declare(
    glm
    URL https://github.com/g-truc/glm/releases/download/1.0.3/glm-1.0.3.zip
    DOWNLOAD_NO_PROGRESS ON
    DOWNLOAD_DIR ${CMAKE_BINARY_DIR}/downloads
  )
  FetchContent_MakeAvailable(glm)
endif()

# add nlohmann json
find_package (nlohmann_json CONFIG QUIET)
if(NOT nlohmann_json_FOUND)
FetchContent_Declare(
   nlohmann_json
   URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz
    DOWNLOAD_NO_PROGRESS ON
    DOWNLOAD_DIR ${CMAKE_BINARY_DIR}/downloads
  )
  FetchContent_MakeAvailable(nlohmann_json)
 endif()

# Dear ImGui
FetchContent_Declare(
  imgui
  GIT_REPOSITORY https://github.com/ocornut/imgui
  GIT_TAG v1.92.5-docking
  GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(imgui)

add_library(imgui STATIC
  ${imgui_SOURCE_DIR}/imgui.cpp
  ${imgui_SOURCE_DIR}/imgui_draw.cpp
  ${imgui_SOURCE_DIR}/imgui_tables.cpp
  ${imgui_SOURCE_DIR}/imgui_widgets.cpp
  ${imgui_SOURCE_DIR}/imgui_demo.cpp
  ${imgui_SOURCE_DIR}/backends/imgui_impl_sdl3.cpp
  ${imgui_SOURCE_DIR}/backends/imgui_impl_sdlrenderer3.cpp)

target_include_directories(imgui PUBLIC ${imgui_SOURCE_DIR} ${sdl3_SOURCE_DIR}/include)
target_link_libraries(imgui PUBLIC SDL3::SDL3)
# enable c++20 features
target_compile_features(imgui PUBLIC cxx_std_20)

if (WIN32)
  # Add VLD (Visual Leak Detector) for memory leak detection on Windows
  find_package(VLD CONFIG)
endif()

# ENGINE LIBRARY
add_library(${ENGINE_TARGET} STATIC
  Minigin/Font.cpp
  Minigin/GameObject.cpp
  Minigin/Component.cpp
  Minigin/InputManager.cpp
  Minigin/Minigin.cpp
  Minigin/Renderer.cpp
  Minigin/ResourceManager.cpp
  Minigin/Scene.cpp
  Minigin/SceneManager.cpp
  Minigin/TextComponent.cpp
  Minigin/Texture2D.cpp
  Minigin/Transform.cpp
  Minigin/RenderComponent.cpp
  
  
  Minigin/Controller.cpp
  Minigin/SpriteComponent.cpp
  Minigin/Hitbox.cpp
  Minigin/CollisionManager.cpp
  Minigin/SoundSystem.cpp
  Minigin/ServiceLocator.cpp
  Minigin/Draw.cpp
  Minigin/WindowConfig.cpp
  Minigin/Subject.cpp
  Minigin/InputData.cpp
  Minigin/EventQueue.cpp 
  Minigin/Event.cpp
  Minigin/Command.cpp 
)
target_compile_features(${ENGINE_TARGET} PUBLIC cxx_std_20)

target_include_directories(${ENGINE_TARGET} PUBLIC
  ${CMAKE_SOURCE_DIR}/Minigin/
  ${imgui_SOURCE_DIR}
  ${glm_SOURCE_DIR}
  ${sdl3_mixer_SOURCE_DIR}/include
  $<$<CONFIG:Debug>:${VLD_INCLUDE_DIRS}>
)

target_link_libraries(${ENGINE_TARGET} PUBLIC
  SDL3::SDL3
  SDL3_ttf::SDL3_ttf
  SDL3_mixer::SDL3_mixer
  glm::glm
  imgui
  $<$<CONFIG:Debug>:${VLD_LIBRARIES}>
  $<$<PLATFORM_ID:Windows>:xinput.lib>
)

if(MSVC)
  # compile at warning level 4 + treat warnings as errors
  target_compile_options(${ENGINE_TARGET} PRIVATE /W4 /WX)
else()
  target_compile_options(${ENGINE_TARGET} PRIVATE -Wall -Wextra -Werror)
endif()

# GAME
add_executable(${GAME_TARGET}
    PacMan/Main.cpp
    PacMan/Commands.cpp
    PacMan/HealthComponentUI.cpp
    PacMan/PlayerMovement.cpp
    PacMan/HealthComponent.cpp
    PacMan/MenuManager.cpp
    PacMan/ButtonComponent.cpp
    PacMan/Events.cpp
    PacMan/GamestateManager.cpp
    PacMan/Graph.cpp
    PacMan/LevelLoader.cpp
    PacMan/GhostState.cpp
    PacMan/GhostComponent.cpp
    PacMan/TargetMoverComponent.cpp
    PacMan/FruitComponent.cpp
    PacMan/FruitSpawner.cpp
    PacMan/MoveStrategies.cpp
    PacMan/GameState.cpp
    PacMan/GamestateManager.cpp
    PacMan/SoundManager.cpp
    PacMan/ScoreComponentUI.cpp
    PacMan/ScoreComponent.cpp
    PacMan/Pellets.cpp
    PacMan/FruitSpawner.cpp
    PacMan/FPSComponent.cpp
    PacMan/SceneLoader.cpp
    PacMan/PacmanAnimator.cpp
    PacMan/LetterSelectComponent.cpp
    PacMan/NameSelectComponent.cpp
    PacMan/HighscoreParser.cpp
    PacMan/RespawnComponent.cpp)

target_compile_features(${GAME_TARGET} PUBLIC cxx_std_20)

target_include_directories(${GAME_TARGET} PRIVATE
  ${CMAKE_SOURCE_DIR}/PacMan/
  ${CMAKE_SOURCE_DIR}/Minigin/
  ${imgui_SOURCE_DIR}
  ${glm_SOURCE_DIR}
  $<$<CONFIG:Debug>:${VLD_INCLUDE_DIRS}>
)

target_link_libraries(${GAME_TARGET} PRIVATE
  ${ENGINE_TARGET}
  nlohmann_json::nlohmann_json
)

target_compile_definitions(${GAME_TARGET} PRIVATE
    DATA_PATH="${CMAKE_SOURCE_DIR}/Data"
)

if(MSVC)
# compile at warning level 4 + treat warnings as errors
  target_compile_options(${GAME_TARGET} PRIVATE /W4 /WX)
else()
  target_compile_options(${GAME_TARGET} PRIVATE -Wall -Wextra -Werror)
endif()

if(EMSCRIPTEN)
  set(EMSCRIPTEN_COMPILE_FLAGS "-g")
  set(EMSCRIPTEN_LINK_FLAGS "-sUSE_FREETYPE=1 -sUSE_HARFBUZZ=1 -g -sALLOW_MEMORY_GROWTH --preload-file \"${CMAKE_SOURCE_DIR}/Data@/\"")
  set_target_properties(${GAME_TARGET} PROPERTIES
    COMPILE_FLAGS "${EMSCRIPTEN_COMPILE_FLAGS}"
    LINK_FLAGS "${EMSCRIPTEN_LINK_FLAGS}"
  )
  add_custom_command(TARGET ${GAME_TARGET} POST_BUILD
    COMMAND "${CMAKE_COMMAND}" -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/web" "$<TARGET_FILE_DIR:${GAME_TARGET}>/"
  )
  set(CMAKE_EXECUTABLE_SUFFIX ".html")

elseif(WIN32)
  set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${GAME_TARGET}) # set startup project
  set_target_properties(${GAME_TARGET} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "$<TARGET_FILE_DIR:${GAME_TARGET}>")

  foreach(dllTarget IN ITEMS SDL3::SDL3 SDL3_ttf::SDL3_ttf SDL3_mixer::SDL3_mixer)
    add_custom_command(TARGET ${GAME_TARGET} POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "$<TARGET_FILE:${dllTarget}>"
        "$<TARGET_FILE_DIR:${GAME_TARGET}>"
      VERBATIM
    )
  endforeach()

  add_custom_command(TARGET ${GAME_TARGET} POST_BUILD
    COMMAND "${CMAKE_COMMAND}" -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/Data" "$<TARGET_FILE_DIR:${GAME_TARGET}>/Data"
  )
endif()
