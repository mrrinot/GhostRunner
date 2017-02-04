#include "Player.hh"
#include "InputEngine.hh"
#include "SoundEngine.hh"
#include "Scene.hh"
#include "Logger.hh"
#include "AdditionalDrawableText.hh"
#include <iostream>
#include "Dash.hh"
#include "Dodge.hh"
#include "Inflate.hh"

const float Player::TAKEOVER_TIME = 60.f; // 60 = 1 sec
const float	Player::TAKEOVER_SPEED_DIVIDOR = 2.f;
const float	Player::TAKEOVER_DECLINE_COEF = 0.5f;

const float	Player::GHOST_MAX_SPEED = 7.f;
const float	Player::PLAYER_MAX_SPEED = 5.f;

Player::Player(const std::string &name, const Vector::Vector2<float>& upLeftCorner, const Vector::Vector2<float>& size)
: GameObject(name, upLeftCorner, size, 1, 5, true, false), _isGoingRight(true), _currentAction(nullptr), _isAnimAction(false)
{
	sf::Color textColor = sf::Color::White;

	if (name[name.length() - 1] == '2')
		textColor = sf::Color::Red;
	else if (name[name.length() - 1] == '3')
		textColor = sf::Color::Green;
	else if (name[name.length() - 1] == '4')
		textColor = sf::Color::Blue;
	_actionMap[DASH] = new Dash();
	_actionMap[DODGE] = new Dodge();
    _actionMap[INFLATE] = new Inflate();

	for (auto &&act : _actionMap)
		act.second->setPlayer(this);
	addLayer(Layer::PLAYERGHOST);
	addAdditionalInfo(new AdditionalDrawableText(Vector::Vector2<float>(0.f, -30.f), &(_RigidBody.getCollider()), name, textColor, 20));
	_damageLess = 0.0f;
	_steelLifeBar = NULL;
	_takeOver = 0.f;
	_isAggro = false;

	this->_steelLifeBar = new AdditionalDrawableBar(Vector::Vector2<float>(0.f, -10.f), Vector::Vector2<float>(75.f/*this->_RigidBody.getCollider().getWidth()*/, 5.f));
	_actionsCooldown[DASH] = new AdditionalDrawableBar(Vector::Vector2<float>(-20.f, 50.f), Vector::Vector2<float>(5.f, 75.f), sf::Color::Red);
	_actionsCooldown[DODGE] = new AdditionalDrawableBar(Vector::Vector2<float>(-27.f, 50.f), Vector::Vector2<float>(5.f, 75.f), sf::Color::Blue);
    _actionsCooldown[INFLATE] = new AdditionalDrawableBar(Vector::Vector2<float>(-27.f, 50.f), Vector::Vector2<float>(5.f, 75.f), sf::Color::Yellow);

    for (auto &&bar : _actionsCooldown)
    {
      bar.second->setVertical(true);
      addAdditionalInfo(bar.second);
    }
	this->addAdditionalInfo(this->_steelLifeBar);
}

Player::~Player()
{
  GameObject::~GameObject();

  if (_player == NULL)
    delete _player;
  if (_ghost == NULL)
    delete _ghost;
}

void Player::OnCollisionEnter(GameObject *other)
{
}

void Player::OnCollisionStay(GameObject *other)
{
  if (other->isInLayer(Layer::PLAYER) && this->isInLayer(Layer::GHOST)) {
    if (((Player *)other)->_damageLess > 0)
    {
      this->_isAggro = false;
      this->_RigidBody.setMaxSpeed(GHOST_MAX_SPEED);
      ((Player *)other)->_isAggro = false;
      ((Player *)other)->_RigidBody.setMaxSpeed(PLAYER_MAX_SPEED);
    }
    else if (this->_isAggro == false) {
      //_takeOver = 0.f;
      _isAggro = true;
      other->getRigidBody().setMaxSpeed(other->getRigidBody().getMaxSpeed() / TAKEOVER_SPEED_DIVIDOR);
      static_cast<Player *>(other)->setAggro(true);
    }
    else if (this->_takeOver >= TAKEOVER_TIME) {
      static_cast<Player *>(other)->resetSpeedOnDeath();
      static_cast<Player *>(other)->setLife(0);
      SoundEngine::getInstace().PlaySoundOnChannel("Jump", "Bond", "FX", false, true);

      if (!((Player *)other)->isAlive())
      {
        // 2 sec d'invulnerabilite
        this->setInvulnerability(200.0f);
        this->setLife(1);
        this->setPosition(other->getPosition());
        static_cast<Player *>(other)->repulseGhost();
        OnCollisionExit(other);
      }
    }
    //else
    //	this->_steelLifeBar->setPercentage(this->_takeOver / TAKEOVER_TIME);
  }
}

