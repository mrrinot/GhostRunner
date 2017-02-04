#include "Camera.hh"
#include "Player.hh"
#include "SoundEngine.hh"
#include "Scene.hh"
#include <iostream>
#include <algorithm>

Camera::Camera(const Vector::Vector2<float>& position, const Vector::Vector2<float>& size, bool allowBackward, Animation *back) :
_pos(position), _size(size), _allowBackward(allowBackward)
{
	_background = back;
}

Camera::~Camera()
{
}

void Camera::addObjectToFollow(GameObject *go)
{
	_FollowingList.push_back(go);
}

void Camera::setPos(const Vector::Vector2<float>& position) {
	_pos = position;
}

void Camera::resetObjectToFollow() {
	_FollowingList.clear();
}

void Camera::update(float deltatime)
{
#pragma region Conpute Position of Camera depending on _FollowingList
	Vector::Vector2<float>	objToFollow = Vector::Vector2<float>::Zero;
	Vector::Vector2<float>	avrToFollow = Vector::Vector2<float>::Zero;
	float						numOfPlayer = 0.0f;

	// zone a entrer dedans sur les bord pour bouger en (40% de la taille en x et 20% en y) 
	Vector::Vector2<float>	marge = Vector::Vector2<float>(_size.x() * 0.4f, _size.y() * 0.2f);

	// Get all GameObject on the good layer
	for (auto go : _FollowingList)
	{
		if (go->isInLayer(Layer::PLAYER))
		{
			objToFollow += go->getPosition() + Vector::Vector2<float>(go->getWidth() / 2.0f, go->getLenght() / 2.0f);
			numOfPlayer += 1.0f;
		}
		avrToFollow += go->getPosition() + Vector::Vector2<float>(go->getWidth() / 2.0f, go->getLenght() / 2.0f);
	}

	// If more than 1 object and 0 object on the good layer, do average of all GameObject
	if (_FollowingList.size() > 0 && numOfPlayer == 0.0f)
		avrToFollow = Vector::Vector2<float>(avrToFollow.x() / (float)_FollowingList.size(), avrToFollow.y() / (float)_FollowingList.size());
	// If GameObject to follow on good layer, do the average of the game object on the good layer
	else if (numOfPlayer != 0.0f)
		avrToFollow = Vector::Vector2<float>(objToFollow.x() / numOfPlayer, objToFollow.y() / numOfPlayer);
	// Aucun object a afficher : stop (exeption ?)
	else
		return;

	// If not on the cameras, set pos on center #NotSmooth
	if (avrToFollow.x() < _pos.x() || (_pos.x() + _size.x()) < avrToFollow.x())
		_pos.x(avrToFollow.x());
	// Follow en X
	else if (avrToFollow.x() < _pos.x() + marge.x() && _allowBackward)
		_pos.x(avrToFollow.x() - marge.x());
	else if ((_pos.x() + _size.x()) - marge.x() < avrToFollow.x())
		_pos.x(avrToFollow.x() - (_size.x() - marge.x()));

	// If not on the cameras, set pos on center #NotSmooth
	if (avrToFollow.y() < _pos.y() || (_pos.y() + _size.y()) < avrToFollow.y())
		_pos.y(avrToFollow.y());
	// Follow en Y
	else if (avrToFollow.y() < _pos.y() + marge.y())
		_pos.y(avrToFollow.y() - marge.y());
	else if ((_pos.y() + _size.y()) - marge.y() < avrToFollow.y())
		_pos.y(avrToFollow.y() - (_size.y() - marge.y()));
#pragma endregion

#pragma region Move all the _FollowingList in the screen
	for (auto go : _FollowingList) {
		//if (go->isInLayer(Layer::PLAYER))
		//	continue;

		if (go->getPosition().x() < _pos.x())
			go->setPosition(Vector::Vector2<float>(_pos.x(), go->getPosition().y()));
		else if ((go->getPosition().x() + go->getWidth()) > (_pos.x() + _size.x()))
			go->setPosition(Vector::Vector2<float>(_pos.x() + _size.x() - go->getWidth(), go->getPosition().y()));

		if (go->getPosition().y() < _pos.y())
			go->setPosition(Vector::Vector2<float>(go->getPosition().x(), _pos.y()));
		else if ((go->getPosition().y() + go->getLenght()) > (_pos.y() + _size.y()))
			go->setPosition(Vector::Vector2<float>(go->getPosition().x(), _pos.y() + _size.y() - go->getLenght()));
	}
#pragma endregion
}


const Vector::Vector2<float>		&Camera::getPos() const {
	return _pos;
}

const Vector::Vector2<float>		&Camera::getSize() const {
	return _size;
}

std::vector<GameObject *> Camera::getGoOnScreen()
{
	std::vector<GameObject *>	_visibleGo;

	// Get Visible GO
	float xMin = _pos.x(), xMax = _pos.x() + _size.x(); // Add marge here ?
	_visibleGo.clear();
	for (auto go : Scene::getInstance().getAllGameObjectInScene())
		if ((go->getPosition().x() + go->getWidth()) >= xMin) {
		if (go->getPosition().x() > xMax) {
			if (go->getRigidBody().IsFixe())
				break;
		}
		else
			_visibleGo.push_back(go);
		}

	/*std::sort(_visibleGo.begin(), _visibleGo.end(), [](GameObject* a, GameObject* b) -> float {
		if (a->hasGraphicComponent() && b->hasGraphicComponent())
		return a->getGraphicComponent()->getZPos() - b->getGraphicComponent()->getZPos();
		return 0.f;
		});*/

	std::reverse(_visibleGo.begin(), _visibleGo.end());

	return _visibleGo;
}

std::vector<GameObject *> Camera::getGoOnScreen(std::vector<GameObject *>& golist)
{
	std::vector<GameObject *>	_VisibleGo;

	// Get Visible GO
	float xMin = _pos.x(), xMax = _pos.x() + _size.x(); // Add marge here ?
	_VisibleGo.clear();
	for (auto go : golist)
		if ((go->getPosition().x() + go->getWidth()) >= xMin) {
		if (go->getPosition().x() > xMax) {
			if (go->getRigidBody().IsFixe())
				break;
		}
		else
			_VisibleGo.push_back(go);
		}
	return _VisibleGo;
}

void Camera::drawBackground(sf::RenderWindow& window) {
	if (_background == nullptr)
		return;

	float tileoffset = std::fmod(this->_pos.x(), _background->getCurrentFrame()->getGlobalBounds().width);
	float yOffset = -1300.f - this->_pos.y();

	if (this->_pos.x() < 0.f) {
		_background->setSpritePos(Vector::Vector2<float>(-(_background->getCurrentFrame()->getGlobalBounds().width + this->_pos.x()), yOffset));
		window.draw(*_background->getCurrentFrame());
	}

	_background->setSpritePos(Vector::Vector2<float>(-tileoffset, yOffset));
	window.draw(*_background->getCurrentFrame());
	_background->setSpritePos(Vector::Vector2<float>((_background->getCurrentFrame()->getGlobalBounds().width - tileoffset), yOffset));
	window.draw(*_background->getCurrentFrame());

}