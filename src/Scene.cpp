#include "Scene.hh"

Scene::Scene()
{
}


Scene::~Scene()
{
}

Scene Scene::_instance = Scene();

Scene &Scene::getInstance()
{
  return _instance;
}

#include <iostream>


Scene		*Scene::addGameObject(GameObject *go) {
  if (go->getRigidBody().IsFixe()) {
    for (auto it = _fixedGameObjects.begin(); it != _fixedGameObjects.end(); it++) {
      if ((*it)->getPosition().x() >= go->getPosition().x()) {
        _fixedGameObjects.insert(it, go);
        return this;
      }
    }
    _fixedGameObjects.push_back(go);
  }
  else
    _movingGameObjects.push_back(go);
  //_gameObjects.push_back(go);
  return this;
}

Scene		*Scene::addCameras(Camera *cam) {
  if (_cam != NULL)
    delete _cam;
  _cam = cam;
  return this;
}

Scene		*Scene::addEnd(EndBlock *end) {
	_endBlocs.push_back(end);
	return addGameObject(end);
}

bool		Scene::isEnded() const {
	for (auto end : _endBlocs)
		if (end->isEnded())
			return true;
	return false;
}

std::string	Scene::getWinner() const {
	for (auto end : _endBlocs)
		if (end->isEnded())
			return end->getWinner();
	return "Nobody";
}

void		Scene::clearScene(){
	/*for (auto it = _fixedGameObjects.begin(); it != _fixedGameObjects.end(); it++)
		delete *it;
	for (auto it = _movingGameObjects.begin(); it != _movingGameObjects.end(); it++)
		delete *it;*/

	_fixedGameObjects.clear();
	_movingGameObjects.clear();
	_endBlocs.clear();
}

void Scene::update(float deltaTime)
{
  std::vector<GameObject *>	GoOnCam = (_cam == NULL ? _fixedGameObjects : _cam->getGoOnScreen(_fixedGameObjects));

  for (auto Moving = _movingGameObjects.begin(); Moving != _movingGameObjects.end(); ++Moving) {
    for (auto Fixe = GoOnCam.begin(); Fixe != GoOnCam.end(); Fixe++)
		if ((*Moving)->CheckCollisionWith(*Fixe)) {
		//std::cout << "Collide : " << (*Fixe)->getName() << " & " << (*Moving)->getName() << "\n";
			(*Moving)->ResolveCollisionWith(*Fixe);
		}

    for (auto Other = Moving + 1; Other != _movingGameObjects.end(); Other++)
		if ((*Moving)->CheckCollisionWith(*Other)) {
			//std::cout << "Collide : " << (*Other)->getName() << " & " << (*Moving)->getName() << "\n";
			(*Moving)->ResolveCollisionWith(*Other);
		}
  }

  for (auto it = GoOnCam.begin(); it != GoOnCam.end(); ++it)
    (*it)->update(deltaTime);
  for (auto Moving = _movingGameObjects.begin(); Moving != _movingGameObjects.end(); ++Moving)
    (*Moving)->update(deltaTime);

  if (_cam != NULL)
    _cam->update(deltaTime);
}

void Scene::removeGameObject(GameObject*const go)
{
  auto it = std::find(_movingGameObjects.begin(), _movingGameObjects.end(), go);

  if (it == _movingGameObjects.end()) {
    it = std::find(_fixedGameObjects.begin(), _fixedGameObjects.end(), go);

    if (it != _fixedGameObjects.end()) {
      _fixedGameObjects.erase(it);
      delete *it;
    }
  }
  else {
    delete *it;
    _movingGameObjects.erase(it);
  }
}

std::vector<GameObject*> Scene::getAllGameObjectInScene()
{
  std::vector<GameObject*>	_gameObjects = _movingGameObjects;
  _gameObjects.insert(_gameObjects.end(), _fixedGameObjects.begin(), _fixedGameObjects.end());
  return _gameObjects;
}

GameObject* Scene::getGameObjectInSceneById(int id)
{
  auto ret = std::find_if(_movingGameObjects.begin(), _movingGameObjects.end(), [&id](GameObject* go) {return go->getId() == id; });
  if (ret == _movingGameObjects.end())
    ret = std::find_if(_fixedGameObjects.begin(), _fixedGameObjects.end(), [&id](GameObject* go) {return go->getId() == id; });
  if (ret != _fixedGameObjects.end())
    return *ret;
  return NULL;
}

GameObject* Scene::getGameObjectInSceneByName(const std::string& name)
{
  auto ret = std::find_if(_movingGameObjects.begin(), _movingGameObjects.end(), [&name](GameObject *go) {return go->getName() == name; });
  if (ret == _movingGameObjects.end())
    ret = std::find_if(_fixedGameObjects.begin(), _fixedGameObjects.end(), [&name](GameObject *go) {return go->getName() == name; });
  if (ret == _fixedGameObjects.end())
    return NULL;
  return *ret;
}

std::vector<GameObject*> Scene::getGameObjectsInSceneByName(const std::string& name)
{
  std::vector<GameObject*> ret;

  std::for_each(_fixedGameObjects.begin(), _fixedGameObjects.end(), [&name, &ret](GameObject *go) {if (go->getName() == name) ret.push_back(go); });
  std::for_each(_movingGameObjects.begin(), _movingGameObjects.end(), [&name, &ret](GameObject *go) {if (go->getName() == name) ret.push_back(go); });
  return ret;
}