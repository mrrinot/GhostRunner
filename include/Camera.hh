#pragma once
#include "GameObject.hh"

class Camera
{
protected:
	std::vector<GameObject *>	_FollowingList;

	Vector::Vector2<float>		_pos;
	Vector::Vector2<float>		_size;

	bool						_allowBackward;
	Animation					*_background;

public:
	Camera(const Vector::Vector2<float>& position, const Vector::Vector2<float>& size, bool allowBackward = true, Animation *back = nullptr);
	~Camera();

	virtual void				update(float deltatime);
	void						addObjectToFollow(GameObject *);
	void						setPos(const Vector::Vector2<float>& position);
	void						resetObjectToFollow();

	const Vector::Vector2<float>		&getPos() const;
	const Vector::Vector2<float>		&getSize() const;

	void								drawBackground(sf::RenderWindow& window);

	std::vector<GameObject *>	getGoOnScreen();
	std::vector<GameObject *>	getGoOnScreen(std::vector<GameObject *>& golist);
};

