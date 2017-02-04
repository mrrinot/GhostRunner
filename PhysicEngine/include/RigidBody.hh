#pragma once

#include "BoxCollider.hh"
#include "Layer.hh"
#include <vector>

class						RigidBody
{
private:
	Vector::Vector2<float>	_velocity;
	float					_weight;
	float					_elasticity;

	Layer					_layer;
	Colliders::BoxCollider	_boxCollider;

	float					_MaxSpeed;
	float					_MaxSpeedSquare;
	bool					_isFixe;
	bool					_isResolveCollide;

	std::vector<Colliders::BoxCollider>	_fixeCollideWithMe;
	Vector::Vector2<float>				_originalPos;
	Vector::Vector2<float>				_originalVelocity;

public:
	RigidBody(const Vector::Vector2<float>& pos, const Vector::Vector2<float>& size, float weight, float MaxSpeed, bool ResolveCollide = true, bool isFixe = false);
	RigidBody(const Vector::Vector2<float>& pos, const Vector::Vector2<float>& size, bool ResolveCollide = true, bool isFixe = true);
	RigidBody(const Colliders::BoxCollider& box, bool ResolveCollide = true, bool isFixe = true);
	~RigidBody();

	static const float		_epsilon; // value under which velocity is considered as 0

	Vector::Vector2<float>	getVelocity() const;
	float const				getWeight() const;
	float const				getMaxSpeed() const;
	bool					IsFixe() const;
	bool					IsResolveCollide() const;
	float					getWidth() const;
	float					getLenght() const;
	Vector::Vector2<float> const	&getPos() const; // Up left Corner

	Colliders::BoxCollider &getCollider();

	void					setVelocity(const Vector::Vector2<float>& velocity, bool force = false);
	void					addVelocity(const Vector::Vector2<float>& velocity);
	void					subVelocity(const Vector::Vector2<float>& velocity);
	void					alterVelocity(const Vector::Vector2<float>& velocityMultiplicator);

	void					setWeight(float weight);
	void					setMaxSpeed(float MaxSpeed);
	void					setFixe(bool isfixe);
	void					setResolveColide(bool isResolveCollide);
	void                    setColliderSize(const Vector::Vector2<float> &size);
	void					setCollider(const Colliders::BoxCollider &box);

	bool					isCollideWith(const RigidBody &other) const;
	void					resolveCollideWith(RigidBody &other, bool isTmpRGBD = false);
	void					udpdate(float delaTime);

	// Layer
	Layer const				&getLayer() const;
	void					addAllLayer();
	void					rmAllLayer();
	void					addLayer(Layer::LayerTypes lt);
	void					removeLayer(Layer::LayerTypes lt);
	bool					isInLayer(Layer::LayerTypes lt) const;
	bool					shareALayer(RigidBody const &other) const;
};

/*
class						RigidBody
{
private:
	Vector::Vector2<float>	_force;
	Vector::Vector2<float>	_velocity;

	float					_weight;
	float					_invWeight;

	float					_elasticity;

	bool					_useGravity;

public:
	RigidBody(float weight = 0, float elasticity = 0, bool _useGravity = true);
	~RigidBody();

	Vector::Vector2<float>	getVelocity() const;

	float const				getElasticity() const;
	float const				getWeight() const;
	float const				getInvWeight() const;
	bool const				getUseGravity() const;
	Vector::Vector2<float>	getForce() const;

	void					setElasticity(float e);
	void					setWeight(float w);
	void					setUseGravity(bool u);
	void					setForce(Vector::Vector2<float> force);

	void					applyImpulse(Vector::Vector2<float> impulse);
	void					applyForce(Vector::Vector2<float> force);

	void					setVelocity(const Vector::Vector2<float>& v);
	void					updateVelocity(float deltatime);
	Vector::Vector2<float>	getDeltaPosition(float deltatime) const;

	void					resetForces();

	static const float		_epsilon; // value under which velocity is considered as 0
};
*/
