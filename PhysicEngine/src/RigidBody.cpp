#include "RigidBody.hh"

const float RigidBody::_epsilon = .1f;

// Construct
#pragma region Constructor/Destructor
RigidBody::RigidBody(const Vector::Vector2<float>& pos, const Vector::Vector2<float>& size, float weight, float MaxSpeed, bool ResolveCollide, bool isFixe) :
	_boxCollider(pos, size + pos), _weight(weight), _MaxSpeed(MaxSpeed), _MaxSpeedSquare(MaxSpeed * MaxSpeed), _isResolveCollide(ResolveCollide), _isFixe(isFixe), _velocity(0, 0)
{
	_elasticity = 0;
}

RigidBody::RigidBody(const Vector::Vector2<float>& pos, const Vector::Vector2<float>& size, bool ResolveCollide, bool isFixe) :
	_boxCollider(pos, size + pos), _isResolveCollide(ResolveCollide), _isFixe(isFixe), _velocity(0, 0)
{
	_MaxSpeed = 0;
	_weight = 0;
	_elasticity = 0;
}

RigidBody::RigidBody(const Colliders::BoxCollider& box, bool ResolveCollide, bool isFixe) :
_boxCollider(box), _isResolveCollide(ResolveCollide), _isFixe(isFixe), _velocity(0, 0)
{
	_MaxSpeed = 0;
	_weight = 0;
	_elasticity = 0;
}

RigidBody::~RigidBody() {

}
#pragma endregion

// Getters
#pragma region Getters
Vector::Vector2<float>	RigidBody::getVelocity() const {
	return _velocity;
}

float const				RigidBody::getWeight() const {
	return _weight;
}

float const				RigidBody::getMaxSpeed() const {
	return _MaxSpeed;
}

bool					RigidBody::IsFixe() const {
	return _isFixe;
}

bool					RigidBody::IsResolveCollide() const {
	return _isResolveCollide;
}

Vector::Vector2<float> const	&RigidBody::getPos() const {
	return _boxCollider.getUpLeftCorner();
}

Colliders::BoxCollider &RigidBody::getCollider() {
	return _boxCollider;
}

float					RigidBody::getWidth() const {
	return _boxCollider.getWidth();
}

float					RigidBody::getLenght() const {
	return _boxCollider.getLenght();
}
#pragma endregion

// Alter Velocity
#pragma region Alter Velocity
void					RigidBody::setVelocity(const Vector::Vector2<float>& velocity, bool force) {
	_velocity = velocity;

	if (force)
		return;

	if (std::abs(_velocity.x()) <= _epsilon) {
		_velocity.x(0.0f);
		
		if (std::abs(_velocity.y()) > _MaxSpeed) {
			_velocity.y(_MaxSpeed * (_velocity.y() < 0.0f ? -1.f : 1.f));
			return;
		}
	}

	if (std::abs(_velocity.y()) <= _epsilon) {
		_velocity.y(0.0f);

		if (std::abs(_velocity.x()) > _MaxSpeed) {
			_velocity.x(_MaxSpeed * (_velocity.x() < 0.0f ? -1.f : 1.f));
			return;
		}
	}

	// Calcul Vitesse
	float	SquareSpeed = _velocity.x() * _velocity.x() + _velocity.y() * _velocity.y();

	if (SquareSpeed > _MaxSpeedSquare && SquareSpeed > _epsilon) {
		float	coef = _MaxSpeed / sqrtf(SquareSpeed);
		_velocity *= coef;
	}
}

void					RigidBody::addVelocity(const Vector::Vector2<float>& velocity) {
	setVelocity(_velocity + velocity);
}

void					RigidBody::subVelocity(const Vector::Vector2<float>& velocity) {
	setVelocity(_velocity - velocity);
}

void					RigidBody::alterVelocity(const Vector::Vector2<float>& velocityMultiplicator) {
	setVelocity(Vector::Vector2<float>(velocityMultiplicator.x() * _velocity.x(), velocityMultiplicator.y() * _velocity.y()));
}
#pragma endregion

// Setters
#pragma region Setters
void					RigidBody::setWeight(float weight) {
	if (weight > 0.0f)
		_weight = weight;
}

void                    RigidBody::setColliderSize(const Vector::Vector2<float> &size)
{
  _boxCollider.setSize(size);
}

void					RigidBody::setMaxSpeed(float MaxSpeed) {
	if (MaxSpeed < 0.0f)
		return;
	//if (MaxSpeed > 7.f)
	//	MaxSpeed = 7.f;
	_MaxSpeed = MaxSpeed;
	_MaxSpeedSquare = MaxSpeed * MaxSpeed;
}

void					RigidBody::setFixe(bool isfixe) {
	_isFixe = isfixe;
}

void					RigidBody::setResolveColide(bool isResolveCollide) {
	_isResolveCollide = isResolveCollide;
}

void					RigidBody::setCollider(const Colliders::BoxCollider &box) {
	_boxCollider = box;
}
#pragma endregion

