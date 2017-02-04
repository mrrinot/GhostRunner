#include "GameObject.hh"
#include "Logger.hh"

unsigned int GameObject::_idCounter = 0;

GameObject::GameObject(const std::string &name, const Vector::Vector2<float>& upLeftCorner, const Vector::Vector2<float>& size, float weight, float MaxSpeed, bool ResolveCollide, bool isFixe) :
_RigidBody(upLeftCorner, size, weight, MaxSpeed, ResolveCollide, isFixe), _name(name) {
	_hitboxOutline = new AdditionalDrawableHitboxOutline(Vector::Vector2<float>(0.f, 0.f), size, sf::Color::Red);
  _id = _idCounter++;
  _toDestroy = false;
}

GameObject::GameObject(const std::string &name, const Vector::Vector2<float>& upLeftCorner, const Vector::Vector2<float>& size, bool ResolveCollide, bool isFixe) :
_RigidBody(upLeftCorner, size, ResolveCollide, isFixe), _name(name) {
  _hitboxOutline = new AdditionalDrawableHitboxOutline(Vector::Vector2<float>(0.f, 0.f), size, sf::Color::Red);
  _id = _idCounter++;
  _toDestroy = false;
}

GameObject::~GameObject() {
  for (auto it = _additionalInfo.begin(); it != _additionalInfo.end(); it++) {
    delete *it;
    it = _additionalInfo.erase(it);
  }
}

#pragma region Simple Getter
unsigned int const						GameObject::getId() const {
  return this->_id;
}

std::string const &						GameObject::getName() const {
  return this->_name;
}

Vector::Vector2<float> const			GameObject::getPosition() const {
  return this->_RigidBody.getPos();
}

RigidBody								&GameObject::getRigidBody() {
  return _RigidBody;
}

Animator								&GameObject::getAnimator() {
  return _animator;
}

bool									GameObject::hasGraphicComponent() const {
  return _animator.getCurrentAnim() != NULL;
}

bool									GameObject::isInLayer(Layer::LayerTypes l) {
  return _RigidBody.isInLayer(l);
}

bool const								GameObject::getToDestroy() const {
  return _toDestroy;
}

float									GameObject::getWidth() const {
  return _RigidBody.getWidth();
}

float									GameObject::getLenght() const {
  return _RigidBody.getLenght();
}

#pragma endregion;
Animation*	GameObject::getGraphicComponent()
{
  return _animator.getCurrentAnim();
}

Animation*	GameObject::getGraphicComponent(const Vector::Vector2<float>& incr)
{
  if (!hasGraphicComponent())
    return nullptr;
  _animator.getCurrentAnim()->setSpritePos(_RigidBody.getPos() + incr);
  return _animator.getCurrentAnim();
}

void                                    GameObject::setColliderSize(const Vector::Vector2<float> &size)
{
  _RigidBody.setColliderSize(size);
  if (_hitboxOutline != nullptr)
    _hitboxOutline->setSize(size);
}

void									GameObject::setPosition(const Vector::Vector2<float>& pos)
{
  this->_RigidBody.getCollider().setPosition(pos);
}

void									GameObject::updatePosition(const Vector::Vector2<float>& incr)
{
  this->_RigidBody.getCollider().updatePosition(incr);
}

void									GameObject::update(float deltatime) {
  auto it = _collisionsWithMe.begin();

  while (it != _collisionsWithMe.end()) {
    if (it->second.first == STAYANDCHECKED)
      it->second.second->OnCollisionStay(this);
    else if (it->second.first == STAY) {
      it->second.second->OnCollisionExit(this);
      auto todelete = it;
      it++;
      _collisionsWithMe.erase(todelete);
      continue;
    }
    else if (it->second.first == ENTER)
      it->second.second->OnCollisionEnter(this);
    it->second.first = STAY;
    it++;
  }

  _RigidBody.udpdate(deltatime);

  if (hasGraphicComponent())
    _animator.getCurrentAnim()->setSpritePos(getPosition());

  for (auto it = _additionalInfo.begin(); it != _additionalInfo.end(); it++)
  if ((*it)->ToDelete()) {
    delete *it;
    it = _additionalInfo.erase(it);

    if (it == _additionalInfo.end())
      break;
  }
  else
    (*it)->update(deltatime);
}

bool    							GameObject::changeAnimation(const std::string &name, bool isRet) {
  if (isRet)
    return _animator.changeCurrentAnim(name);
  return _animator.changeCurrentAnim("ret_" + name);
}


#pragma region Collision
bool									GameObject::CheckCollisionWith(GameObject *other) {
  if (_RigidBody.isCollideWith(other->_RigidBody)) {
    if (this->_collisionsWithMe.find(other->getId()) == this->_collisionsWithMe.end())
      this->_collisionsWithMe[other->getId()] = std::pair<CollisionType, GameObject *>(ENTER, other);
    else
      this->_collisionsWithMe[other->getId()].first = STAYANDCHECKED;
    if (other->_collisionsWithMe.find(this->getId()) == other->_collisionsWithMe.end())
      other->_collisionsWithMe[this->getId()] = std::pair<CollisionType, GameObject *>(ENTER, this);
    else
      other->_collisionsWithMe[this->getId()].first = STAYANDCHECKED;

    return true;
  }
  return false;
}

void									GameObject::ResolveCollisionWith(GameObject *other) {
  if (_collisionsWithMe.find(other->getId()) == _collisionsWithMe.end())
    return;
  _RigidBody.resolveCollideWith(other->_RigidBody);
}

void									GameObject::OnCollisionEnter(GameObject *other) {

}

void									GameObject::OnCollisionStay(GameObject *other) {

}

void									GameObject::OnCollisionExit(GameObject *other) {

}
#pragma endregion

void									GameObject::setToDestroy(bool b) {
  _toDestroy = b;
}

GameObject*								GameObject::addLayer(Layer::LayerTypes l) {
  _RigidBody.addLayer(l);
  return this;
}

GameObject*								GameObject::removeLayer(Layer::LayerTypes l) {
  _RigidBody.removeLayer(l);
  return this;
}

GameObject*                             GameObject::addAnimation(const std::string &name, Animation *anim)
{
  _animator.addAnim(name, anim);
  return this;
}

bool									GameObject::hasAdditionalInfos() const {
  return !_additionalInfo.empty();
}

std::vector<IAdditionalDrawableInfo *>	&GameObject::getAdditionalInfos() {
  return _additionalInfo;
}

void									GameObject::addAdditionalInfo(IAdditionalDrawableInfo *info) {
  _additionalInfo.push_back(info);
}

void                                    GameObject::switchHitbox(bool switched)
{
  if (switched)
    _additionalInfo.push_back(_hitboxOutline);
  else
    _additionalInfo.erase(std::find(_additionalInfo.begin(), _additionalInfo.end(), _hitboxOutline));
}

const std::map<unsigned int, std::pair<CollisionType, GameObject *>> &GameObject::getCollisionsWithMe() const{
	return _collisionsWithMe;
}