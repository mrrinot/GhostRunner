#ifndef TEXTINBOX_HH_
#define TEXTINBOX_HH_

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

class	TextInBox : public sf::Drawable
{
public:
  TextInBox();
  ~TextInBox();

public:
  void  draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
  const sf::RectangleShape& getBox() const;
  sf::RectangleShape& getBox();

  const sf::Text& getText() const;
  sf::Text& getText();

  const sf::Font& getFont() const;
  sf::Font& getFont();

  void  centerText();

private:
  sf::RectangleShape  _rectangle;
  sf::Text  _text;
  sf::Font  _font;
};

#endif // TEXTINBOX_HH_
