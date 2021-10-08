#pragma once

#include "UIComponent.h"

class ConfigurationWindow : public UIComponent
{
public:
	ConfigurationWindow(Application* app, std::string title, bool* open, ImGuiWindowFlags flags);
	update_status Update() override;
};

static int initialWinSize;
static int initialWinAudio;
static int newWinHeight, newWinWidth;
static float initialWinBrightness;
static bool vsync;
static bool fullscreenActive;
