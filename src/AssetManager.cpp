#include <vector>
#include "AssetManager.hh"
#include "Tools/WINFSReader.hh"
#include "Logger.hh"
#include <SFML/Graphics/Texture.hpp>

const std::string AssetManager::ANIM_PATH = "./Resources/Descriptors";
const std::string AssetManager::ROOT_PATH = "./Resources";
const std::string AssetManager::PATTERN_PATH = "./Resources/Level_Patterns";

AssetManager::AssetManager()
{

}

AssetManager::~AssetManager()
{
  for (auto it = _animMap.begin(); it != _animMap.end(); ++it)
  {
    delete it->second;
  }
  for (auto it = _patternMap.begin(); it != _patternMap.end(); ++it)
  {
    delete it->second;
  }
}

void AssetManager::makeSprite()
{
  Animation *anim;
  sf::Sprite *gc;
  std::string posS;
  unsigned int id;
  sf::Vector2<int> pos;
  sf::Vector2<int> size;

  posS = _parser.get("Positions", "0", "");

  pos.x = std::atoi(posS.substr(0, posS.find(",")).c_str());
  pos.y = std::atoi(posS.substr(posS.find(",") + 1, posS.find(":")).c_str());

  size.x = std::atoi(posS.substr(posS.find(":") + 1, posS.find("/")).c_str());
  size.y = std::atoi(posS.substr(posS.find("/") + 1).c_str());

  id = std::atoi(_parser.get("General", "ID", "").c_str());

  std::string texturePath = _parser.get("General", "Path", "");

  sf::Texture& tex = _textureMap[texturePath];
  gc = new sf::Sprite(tex, sf::IntRect(pos, size));

  tex.loadFromFile(texturePath);

  anim = new Animation(ONCE, 1);
  anim->addSprite(gc);
  // LogInfo() << "ADD SPRITE, ID = " << id << " path = " << texturePath;
  _animMap[id] = anim;
}

void AssetManager::makeAnimation()
{
  Animation *anim;
  std::vector<sf::Sprite *> sprites;
  std::string posS;
  unsigned int id;
  sf::Vector2<int> pos;
  sf::Vector2<int> size;
  e_anim_type animType;
  std::string animTypeStr;
  unsigned int interval = 0;
  int cpt = 0;

  std::string texturePath = _parser.get("General", "Path", "");

  sf::Texture& tex = _textureMap[texturePath];
  tex.loadFromFile(texturePath);

  while ((posS = _parser.get("Positions", std::to_string(cpt), "")) != "")
  {
    pos.x = std::atoi(posS.substr(0, posS.find(",")).c_str());
    pos.y = std::atoi(posS.substr(posS.find(",") + 1, posS.find(":")).c_str());

    size.x = std::atoi(posS.substr(posS.find(":") + 1, posS.find("/")).c_str());
    size.y = std::atoi(posS.substr(posS.find("/") + 1).c_str());

    sprites.push_back(new sf::Sprite(tex, sf::IntRect(pos, size)));

    cpt++;
  }

  animTypeStr = _parser.get("General", "AnimType", "");
  if (animTypeStr == "ONCE")
    animType = ONCE;
  else if (animTypeStr == "LOOP")
    animType = LOOP;
  else if (animTypeStr == "YOYO")
    animType = YOYO;
  else if (animTypeStr == "FREEZE")
    animType = FREEZE;

  interval = std::stoul(_parser.get("General", "IntervalTime", ""));
  // LogInfo() << "interval = " << interval;
  id = std::atoi(_parser.get("General", "ID", "").c_str());
  anim = new Animation(animType, interval);
  for (int i = 0; i < sprites.size(); ++i)
  {
    anim->addSprite(sprites[i]);
  }
  // LogInfo() << "ADD ANIM ID = " << id << " path = " << texturePath;
  _animMap[id] = anim;
}

void  AssetManager::makePattern()
{
  PatternTemplate *pattern;
  unsigned int id;
  unsigned int rarity;
  float diff;
  std::string patternS;

  id = std::atoi(_parser.get("General", "ID", "").c_str());
  diff = std::stof(_parser.get("General", "Difficulty", ""));
  rarity = std::atoi(_parser.get("General", "ChanceOfSpawn", "").c_str());
  patternS = _parser.get("Pattern", "0", "") + _parser.get("Pattern", "1", "") + _parser.get("Pattern", "2", "") + _parser.get("Pattern", "3", "") + _parser.get("Pattern", "4", "");
  pattern = new PatternTemplate(id, patternS, diff, rarity);
  std::string patternSide;
  patternSide = _parser.get("PatternCompatibility", "nextTo", "");
  LogInfo() << "PATTERN SIDE FOR " << id << " is " << patternSide;
  if (patternSide != "none")
  {
    size_t posF = 0;
    unsigned int id = -1;
    id = std::atoi(patternSide.substr(posF, patternSide.find(",", posF + 1) - posF).c_str());
    LogInfo() << "side = " << id;
    pattern->addAdjacentPatternTemplateId(id);
    if (patternSide.find(",") != std::string::npos)
    {
      while ((posF = patternSide.find(",", posF + 1)) != std::string::npos)
      {
        id = std::atoi(patternSide.substr(posF + 1, patternSide.find(",", posF + 1) - posF).c_str());
        pattern->addAdjacentPatternTemplateId(id);
      }
    }
  }
  _patternMap[id] = pattern;
}

void AssetManager::updatePatterns()
{
  for (auto it = _patternMap.begin(); it != _patternMap.end(); ++it)
  {
    std::list<unsigned int> patternIds;

    patternIds = (*it).second->getPatternsId();
    for (auto itId = patternIds.begin(); itId != patternIds.end(); ++itId)
    {
      // LogInfo() << "patt = " << (*it).second->getId() << " id = " << *itId;
      (*it).second->addAdjacentPatternTemplate(_patternMap[*itId]);
    }
  }
}

void  AssetManager::loadGraphicsComponent()
{
  WINFSReader			descReader;
  std::vector<WINFS*>   files;

  descReader.getFilesInDir(files, ANIM_PATH);
  for (unsigned int i = 0; i < files.size(); ++i)
  {
    try
    {
      _parser.open(files[i]->getName());
      _parser.parse();
      if (_parser.get("General", "Type", "") == "SPRITE")
        makeSprite();
      else
        makeAnimation();
    }
    catch (std::exception& e)
    {
      std::cerr << "Error while parsing " << files[i]->getName() << ": " << e.what() << std::endl;
    }
  }
}

void  AssetManager::loadPatterns()
{
  WINFSReader			descReader;
  std::vector<WINFS*>   files;

  descReader.getFilesInDir(files, PATTERN_PATH);
  for (unsigned int i = 0; i < files.size(); ++i)
  {
    try
    {
      _parser.open(files[i]->getName());
      _parser.parse();
      makePattern();
    }
    catch (std::exception& e)
    {
      std::cerr << "Error while parsing " << files[i]->getName() << ": " << e.what() << std::endl;
    }
  }
  updatePatterns();
}

Animation *AssetManager::getAnimation(unsigned int id) const
{
  return _animMap.at(id)->clone();
}

PatternTemplate *AssetManager::getPattern(unsigned int id) const
{
  return _patternMap.at(id)->clone();
}