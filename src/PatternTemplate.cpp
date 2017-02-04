#include "PatternTemplate.hh"
#include <iostream>
#include "Logger.hh"

PatternTemplate::PatternTemplate(int id, const std::string &pattern, float diff, int rarity)
: _id(id), _pattern(pattern), _difficulty(diff), _rarity(rarity)
{
}

PatternTemplate::~PatternTemplate()
{
}

const std::string &PatternTemplate::getPatternTemplate() const
{
  return _pattern;
}

unsigned int PatternTemplate::getRarity() const
{
  return _rarity;
}

float PatternTemplate::getDifficulty() const
{
  return _difficulty;
}

const Vector::Vector2<int> &PatternTemplate::getPos() const
{
  return _pos;
}

int PatternTemplate::getId() const
{
  return _id;
}

void PatternTemplate::setPos(const Vector::Vector2<int> &pos)
{
  _pos = pos;
}

void  PatternTemplate::addAdjacentPatternTemplate(PatternTemplate *temp)
{
  _adjacentPossiblePatternTemplates.push_back(temp);
}


void  PatternTemplate::addAdjacentPatternTemplateId(unsigned int id)
{
  _adjacentPossiblePatternTemplatesId.push_back(id);
}

const std::list<unsigned int> &PatternTemplate::getPatternsId()
{
  return _adjacentPossiblePatternTemplatesId;
}

int PatternTemplate::getRandomPattern(float difficulty) const
{
  int totalPattern = 0;

  //std::cout << pos << " ON " << _id << std::endl;
  //std::cout << _adjacentPossiblePatternTemplates.count(pos) << std::endl;
  if (_adjacentPossiblePatternTemplatesId.empty() == true)
  {
    //std::cout << "EMPTY" << std::endl;
    return -1;
  }
  for (auto it = _adjacentPossiblePatternTemplates.begin(); it != _adjacentPossiblePatternTemplates.end(); ++it)
  {
    //std::cout << "DIFF = " << (*it)->getDifficulty() << std::endl;
    if ((*it)->getDifficulty() <= difficulty)
    {
      //std::cout << "ADD RARITY : " << (*it)->getRarity() << " ID = " << (*it)->getId() << std::endl;
      totalPattern += (*it)->getRarity();
    }
  }
  if (totalPattern > 0)
  {
    //std::cout << "TOTAL = " << totalPattern << std::endl;
    int randomPatternnbr = rand() % totalPattern;
    //std::cout << "RANDOM = " << randomPatternnbr << std::endl;
    auto it = _adjacentPossiblePatternTemplates.begin();
    while (it != _adjacentPossiblePatternTemplates.end() && randomPatternnbr > 0)
    {
      //std::cout << "random still = " << randomPatternnbr << std::endl;
      if ((*it)->getDifficulty() <= difficulty)
        randomPatternnbr -= (*it)->getRarity();
      if (randomPatternnbr > 0)
        ++it;
    }
    //std::cout << "ID CHOSEN = " << (*it)->getId() << std::endl;
    return (*it)->getId();
  }
  else
    return -1;
}

PatternTemplate *PatternTemplate::clone() const
{
  return new PatternTemplate(*this);
}
