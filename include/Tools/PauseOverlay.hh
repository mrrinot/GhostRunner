#ifndef PauseOverlay_HH_
#define PauseOverlay_HH_

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "Animation.hh";

class	PauseOverlay : public sf::Drawable
{
private:
	sf::RectangleShape  _rectangle;
	Animation			*_screen;

public:
	PauseOverlay();
	~PauseOverlay();

	void	setBackMenu(Animation *back);
	void	draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void	center(float width, float height);
};

#endif // PauseOverlay_HH_
