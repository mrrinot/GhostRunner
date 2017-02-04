#pragma once
#include "GameObject.hh"
#include "AdditionalDrawableBar.hh"
#include "IAction.hh"
#include "GlobalInfos.hh"
#include "HeroController.hh"
#include "GhostController.hh"


namespace GE
{
	class Sprite;
}

class IAction;

class Player :
	public GameObject
{
private:
	Animation*					_player;
	Animation*					_ghost;
	AdditionalDrawableBar		*_steelLifeBar;
    std::map<e_Action, IAction *>  _actionMap;
	std::map<e_Action, AdditionalDrawableBar *> _actionsCooldown;

    IAction                     *_currentAction;
	float						_takeOver;
    bool                        _isAggro;
    bool                        _isGoingRight;
    bool                        _isAnimAction;

	int							_life;
	float						_damageLess;

	int							_deviceID;
	std::vector<std::string>	_button;

	HeroController				_heroController;
	GhostController				_ghostController;

	static const float			TAKEOVER_TIME;
	static const float			TAKEOVER_SPEED_DIVIDOR;
	static const float			TAKEOVER_DECLINE_COEF;
	static const float			GHOST_MAX_SPEED;
	static const float			PLAYER_MAX_SPEED;

public:
	Player(const std::string &name, const Vector::Vector2<float>& upLeftCorner, const Vector::Vector2<float>& size);
	~Player();

	virtual void update(float deltatime);

	virtual void OnCollisionEnter(GameObject *other);
	virtual void OnCollisionStay(GameObject *other);
	virtual void OnCollisionExit(GameObject *other);

	void		resetSpeedOnDeath();
	void		repulseGhost();

	Player*		setSprites(Animation* Player, Animation* Ghost);
	Player*		setDevice(int);
	Player*		setLife(int);
	Player*		setInvulnerability(float);
    Player*     setAggro(bool aggro);

	void		updateLife(int);
    bool        isAggro() const;
	bool		isAlive() const;
    bool        facingRight() const;
    void        setAnimAction(bool isAnimAction);

	int			getDeviceID() const;
	int			getLife() const;
};

