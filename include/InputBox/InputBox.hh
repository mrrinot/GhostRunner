#pragma once

#ifndef INPUT_BOX_HH_
#define INPUT_BOX_HH_

#include <SFML/Window/Event.hpp>
#include <SFML/Window/Window.hpp>
#include <map>
#include <functional>
#include <list>
#include "InputBox/IKeyboardTranslator.hh"
#include "InputBox/IControllerTranslator.hh"

/**
 *  @brief  Class meant to amalgamate different event to be treated
 *          as if they were the same.
 *          Allows to transparently use a controller or the keyboard.
 */
class InputBox
{
public:
  /**
   *  @brief  Typedef representing the predicate used to
   *          recognize an event by comparing it to another one.
   *
   *          Is automatically generated using operator== if
   *          an sf::Event is directly passed to @registerEvent.
   *          Otherwise, it has to be specified by hand.
   *          An example could be :
   *
   *          @code{.cpp}
   *            bool  testIfAltAndSpace(const sf::Event& eventToCompare)
   *            {
   *              return eventToCompare.key.alt && eventToCompare.key.code == sf::Keyboard::Space;
   *            }
   *          @endcode
   *
   *          This sample checks if space AND alt are pressed together.
   */
  using PredicateFilterType = std::function<bool(const sf::Event&)>;

public:
  /**
   *  @brief  Structure used to represent an amalgamated event.
   *          Is retrieved using @ref retrieveEvent and contains
   *          information relative to the concerned event.
   */
  struct EventData
  {
    /**
     *  @brief  The name of the amalgamated event as registered
     *          using @ref registerEvent.
     */
    std::string name;

    /**
     *  @brief  The event that triggered this amalgamation.
     */
    sf::Event   event;
  };

private:
  /**
   *  @brief  This internal class is used to store data about
   *          an event filter. An event filter is a combination of a
   *          @ref PredicateFilterType and an associated name.
   *
   *  TODO : Complete with argument data.
   */
  class EventFilter
  {
  public:
    /**
     *  @brief  Constructor initializing internal values.
     *
     *  @param[in]  name      The event represented by this EventFilter.
     *                        This name is used to represent an amalgamation
     *                        of (possibly) multiple sf::Event.
     *  @param[in]  predicate The predicate is used to filter the sf::Event.
     *                        See @ref PredicateFilterType for more informations.
     */
    EventFilter(const std::string& name, PredicateFilterType predicate);

    /**
     *  @brief  Simple destructor.
     */
    ~EventFilter();

    /**
     *  @brief  Uses the internal @ref PredicateFilterType to check whether
     *          @a eventToCheck matches or not.
     *
     *  @param[in]  eventToCheck  The event to test.
     *
     *  @return True if the event matches the expected format.
     *          False otherwise.
     */
    bool  check(const sf::Event& eventToCheck) const;

    /**
     *  @brief  Allows the name of the amalgamated event to be retrieved.
     *
     *  @return The name of the amalgamated event.
     */
    std::string getName() const;

  private:
    /**
     *  @brief  The name/identifier for the amalgamated event.
     */
    const std::string   _name;

    /**
     *  @brief  The predicate used to filter the events.
     */
    PredicateFilterType _predicate;
  };

public:
  /**
   *  @brief  Default constructor, does nothing in particular.
   *
   *  @param[in]  window  The window from which events will be retrieved.
   */
  InputBox(sf::Window& window);

  /**
   *  @brief  Default destructor, does nothing in particular.
   */
  ~InputBox();

  /**
   *  @brief  Function used to register an event to filter.
   *          This overload is based on an exact match : the InputBox
   *          will only match if @a eventToTest is strictly equal to @a eventToFilter.
   *          @a eventToFilter.type is used to filter the event.
   *
   *  @param[in]  name          The name used to represent the amalgamated events.
   *  @param[in]  eventToFilter The exact event required to match against.
   */
  void  registerEvent(const std::string& name,
    sf::Event eventToFilter);

  /**
   *  @brief  Function used to register a specific predicate to test an event.
   *
   *  @param[in]  name      The name used to represent the amalgamated events.
   *  @param[in]  eventType The event type, used to quickly filter events.
   *  @param[in]  predicate The predicate used to test events.
   *
   *  @see  @ref PredicateFilterType for more info about the predicate.
   */
  void  registerEvent(const std::string& name,
    sf::Event::EventType eventType,
    PredicateFilterType predicate);

  /**
   *  @brief  Function used to retrieve amalgamated events.
   *          Will call sf::Window::pollEvent and translate
   *          events if necessary.
   *
   *  @param[out] dataToFill  The amalgamated event data.
   *                          Will be set by the function if
   *                          a registered event was fired.
   *
   *  @return True if @a dataToFill has been set.
   *          False if no registered event was fired.
   */
  bool  retrieveEvent(EventData& dataToFill);

  /**
   *  @brief  Function used to register a KeyboardTranslator to be used by
   *          the InputBox. The translator will be added at the end of
   *          the internal translators storage.
   *
   *  @param[in]  translatorToRegister  The translator to register.
   */
  void  registerTranslator(IKeyboardTranslator* translatorToRegister);

  /**
   *  @brief  Function used to register a IControllerTranslator to be used by
   *          the InputBox. The translator will be added at the end of
   *          the internal translators storage.
   *
   *  @param[in]  translatorToRegister  The translator to register.
   */
  void  registerTranslator(IControllerTranslator* translatorToRegister);

private:
  /**
   *  @brief  Translates an event using the internal translators.
   *
   *  @param[in]  eventToTranslate  The event to translate.
   *
   *  @return The event translated.
   */
  sf::Event translate(const sf::Event& eventToTranslate) const;

private:
  /**
   *  @brief  List of keyboard translators. Will be used to translate
   *          keyboard events. Order matters.
   */
  std::list<IKeyboardTranslator*>   _keyboardTranslators;

  /**
   *  @brief  List of controller translators. Will be used to translate
   *          controller events. Order matters.
   */
  std::list<IControllerTranslator*> _controllerTranslators;

  /**
   *  @brief  Map used to store all registered filters.
   *          The key is the sf::Event::EventType to filter
   *          quickly some events which will never match.
   *          The value is a std::list of EventFilter used
   *          to store each registered predicate.
   */
  std::map<sf::Event::EventType, std::list<EventFilter>> _registeredEvents;

  /**
   *  @brief  The sf::Window used to retrieve events.
   */
  sf::Window&   _window;
};

#endif // INPUT_BOX_HH_