void Player::OnCollisionExit(GameObject *other)
{
  //SoundEngine::getInstace().PlaySoundOnChannel("Jump", "Bond", "Music", false, true);
  if (((other->isInLayer(Layer::PLAYER) && this->isInLayer(Layer::GHOST)) ||
    (other->isInLayer(Layer::GHOST) && this->isInLayer(Layer::PLAYER))) &&
    _isAggro != false) {
    //_steelLifeBar->setToDelete();
    //_steelLifeBar = NULL;
    //_takeOver = -1.f;
    _isAggro = false;

    if (other->isInLayer(Layer::PLAYER) && this->isInLayer(Layer::GHOST)) {

      static_cast<Player *>(other)->setAggro(false);
      for (auto elem : other->getCollisionsWithMe()) // Si toujours en collision avec un autre ghost
      if (elem.second.second->isInLayer(Layer::GHOST) && elem.second.second->getName() != this->getName()) {
        static_cast<Player *>(other)->setAggro(true);
        break;
      }
      other->getRigidBody().setMaxSpeed(other->getRigidBody().getMaxSpeed() * TAKEOVER_SPEED_DIVIDOR);
    }
  }
}

void		Player::repulseGhost() {
  Vector::Vector2<float>	direction;

  for (auto elem : _collisionsWithMe)
  if (elem.second.second->isInLayer(Layer::GHOST)) {
    direction.x((float)(rand() % 500 - 250));
    direction.y((float)(rand() % 500 - 250));

    direction.normalize();

    elem.second.second->getRigidBody().setVelocity(direction * 5.f);
  }

  direction.x((float)(rand() % 500 - 250));
  direction.y((float)(rand() % 500 - 250));

  direction.normalize();
  this->getRigidBody().setVelocity(direction * 5.f);
}

void		Player::resetSpeedOnDeath() {
  for (auto elem : _collisionsWithMe)
  if (elem.second.second->isInLayer(Layer::GHOST)) {
    static_cast<Player *>(elem.second.second)->setAggro(false);
    elem.second.second->getRigidBody().setMaxSpeed(GHOST_MAX_SPEED);
    elem.second.second->OnCollisionExit(this);
  }
  this->getRigidBody().setMaxSpeed(PLAYER_MAX_SPEED);
  this->setAggro(false);
}

