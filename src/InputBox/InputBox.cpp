#include "InputBox/InputBox.hh"
#include "InputBox/SFMLCustomStuff.hh"

InputBox::EventFilter::EventFilter(const std::string& name, PredicateFilterType predicate)
  : _name(name)
  , _predicate(predicate)
{
}

InputBox::EventFilter::~EventFilter()
{
}

bool  InputBox::EventFilter::check(const sf::Event& eventToCheck) const
{
  return _predicate(eventToCheck);
}

std::string  InputBox::EventFilter::getName() const
{
  return _name;
}

InputBox::InputBox(sf::Window& window)
  : _window(window)
{
}

InputBox::~InputBox()
{
}

void  InputBox::registerEvent(const std::string& name,
  sf::Event eventToFilter)
{
  _registeredEvents[eventToFilter.type].push_back(EventFilter(name,
    [eventToFilter](const sf::Event& param) {
    return param == eventToFilter;
  }));
}

void  InputBox::registerEvent(const std::string& name,
  sf::Event::EventType eventType,
  PredicateFilterType predicate)
{
  _registeredEvents[eventType].push_back(EventFilter(name, predicate));
}

void  InputBox::registerTranslator(IKeyboardTranslator* translatorToRegister)
{
  _keyboardTranslators.push_back(translatorToRegister);
}

void  InputBox::registerTranslator(IControllerTranslator* translatorToRegister)
{
  _controllerTranslators.push_back(translatorToRegister);
}

sf::Event InputBox::translate(const sf::Event& eventToTranslate) const
{
  sf::Event result = eventToTranslate;

  if (result.type == sf::Event::EventType::KeyPressed ||
    result.type == sf::Event::EventType::KeyReleased)
  {
    for (IKeyboardTranslator* translator : _keyboardTranslators)
      if (translator->needTranslation(result))
        result = translator->translate(result);
  }
  else if (result.type == sf::Event::EventType::JoystickButtonPressed ||
    result.type == sf::Event::EventType::JoystickButtonReleased ||
    result.type == sf::Event::EventType::JoystickMoved)
  {
    for (IControllerTranslator* translator : _controllerTranslators)
      if (translator->needTranslation(result))
        result = translator->translate(result);
  }

  return result;
}

bool  InputBox::retrieveEvent(EventData& dataToFill)
{
  sf::Event event;

  while (_window.pollEvent(event))
  {
    if (!_registeredEvents.count(event.type))
      continue;

    event = translate(event);

    std::list<EventFilter>& filters = _registeredEvents.at(event.type);

    for (EventFilter& filter : filters)
      if (filter.check(event))
      {
        dataToFill.name = filter.getName();
        dataToFill.event = event;
        return true;
      }
  }

  return false;
}
