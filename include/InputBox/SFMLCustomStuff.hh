#pragma once

#ifndef SFML_CUSTOM_STUFF_HH_
#define SFML_CUSTOM_STUFF_HH_

#include <SFML/Window/Event.hpp>

namespace sf
{

  bool  operator==(const Event& lhs, const Event& rhs);
  bool  operator==(const Event::SizeEvent& lhs, const Event::SizeEvent& rhs);
  bool  operator==(const Event::KeyEvent& lhs, const Event::KeyEvent& rhs);
  bool  operator==(const Event::TextEvent& lhs, const Event::TextEvent& rhs);
  bool  operator==(const Event::MouseMoveEvent& lhs, const Event::MouseMoveEvent& rhs);
  bool  operator==(const Event::MouseButtonEvent& lhs, const Event::MouseButtonEvent& rhs);
  bool  operator==(const Event::MouseWheelEvent& lhs, const Event::MouseWheelEvent& rhs);
  bool  operator==(const Event::JoystickConnectEvent& lhs, const Event::JoystickConnectEvent& rhs);
  bool  operator==(const Event::JoystickMoveEvent& lhs, const Event::JoystickMoveEvent& rhs);
  bool  operator==(const Event::JoystickButtonEvent& lhs, const Event::JoystickButtonEvent& rhs);

} // namespace sf

namespace EventMaker
{
  
  sf::Event make(sf::Event::EventType type);
  sf::Event make(sf::Event::EventType type, const sf::Event::SizeEvent&             size);
  sf::Event make(sf::Event::EventType type, const sf::Event::KeyEvent&              key);
  sf::Event make(sf::Event::EventType type, const sf::Event::TextEvent&             text);
  sf::Event make(sf::Event::EventType type, const sf::Event::MouseMoveEvent&        mouseMove);
  sf::Event make(sf::Event::EventType type, const sf::Event::MouseButtonEvent&      mouseButton);
  sf::Event make(sf::Event::EventType type, const sf::Event::MouseWheelEvent&       mouseWheel);
  sf::Event make(sf::Event::EventType type, const sf::Event::JoystickConnectEvent&  joystickConnect);
  sf::Event make(sf::Event::EventType type, const sf::Event::JoystickMoveEvent&     joystickMove);
  sf::Event make(sf::Event::EventType type, const sf::Event::JoystickButtonEvent&   joystickButton);

  sf::Event::SizeEvent            makeSize(unsigned int width, unsigned int height);
  sf::Event::KeyEvent             makeKey(sf::Keyboard::Key code, bool alt, bool control, bool shift, bool system);
  sf::Event::TextEvent            makeText(sf::Uint32 unicode);
  sf::Event::MouseMoveEvent       makeMouseMove(int x, int y);
  sf::Event::MouseButtonEvent     makeMouseButton(sf::Mouse::Button button, int x, int y);
  sf::Event::MouseWheelEvent      makeMouseWheel(int delta, int x, int y);
  sf::Event::JoystickConnectEvent makeJoystickConnect(unsigned int joystickId);
  sf::Event::JoystickMoveEvent    makeJoystickMove(unsigned int joystickId, sf::Joystick::Axis axis, float position);
  sf::Event::JoystickButtonEvent  makeJoystickButton(unsigned int joystickId, unsigned int button);

} // namespace EventMaker

#endif // SFML_CUSTOM_STUFF_HH_