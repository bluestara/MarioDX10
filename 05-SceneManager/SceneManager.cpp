#include "SceneManager.h"
#include "Animations.h"
#include "PlayScene.h"

SceneManager* SceneManager::__instance = nullptr;

SceneManager::SceneManager() {

}

SceneManager* SceneManager::GetInstance()
{
	if (__instance == nullptr) {
		__instance = new SceneManager();
	}
	return __instance;
}


void SceneManager::SwitchScene()
{
	if (next_scene < 0 || next_scene == current_scene) return;

	DebugOut(L"[INFO] Switching to scene %d\n", next_scene);

	scenes[current_scene]->Unload();

	CSprites::GetInstance()->Clear();
	CAnimations::GetInstance()->Clear();

	current_scene = next_scene;
	LPSCENE s = scenes[next_scene];
	CGame::GetInstance()->SetKeyHandler(s->GetKeyEventHandler());
	s->Load();
}

void SceneManager::InitiateSwitchScene(int scene_id)
{
	next_scene = scene_id;
}



void SceneManager::_ParseSection_SETTINGS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 2) return;
	if (tokens[0] == "start")
		next_scene = atoi(tokens[1].c_str());
	else
		DebugOut(L"[ERROR] Unknown game setting: %s\n", ToWSTR(tokens[0]).c_str());
}

void SceneManager::_ParseSection_SCENES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 2) return;
	int id = atoi(tokens[0].c_str());
	LPCWSTR path = ToLPCWSTR(tokens[1]);   // file: ASCII format (single-byte char) => Wide Char

	LPSCENE scene = new CPlayScene(id, path);
	scenes[id] = scene;
}