#pragma once
#include "Scene.h"
#include "Utils.h"
#include "debug.h"

class SceneManager
{
private:
	static SceneManager* __instance;
	SceneManager();

	unordered_map<int, LPSCENE> scenes;
	int current_scene;
	int next_scene = -1;

public:
	static SceneManager* GetInstance();

	LPSCENE GetCurrentScene() { return scenes[current_scene]; }

	void _ParseSection_SETTINGS(string line);
	void _ParseSection_SCENES(string line);

	void SwitchScene();
	void InitiateSwitchScene(int scene_id);
};

