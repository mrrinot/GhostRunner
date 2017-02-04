#include "Tools/TextInBox.hh"

TextInBox::TextInBox()
{
}

TextInBox::~TextInBox()
{
}

void  TextInBox::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  target.draw(_rectangle, states);
  target.draw(_text, states);
}

void  TextInBox::centerText()
{
  auto rectBox = _rectangle.getGlobalBounds();
  float width = rectBox.width;
  float height = rectBox.height;

  sf::FloatRect textRect = _text.getLocalBounds();

  _text.setOrigin((textRect.left + textRect.width) / 2.0f,
    (textRect.top + textRect.height) / 2.0f);

  _text.setPosition(rectBox.left + width / 2.0f, rectBox.top + height / 2.0f);
}

const sf::RectangleShape& TextInBox::getBox() const
{
  return _rectangle;
}

sf::RectangleShape& TextInBox::getBox()
{
  return _rectangle;
}

const sf::Text& TextInBox::getText() const
{
  return _text;
}

sf::Text& TextInBox::getText()
{
  return _text;
}

const sf::Font& TextInBox::getFont() const
{
  return _font;
}

sf::Font& TextInBox::getFont()
{
  return _font;
}