#ifndef WinOverlay_HH_
#define WinOverlay_HH_

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "Animation.hh";

class	WinOverlay : public sf::Drawable
{
private:
	sf::RectangleShape  _rectangle;
	sf::Font			_font;
	sf::Text			_text;
	Animation			*_screen;

public:
	WinOverlay();
	~WinOverlay();

	void	setWinner(std::string &back);
	void	setBackMenu(Animation *back);
	void	draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void	center(float width, float height);
};

#endif // WinOverlay_HH_
