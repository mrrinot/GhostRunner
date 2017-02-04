#include "InputBox/SFMLCustomStuff.hh"

namespace sf
{

  bool  operator==(const Event& lhs, const Event& rhs)
  {
    if (lhs.type != rhs.type)
      return false;

    if (lhs.type == Event::EventType::Resized)
      return lhs.size == rhs.size;

    if (lhs.type == Event::EventType::KeyPressed
      || lhs.type == Event::EventType::KeyReleased)
      return lhs.key == rhs.key;

    if (lhs.type == Event::EventType::TextEntered)
      return lhs.text == rhs.text;

    if (lhs.type == Event::MouseMoved)
      return lhs.mouseMove == rhs.mouseMove;

    if (lhs.type == Event::EventType::MouseButtonPressed
      || lhs.type == Event::EventType::MouseButtonReleased)
      return lhs.mouseButton == rhs.mouseButton;

    if (lhs.type == Event::EventType::MouseWheelMoved)
      return lhs.mouseWheel == rhs.mouseWheel;

    if (lhs.type == Event::EventType::JoystickConnected
      || lhs.type == Event::EventType::JoystickDisconnected)
      return lhs.joystickConnect == rhs.joystickConnect;

    if (lhs.type == Event::EventType::JoystickMoved)
      return lhs.joystickMove == rhs.joystickMove;

    if (lhs.type == Event::EventType::JoystickButtonPressed
      || lhs.type == Event::EventType::JoystickButtonReleased)
      return lhs.joystickButton == rhs.joystickButton;

    return true;
  }

  bool  operator==(const Event::SizeEvent& lhs, const Event::SizeEvent& rhs)
  {
    return lhs.width == rhs.width && lhs.height == rhs.height;
  }

  bool  operator==(const Event::KeyEvent& lhs, const Event::KeyEvent& rhs)
  {
    bool result = true;

    result = result && lhs.code == rhs.code;
    result = result && lhs.alt == rhs.alt;
    result = result && lhs.control == rhs.control;
    result = result && lhs.shift == rhs.shift;
    result = result && lhs.system == rhs.system;

    return result;
  }

  bool  operator==(const Event::TextEvent& lhs, const Event::TextEvent& rhs)
  {
    return lhs.unicode == rhs.unicode;
  }

  bool  operator==(const Event::MouseMoveEvent& lhs, const Event::MouseMoveEvent& rhs)
  {
    return lhs.x == rhs.x && lhs.y == rhs.y;
  }

  bool  operator==(const Event::MouseButtonEvent& lhs, const Event::MouseButtonEvent& rhs)
  {
    return lhs.x == rhs.x && lhs.y == rhs.y && lhs.button == rhs.button;
  }

  bool  operator==(const Event::MouseWheelEvent& lhs, const Event::MouseWheelEvent& rhs)
  {
    return lhs.x == rhs.x && lhs.y == rhs.y && lhs.delta == rhs.delta;
  }

  bool  operator==(const Event::JoystickConnectEvent& lhs, const Event::JoystickConnectEvent& rhs)
  {
    return lhs.joystickId == rhs.joystickId;
  }

  bool  operator==(const Event::JoystickMoveEvent& lhs, const Event::JoystickMoveEvent& rhs)
  {
    return lhs.joystickId == rhs.joystickId && lhs.axis == rhs.axis && lhs.position == rhs.position;
  }

  bool  operator==(const Event::JoystickButtonEvent& lhs, const Event::JoystickButtonEvent& rhs)
  {
    return lhs.joystickId == rhs.joystickId && lhs.button == rhs.button;
  }

} // namespace sf

namespace EventMaker
{

  sf::Event make(sf::Event::EventType type)
  {
    sf::Event eventToReturn;

    eventToReturn.type = type;
    return eventToReturn;
  }

  sf::Event make(sf::Event::EventType type, const sf::Event::SizeEvent&             size)
  {
    sf::Event eventToReturn;

    eventToReturn.type = type;
    eventToReturn.size = size;
    return eventToReturn;
  }

  sf::Event make(sf::Event::EventType type, const sf::Event::KeyEvent&              key)
  {
    sf::Event eventToReturn;

    eventToReturn.type = type;
    eventToReturn.key = key;
    return eventToReturn;
  }

  sf::Event make(sf::Event::EventType type, const sf::Event::TextEvent&             text)
  {
    sf::Event eventToReturn;

    eventToReturn.type = type;
    eventToReturn.text = text;
    return eventToReturn;
  }

