#pragma once

#ifndef ICONTROLLER_TRANSLATOR_HH_
#define ICONTROLLER_TRANSLATOR_HH_

#include <SFML/Window/Event.hpp>

/**
 *  @brief  Base class for all controller translators.
 *          A translator is a middleware used to transform
 *          an event by changing some of its internal properties.
 *
 *          It provides a way to alter an event without the need
 *          for the user to hard code some stuff.
 *
 *          A controller translator can be used, for example,
 *          to ensure the consistency between different controller.
 *          Let's say the main project is based on Xbox 360's input
 *          style, the button 1 will be 'A' on the controller but
 *          can be somewhere else on, let's say, a PS3 controller.
 *          By providing a translation from PS3 to Xbox 360, the
 *          developper can consider all PS3 controllers as if it
 *          was an Xbox 360 controller.
 */
class IControllerTranslator
{
public:
  /**
   *  @brief  Typedef representing an event.
   */
  using Event = sf::Event;

public:
  /**
   *  @brief  Virtual destructor not doing anything.
   */
  virtual ~IControllerTranslator() {}

  /**
   *  @brief  Function used to translate an event.
   *
   *  @param[in]  eventToTranslate The event to translate.
   *
   *  @return The event properly translated.
   */
  virtual Event   translate(const Event& eventToTranslate) = 0;

  /**
   *  @brief  Function used to quickly skip a Translator if the event doesn't
   *          match its requirements.
   *
   *          Defaults to "return true;" but can be overriden at will.
   *
   *          For example, it can be used to ensure that the joystickId is 0
   *          because the first player is the only one using a PS3 controller.
   *
   *  @param[in]  eventToTest The event that the translator needs to check.
   *
   *  @return True if this event must be translated.
   *          False if it must be skipped.
   */
  virtual bool      needTranslation(const Event& eventToTest)
  {
    return true;
  }
};

#endif // ICONTROLLER_TRANSLATOR_HH_