void		Player::update(float deltatime)
{
#pragma region Get Input & Compute Direction
  Inputs					input = InputEngine::getInstance().GetInput(_deviceID);
  Vector::Vector2<float>	movement = Vector::Vector2<float>::Zero;
  bool isLanded = false;

  if (isAlive())
  {

    for (auto it = _collisionsWithMe.begin(); it != _collisionsWithMe.end(); it++)
    {
      if (((*it).second.second)->getRigidBody().IsResolveCollide() && //((*it).second.second)->isInLayer(Layer::WALL) && 
        std::abs(((*it).second.second)->getPosition().y() - (this->getPosition().y() + this->getLenght())) <= RigidBody::_epsilon &&
        ((*it).second.second)->getPosition().x() < (this->getPosition().x() + this->getWidth()) &&
        this->getPosition().x() < (((*it).second.second)->getPosition().x() + ((*it).second.second)->getWidth()))
      {
        _heroController.landing();
        isLanded = true;
        break;
      }
    }

    _heroController.doInput(input.Buttons, _button, input.X_Axis);
    movement.x((float)_heroController.getDirection() * 0.6f);
    if (movement.x() > 0 && !_isGoingRight)
      _isGoingRight = true;
    else if (movement.x() < 0 && _isGoingRight)
      _isGoingRight = false;
  }
  else
  {
    _ghostController.doInput(input.Buttons, _button, input.X_Axis, input.Y_Axis);
    if (_ghostController.getYDirection() != 0)
      movement.y(movement.y() + (0.1f * _ghostController.getYDirection()));
    if (_ghostController.getXDirection() != 0)
      movement.x(movement.x() + (0.1f * _ghostController.getXDirection()));
    if (movement.x() > 0 && !_isGoingRight)
      _isGoingRight = true;
    else if (movement.x() < 0 && _isGoingRight)
      _isGoingRight = false;
    changeAnimation("ghost", _isGoingRight);
  }
  //std::cout << "Player 1 : (" << getPosition().x() << ", " << getPosition().y() << ")\n";
  if (_damageLess > 0)
    _damageLess -= deltatime;

  if (!isAlive()) {
    if (_isAggro)
      _takeOver += deltatime;
    else if (!_isAggro && _takeOver > 0.f) {
      _takeOver -= deltatime * TAKEOVER_DECLINE_COEF;
      if (_takeOver < 0.f)
        _takeOver = 0.f;
    }
    if (_steelLifeBar != NULL)
      this->_steelLifeBar->setPercentage(this->_takeOver / TAKEOVER_TIME);
  }

#pragma endregion

  bool isfreinage = (movement == Vector::Vector2<float>::Zero);

  for (auto &&bar : _actionsCooldown)
  {
    bar.second->setPercentage(_actionMap[bar.first]->getCooldown() / _actionMap[bar.first]->getMaxCooldown());
  }

  if (!isAlive()) // Ghost
  {
    this->_RigidBody.addVelocity(movement * 5.f * deltatime);
    this->_RigidBody.setVelocity(_RigidBody.getVelocity() / (_isAggro ? 1.3f : 1.f));

    if (isfreinage) {
      Vector::Vector2<float>	direction = this->getRigidBody().getVelocity();
      direction.normalize(); // Normalisation du vecteur
      this->_RigidBody.addVelocity((-direction) * 0.05f);
    }
  // ACTION
    e_Action action = _ghostController.getAction();
    for (auto &&act : _actionMap)
      act.second->updateCooldown(deltatime);

    Vector::Vector2<float> speed;
    if (_currentAction == nullptr)
    {
      // LogInfo() << "NO ACTION";
      if (action != NONE && _actionMap[action]->getCooldown() <= 0.f)
      {
        // LogInfo() << "NO COOLDOWN, new action => " << action;
        _currentAction = _actionMap[action];
      }
    }
    if (_currentAction != nullptr)
    {
      // LogInfo() << "action updated";
      _currentAction->update(deltatime, speed);
      if (_currentAction->isFinished())
      {
        // LogInfo() << "ACTION ENDED INSECTS";
        _currentAction = nullptr;
      }
    }
    // LogInfo() << "NEW SPEED = " << speed.toString();
    /*
    if (direction.x() < 0 && movement.x() > 0 || direction.x() > 0 && movement.x() < 0)
    movement.x(movement.x() * 2.0f);
    if (direction.y() < 0 && movement.y() > 0 || direction.y() > 0 && movement.y() < 0)
    movement.y(movement.y() * 2.0f);
    */

  }
  else			// Alive
  {
    // If on Plateform && not moving
    Vector::Vector2<float> speed;
    if (isfreinage && isLanded && !_heroController.isJumping()) {
      //_rgbd->applyForce((-direction) * 1.0f);
      //_rgbd->setVelocity(Vector::Vector2<float>::Zero);
      this->_RigidBody.setVelocity(Vector::Vector2<float>::Zero);
      speed = _RigidBody.getVelocity();
      if (!_isAnimAction)
        changeAnimation("default", _isGoingRight);
    }
    else {
      speed = this->_RigidBody.getVelocity();
      // Gravity
      if (!isLanded)
      {
        speed += Vector::Vector2<float>(0.f, .5f);
        if (!_isAnimAction)
          changeAnimation("jump", _isGoingRight);
      }
      else
      {
        if (!_isAnimAction)
          changeAnimation("run", _isGoingRight);
      }
      if (_heroController.isJumping())
      {
        float strength = _heroController.getJumpStrength();
        if ((speed.y() == 0 && isLanded) || _heroController.canDoubleJump())
        {
          speed.y(0);
          _animator.getCurrentAnim()->reset();
          speed += Vector::Vector2<float>(0.f, -9.f);
        }
        if (strength > 30.f && strength < 175.f)
          speed += Vector::Vector2<float>(0.f, -0.5f);
      }
      speed += movement;
      speed /= (_isAggro == false ? 1.f : 1.15f);

      if (std::abs(speed.x()) > this->_RigidBody.getMaxSpeed())
        speed.x(((speed.x() >= 0) - (speed.x() < 0)) * this->_RigidBody.getMaxSpeed());
    }
      // ACTION MANAGEMENT
      e_Action action = _heroController.getAction();
      // LogInfo() << "action = " << action;
	  

	 
      for (auto &&act : _actionMap)
        act.second->updateCooldown(deltatime);

      if (_currentAction == nullptr)
      {
        // LogInfo() << "NO ACTION";
        if (action != NONE && _actionMap[action]->getCooldown() <= 0.f)
        {
          // LogInfo() << "NO COOLDOWN, new action => " << action;
          _currentAction = _actionMap[action];
        }
      }
      if (_currentAction != nullptr)
      {
        // LogInfo() << "action updated";
        _currentAction->update(deltatime, speed);
        if (_currentAction->isFinished())
        {
          // LogInfo() << "ACTION ENDED INSECTS";
          _currentAction = nullptr;
        }
      }
      // LogInfo() << "NEW SPEED = " << speed.toString();
      this->_RigidBody.setVelocity(speed, true);
  }

  GameObject::update(deltatime);
}

