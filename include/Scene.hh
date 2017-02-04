#pragma once

#include <vector>
#include <list>
#include <string>
#include <map>
#include "GameObject.hh"
#include "Camera.hh"
#include "EndBlock.hh"

class Scene
{
private:
	std::vector<GameObject*>	_movingGameObjects;
	std::vector<GameObject*>	_fixedGameObjects;
	std::vector<EndBlock*>		_endBlocs;
	Camera						*_cam;

  Scene();
  ~Scene();

  Scene(const Scene&);
  Scene& operator=(const Scene&);

  static Scene _instance;

public:
	static Scene& getInstance();

	void update(float deltaTime);

	Scene		*addGameObject(GameObject *go);
	Scene		*addCameras(Camera *cam);
	Scene		*addEnd(EndBlock *end);

	bool		isEnded() const;
	std::string	getWinner() const;

	void		clearScene();

	template<class T>
	GameObject* addGameObject(const Vector::Vector2<float>& position = Vector::Vector2<float>::Zero, const std::string& name = "")
	{
		GameObject* ret = new T(position, name);
		_gameObjects.push_back(ret);
		return ret;
	}

	// you should not need this function
	// use GameObject.setToDestroy(true) instead;
	// and the GO will be destroy at the end of the frame
	// use this one if you really want to destroy the GO even if its death flag is false
	// yet, it may be called whereas an other GO needs the GO you're erasing, and A LOT OF SHIT will happen
	// unless you know exactly what you're doing, DO NOT use this function
	void removeGameObject(GameObject*const go);

	std::vector<GameObject*> getAllGameObjectInScene();
	GameObject* getGameObjectInSceneById(int id);
	GameObject* getGameObjectInSceneByName(const std::string& name); // return the first GO with the name "name"
	std::vector<GameObject*> getGameObjectsInSceneByName(const std::string& name); // return all GOs with the name "name"
};