// Other Method
bool					RigidBody::isCollideWith(const RigidBody &other) const {
	return shareALayer(other) && Colliders::collide(other._boxCollider, this->_boxCollider);
}
#include <iostream>
void					RigidBody::resolveCollideWith(RigidBody &other, bool isTmpRGBD) {
	if ((this->IsFixe() && other.IsFixe()) ||
		!this->IsResolveCollide() || !other.IsResolveCollide())
		return;

	/*if (isTmpRGBD)
		std::cout << "Check Reroll\n";
	std::cout << "Me : (" << _boxCollider.getUpLeftCorner().x() << ", " << _boxCollider.getUpLeftCorner().y() << ") - (" << _boxCollider.getWidth() << ", " << _boxCollider.getLenght() << ")\n";
	std::cout << "Check With : (" << other._boxCollider.getUpLeftCorner().x() << ", " << other._boxCollider.getUpLeftCorner().y() << ") - (" << other._boxCollider.getWidth() << ", " << other._boxCollider.getLenght() << ")\n";
*/
#pragma region Resolve Stacked Object
	if (!isTmpRGBD) {
		if (other.IsFixe()) {
			bool found = false;

			for (auto it = _fixeCollideWithMe.begin(); it != _fixeCollideWithMe.end(); it++)
				if ((*it).getUpLeftCorner().x() == other._boxCollider.getUpLeftCorner().x() &&
					(*it).getDownRightCorner().x() == other._boxCollider.getDownRightCorner().x()) {

					if ((*it).getUpLeftCorner().y() > other._boxCollider.getUpLeftCorner().y())
						(*it).setPosition(other._boxCollider.getUpLeftCorner());
					(*it).setSize(Vector::Vector2<float>((*it).getWidth(), (*it).getLenght() + other._boxCollider.getLenght()));
					//std::cout << "Fusion : (" << (*it).getUpLeftCorner().x() << ", " << (*it).getUpLeftCorner().y() << ") - (" << (*it).getWidth() << ", " << (*it).getLenght() << ")\n";

					found = true;
					break;
				}
				else if ((*it).getUpLeftCorner().y() == other._boxCollider.getUpLeftCorner().y() &&
					(*it).getDownRightCorner().y() == other._boxCollider.getDownRightCorner().y()) {

					if ((*it).getUpLeftCorner().x() > other._boxCollider.getUpLeftCorner().x())
						(*it).setPosition(other._boxCollider.getUpLeftCorner());
					(*it).setSize(Vector::Vector2<float>((*it).getWidth() + other._boxCollider.getWidth(), (*it).getLenght()));
					//std::cout << "Fusion : (" << (*it).getUpLeftCorner().x() << ", " << (*it).getUpLeftCorner().y() << ") - (" << (*it).getWidth() << ", " << (*it).getLenght() << ")\n";

					found = true;
					break;
				}

			if (found) {
				_velocity = _originalVelocity;
				_boxCollider.setPosition(_originalPos);

				for (auto box : _fixeCollideWithMe) {
					RigidBody tmp(box);
					resolveCollideWith(tmp, true);
				}

				return;
			}
			else {
				_fixeCollideWithMe.push_back(other._boxCollider);
				if (other._boxCollider.getDownRightCorner().x() == this->_boxCollider.getUpLeftCorner().x() || // If not overlap
					other._boxCollider.getUpLeftCorner().x() == this->_boxCollider.getDownRightCorner().x() ||
					other._boxCollider.getDownRightCorner().y() == this->_boxCollider.getUpLeftCorner().y() ||
					other._boxCollider.getUpLeftCorner().y() == this->_boxCollider.getDownRightCorner().y())
					return;
			}
		}
	}
	else if (other._boxCollider.getDownRightCorner().x() == this->_boxCollider.getUpLeftCorner().x() || // If not overlap
			other._boxCollider.getUpLeftCorner().x() == this->_boxCollider.getDownRightCorner().x() ||
			other._boxCollider.getDownRightCorner().y() == this->_boxCollider.getUpLeftCorner().y() ||
			other._boxCollider.getUpLeftCorner().y() == this->_boxCollider.getDownRightCorner().y())
			return;
#pragma endregion

#pragma region Calcul Penetration (peneX, peneY)
	// Penetration x
	float peneX = 0.0f;
	bool containtInX = false;

	// this  : |__|		|__|
	// other :   |__|	   |__|
	if (other._boxCollider.getUpLeftCorner().x() <= this->_boxCollider.getDownRightCorner().x() &&
		this->_boxCollider.getDownRightCorner().x() < other._boxCollider.getDownRightCorner().x() &&
		this->_boxCollider.getUpLeftCorner().x() < other._boxCollider.getUpLeftCorner().x()) {
		peneX = other._boxCollider.getUpLeftCorner().x() - this->_boxCollider.getDownRightCorner().x();
	}
	// this  :   |__|	   |__|
	// other : |__|		|__|
	else if (other._boxCollider.getDownRightCorner().x() >= this->_boxCollider.getUpLeftCorner().x() &&
		this->_boxCollider.getUpLeftCorner().x() > other._boxCollider.getUpLeftCorner().x() &&
		this->_boxCollider.getDownRightCorner().x() > other._boxCollider.getDownRightCorner().x()) {
		peneX = other._boxCollider.getDownRightCorner().x() - this->_boxCollider.getUpLeftCorner().x();
	}
	// this  :   |__|		|______|
	// other : |______|		  |__|
	else {
		containtInX = true;
	}

	// Penetration y
	float peneY = 0.0f;
	bool containtInY = false;

	// this  : |__|		|__|
	// other :   |__|	   |__|
	if (other._boxCollider.getUpLeftCorner().y() <= this->_boxCollider.getDownRightCorner().y() &&
		this->_boxCollider.getDownRightCorner().y() < other._boxCollider.getDownRightCorner().y() &&
		this->_boxCollider.getUpLeftCorner().y() < other._boxCollider.getUpLeftCorner().y()) {
		peneY = other._boxCollider.getUpLeftCorner().y() - this->_boxCollider.getDownRightCorner().y();
	}
	// this  :   |__|	   |__|
	// other : |__|		|__|
	else if (other._boxCollider.getDownRightCorner().y() >= this->_boxCollider.getUpLeftCorner().y() &&
		this->_boxCollider.getUpLeftCorner().y() > other._boxCollider.getUpLeftCorner().y() &&
		this->_boxCollider.getDownRightCorner().y() > other._boxCollider.getDownRightCorner().y()) {
		peneY = other._boxCollider.getDownRightCorner().y() - this->_boxCollider.getUpLeftCorner().y();
	}
	// this  :   |__|		|______|
	// other : |______|		  |__|
	else {
		containtInY = true;
	}
#pragma endregion

	if (peneX == 0.0f && peneY == 0.0f) {
		//std::cout << "Exit - Penex : " << peneX << " / Peney : " << peneY << " / containtInX :" << (containtInX ? "True" : "False") << " / containtInY : " << (containtInY ? "True" : "False") << "\n";
		return;
	}

#pragma region Compute Collision
	float elasticity = std::max(this->_elasticity, other._elasticity);

	if ((std::abs(peneY) > std::abs(peneX) && peneX != .0f) || (peneY == .0f && containtInY) || 
		(std::abs(peneX) > 0.f && ((getVelocity().y() > 0.f && peneY > 0.f) || (getVelocity().y() < 0.f && peneY < 0.f)))) {
		if (other.IsFixe()) {
			this->_boxCollider.updatePosition(Vector::Vector2<float>(peneX, .0f));
			this->setVelocity(Vector::Vector2<float>(0.f, this->_velocity.y()), true);
			//std::cout << "Resolve X - Penex : " << peneX << " / Peney : " << peneY << " - (" << _velocity.x() << ", " << _velocity.y() << ")\n";
			return;
		}
	}
	else if ((std::abs(peneY) <= std::abs(peneX) && peneY != .0f) || (peneX == .0f && containtInX) ||
		(std::abs(peneY) > 0.f && ((getVelocity().x() > 0.f && peneX > 0.f) || (getVelocity().x() < 0.f && peneX < 0.f)))) {
		if (other.IsFixe()) {
			this->_boxCollider.updatePosition(Vector::Vector2<float>(.0f, peneY));
			this->setVelocity(Vector::Vector2<float>(this->_velocity.x(), 0.f), true);
			//std::cout << "Resolve Y - Penex : " << peneX << " / Peney : " << peneY << " - (" << _velocity.x() << ", " << _velocity.y() << ")\n";
			return;
		}
	}
	else {
		//std::cout << "Error - Penex : " << peneX << " / Peney : " << peneY << " / containtInX :" << (containtInX ? "True" : "False") << " / containtInY : " << (containtInY ? "True" : "False") << "\n";
	}
#pragma endregion
}

void					RigidBody::udpdate(float deltaTime) {
	this->_boxCollider.updatePosition(_velocity * deltaTime);

	//std::cout << "UPDATE ----------- UPDATE ----------- UPDATE\n";

	_originalVelocity = _velocity;
	_originalPos = getPos();
	_fixeCollideWithMe.clear();
}

// Layer Methods
#pragma region // Layer's Method
Layer const				&RigidBody::getLayer() const {
	return this->_layer;
}

void					RigidBody::addAllLayer() {
	this->_layer.addAllLayer();
}

void					RigidBody::rmAllLayer() {
	this->_layer.rmAllLayer();
}

void					RigidBody::addLayer(Layer::LayerTypes lt) {
	this->_layer.addLayer(lt);
}

void					RigidBody::removeLayer(Layer::LayerTypes lt) {
	this->_layer.removeLayer(lt);
}

bool					RigidBody::isInLayer(Layer::LayerTypes lt) const {
	return this->_layer.isInLayer(lt);
}

bool					RigidBody::shareALayer(RigidBody const &other) const {
	return this->_layer.shareALayer(other._layer);
}
#pragma endregion