void		Player::updateLife(int update)
{
  setLife(_life + update);
}

Player*		Player::setLife(int life)
{
  if (life < 0)
    return this;

  for (auto &&bar : _actionsCooldown)
  {
    bar.second->setPercentage(0.f);
    _actionMap[bar.first]->resetCooldown();
  }
  _currentAction = nullptr;

  _takeOver = 0.0f;
  if (_steelLifeBar != NULL)
     this->_steelLifeBar->setPercentage(this->_takeOver / TAKEOVER_TIME);

  if (life == 0 && !_RigidBody.isInLayer(Layer::GHOST))
  {
    changeAnimation("ghost", true);

    _RigidBody.addLayer(Layer::GHOST);
    _RigidBody.addLayer(Layer::GHOST_WALL);
    _RigidBody.removeLayer(Layer::PLAYER);
    _RigidBody.removeLayer(Layer::WALL);

    _RigidBody.setMaxSpeed(GHOST_MAX_SPEED);
    setColliderSize(Vector::Vector2<float>(75.f, 75.f));

  }
  else if (life > 0 && !_RigidBody.isInLayer(Layer::PLAYER))
  {
    changeAnimation("default", true);

    _RigidBody.removeLayer(Layer::GHOST);
    _RigidBody.removeLayer(Layer::GHOST_WALL);
    _RigidBody.addLayer(Layer::PLAYER);
    _RigidBody.addLayer(Layer::WALL);

    _RigidBody.setMaxSpeed(PLAYER_MAX_SPEED);
    setColliderSize(Vector::Vector2<float>(60.f, 55.f));
  }

  // Life is life !! Lala la lala !
  _life = life;
  if (_life < 0)
    _life = 0;

  return this;
}

int			Player::getLife() const
{
  return _life;
}

Player      *Player::setAggro(bool aggro)
{
  _isAggro = aggro;
  return this;
}

bool        Player::isAggro() const
{
  return _isAggro;
}

bool		Player::isAlive() const
{
  return _life != 0;
}

bool        Player::facingRight() const
{
  return _isGoingRight;
}

void        Player::setAnimAction(bool isAnim)
{
  _isAnimAction = isAnim;
}

Player*		Player::setDevice(int id)
{
  _deviceID = id;
  return this;
}

int			Player::getDeviceID() const
{
  return _deviceID;
}

Player*		Player::setInvulnerability(float val)
{
  _damageLess = val;
  return this;
}