  sf::Event make(sf::Event::EventType type, const sf::Event::MouseMoveEvent&        mouseMove)
  {
    sf::Event eventToReturn;

    eventToReturn.type = type;
    eventToReturn.mouseMove = mouseMove;
    return eventToReturn;
  }

  sf::Event make(sf::Event::EventType type, const sf::Event::MouseButtonEvent&      mouseButton)
  {
    sf::Event eventToReturn;

    eventToReturn.type = type;
    eventToReturn.mouseButton = mouseButton;
    return eventToReturn;
  }

  sf::Event make(sf::Event::EventType type, const sf::Event::MouseWheelEvent&       mouseWheel)
  {
    sf::Event eventToReturn;

    eventToReturn.type = type;
    eventToReturn.mouseWheel = mouseWheel;
    return eventToReturn;
  }

  sf::Event make(sf::Event::EventType type, const sf::Event::JoystickConnectEvent&  joystickConnect)
  {
    sf::Event eventToReturn;

    eventToReturn.type = type;
    eventToReturn.joystickConnect = joystickConnect;
    return eventToReturn;
  }

  sf::Event make(sf::Event::EventType type, const sf::Event::JoystickMoveEvent&     joystickMove)
  {
    sf::Event eventToReturn;

    eventToReturn.type = type;
    eventToReturn.joystickMove = joystickMove;
    return eventToReturn;
  }

  sf::Event make(sf::Event::EventType type, const sf::Event::JoystickButtonEvent&   joystickButton)
  {
    sf::Event eventToReturn;

    eventToReturn.type = type;
    eventToReturn.joystickButton = joystickButton;
    return eventToReturn;
  }


  sf::Event::SizeEvent            makeSize(unsigned int width, unsigned int height)
  {
    sf::Event::SizeEvent  eventToReturn;

    eventToReturn.width = width;
    eventToReturn.height = height;
    return eventToReturn;
  }

  sf::Event::KeyEvent             makeKey(sf::Keyboard::Key code, bool alt, bool control, bool shift, bool system)
  {
    sf::Event::KeyEvent eventToReturn;

    eventToReturn.code = code;
    eventToReturn.alt = alt;
    eventToReturn.control = control;
    eventToReturn.shift = shift;
    eventToReturn.system = system;
    return eventToReturn;
  }

  sf::Event::TextEvent            makeText(sf::Uint32 unicode)
  {
    sf::Event::TextEvent  eventToReturn;

    eventToReturn.unicode = unicode;
    return eventToReturn;
  }

  sf::Event::MouseMoveEvent       makeMouseMove(int x, int y)
  {
    sf::Event::MouseMoveEvent eventToReturn;

    eventToReturn.x = x;
    eventToReturn.y = y;
    return eventToReturn;
  }

  sf::Event::MouseButtonEvent     makeMouseButton(sf::Mouse::Button button, int x, int y)
  {
    sf::Event::MouseButtonEvent eventToReturn;

    eventToReturn.button = button;
    eventToReturn.x = x;
    eventToReturn.y = y;
    return eventToReturn;
  }

  sf::Event::MouseWheelEvent      makeMouseWheel(int delta, int x, int y)
  {
    sf::Event::MouseWheelEvent  eventToReturn;

    eventToReturn.delta = delta;
    eventToReturn.x = x;
    eventToReturn.y = y;
    return eventToReturn;
  }

  sf::Event::JoystickConnectEvent makeJoystickConnect(unsigned int joystickId)
  {
    sf::Event::JoystickConnectEvent eventToReturn;

    eventToReturn.joystickId = joystickId;
    return eventToReturn;
  }

  sf::Event::JoystickMoveEvent    makeJoystickMove(unsigned int joystickId, sf::Joystick::Axis axis, float position)
  {
    sf::Event::JoystickMoveEvent  eventToReturn;

    eventToReturn.joystickId = joystickId;
    eventToReturn.axis = axis;
    eventToReturn.position = position;
    return eventToReturn;
  }

  sf::Event::JoystickButtonEvent  makeJoystickButton(unsigned int joystickId, unsigned int button)
  {
    sf::Event::JoystickButtonEvent  eventToReturn;

    eventToReturn.joystickId = joystickId;
    eventToReturn.button = button;
    return eventToReturn;
  }

} // namespace EventMaker