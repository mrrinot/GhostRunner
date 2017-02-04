#pragma once

#include <map>
#include "RigidBody.hh"
#include "AEnvironmentalEffect.hh"
#include "Animator.hh"
#include "Vector2.hh"
#include "IAdditionalDrawableInfo.hh"
#include "AdditionalDrawableHitboxOutline.hh"

typedef enum  e_CollisionType
{
	ENTER,
	STAY,
	STAYANDCHECKED
}				CollisionType;

class GameObject
{
	friend class Scene;

protected:
	static unsigned int						_idCounter;

	unsigned int							_id;
	const std::string						_name;
	Animator								_animator;
	RigidBody								_RigidBody;
    AdditionalDrawableHitboxOutline         *_hitboxOutline;

	std::map<unsigned int, std::pair<CollisionType, GameObject *>>  _collisionsWithMe;
	bool									_toDestroy; // ?

	std::vector<IAdditionalDrawableInfo *>	_additionalInfo;

public:
	GameObject(const std::string &name, const Vector::Vector2<float>& upLeftCorner, const Vector::Vector2<float>& size, float weight, float MaxSpeed, bool ResolveCollide = true, bool isFixe = false);
	GameObject(const std::string &name, const Vector::Vector2<float>& upLeftCorner, const Vector::Vector2<float>& size, bool ResolveCollide = true, bool isFixe = true);
	~GameObject();

	unsigned int const						getId() const;
	std::string const &						getName() const;
	float									getWidth() const;
	float									getLenght() const;

	Vector::Vector2<float> const		    getPosition() const;
	void									setPosition(const Vector::Vector2<float>& pos);
    void                                    setColliderSize(const Vector::Vector2<float> &size);
	void									updatePosition(const Vector::Vector2<float>& incr);

	RigidBody								&getRigidBody();
	Animator                                &getAnimator();
	Animation*								getGraphicComponent();
	Animation*								getGraphicComponent(const Vector::Vector2<float>& incr);

    bool                                    changeAnimation(const std::string &name, bool isRet);
	GameObject*								addLayer(Layer::LayerTypes);
	GameObject*								removeLayer(Layer::LayerTypes);
    GameObject*                             addAnimation(const std::string &name, Animation *anim);

	bool									hasGraphicComponent() const;
	bool									isInLayer(Layer::LayerTypes l);

	bool									CheckCollisionWith(GameObject *other);
	void									ResolveCollisionWith(GameObject *other);

	virtual void							OnCollisionEnter(GameObject *other);
	virtual void							OnCollisionStay(GameObject *other);
	virtual void							OnCollisionExit(GameObject *other);
	virtual void							update(float deltatime);

	bool const								getToDestroy() const;
	void									setToDestroy(bool b);
	
	bool									hasAdditionalInfos() const;
	std::vector<IAdditionalDrawableInfo *>	&getAdditionalInfos();
	void									addAdditionalInfo(IAdditionalDrawableInfo *info);
    void                                    switchHitbox(bool switched);

	const std::map<unsigned int, std::pair<CollisionType, GameObject *>> &getCollisionsWithMe() const;
};
