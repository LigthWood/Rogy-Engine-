#ifndef SCENE_H
#define SCENE_H

#include <typeinfo>
#include <vector>
#include "Entity.h"
#include "../renderer/lighting.h"

enum SceneRequest
{
	SR_SAVE_SCENE,
	SR_LOAD_SCENE,
	SR_NEW_SCENE,
	SR_QUIT_GAME,
	SR_PAST_COPY,
	SR_PLAY_SCENE,
	SR_RECOMPILE_SCRIPTS,
	SR_SET_EDITOR_GRID,
	SR_SET_VIEW
};

class SceneManager

{
public:
	SceneManager();
	~SceneManager();

	std::vector<SceneRequest> m_requests;

	std::vector<std::string> spawn_requests;

	std::vector<EnttID> m_entities;

	std::string name;
	std::string path;

	Entity Root;

	Entity* GetRoot();
	Entity* AddEntity(string ent_name);
	Entity* AddEntity(EnttID entity_id, std::string Name);
	Entity* FindEntity(EnttID entity_id);
	void SetEntityParent(EnttID target, EnttID newParent);
	bool DestroyEntity(Entity* target);

	bool SaveEntityPrefab(EnttID id, const char* path);

	void PushRequest(SceneRequest req);
	std::vector<SceneRequest>& GetRequests();

	void SaveScene(std::string pth);
	void LoadScene(std::string pth);
	void NewScene();
	void QuitGame();

	// Spawning And Destroying
	// Engine Systems
	//----------------------------------------

	// Spawns entity with given blueprint path
	// TODO : Make this function return entity instance.
	void SpawnEntity(std::string pth);
	bool    RemoveEntity(EnttID entity_id);

	template<typename T>
	Entity* CreateEntity(std::string pth, glm::vec3 position, glm::vec3 rot)
	{
		Entity* ent = T::getIns()->SpawnEntity(pth);
		if (ent != nullptr) {
			ent->path = ""; // Spawn as clone
			ent->name += " (Clone)";
			ent->transform.SetPosition(position);
			ent->transform.SetAngels(rot);
		}
		return ent;
	}

	void SaveBP(cereal::BinaryOutputArchive& ar);

	// Editor Events
public:
	bool is_playing = false;
	bool game_view = false;
	bool show_grid = true;
	bool edit_grass = false;

private:
	void RemoveEntityID(EnttID eid);
	void RemoveEntityIDFromList(Entity* ent);
	EnttID CounterID;
	
};


#endif