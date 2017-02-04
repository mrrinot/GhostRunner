#pragma once

#ifndef IKEYBOARD_TRANSLATOR_HH_
#define IKEYBOARD_TRANSLATOR_HH_

#include <SFML/Window/Event.hpp>

/**
 *  @brief  Base class for all keyboard translators.
 *          Is meant to translate keys from one layout to another.
 *          For example, it can translate "W" from a QWERTY and
 *          change it to "Z" from an AZERTY so that the user
 *          only need to care about it's preferred mapping.
 */
class IKeyboardTranslator
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
  virtual ~IKeyboardTranslator()
  {
  }

  /**
   *  @brief  Function used to translate an event.
   *
   *  @param[in]  eventToTranslate The event to translate.
   *
   *  @return The properly translated event.
   */
  virtual Event  translate(const Event& eventToTranslate) = 0;

  /**
   *  @brief  Function used to quickly skip a Translator if the event doesn't
   *          match its requirements.
   *
   *          Defaults to "return true;" but can be overriden at will.
   *
   *  @param[in]  eventToTest The event that the translator needs to check.
   *
   *  @return True if this event must be translated.
   *          False if it must be skipped.
   *
   *  @note   This function has mainly be added for @ref IControllerTranslator
   *          but has also been added here "just in case".
   */
  virtual bool      needTranslation(const Event& eventToTest)
  {
    return true;
  }
};

#endif // IKEYBOARD_TRANSLATOR_HH_