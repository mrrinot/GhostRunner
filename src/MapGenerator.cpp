#include "MapGenerator.hh"
#include "Scene.hh"
#include "Block.hh"
#include "EndBlock.hh"
#include "Logger.hh"
#include <cmath>
#include <ctime>

const float MapGenerator::BLOCK_SIZE = 100.f;

MapGenerator::MapGenerator()
{

}

MapGenerator::~MapGenerator()
{
  //for (auto it = _patternList.begin(); it != _patternList.end(); ++it)
  //  delete *it;
}

void  MapGenerator::createMap(float difficulty, MapGenerator::e_MapSize size, AssetManager &manager)
{
  for (auto it = _patternList.begin(); it != _patternList.end(); ++it)
    delete *it;
  _patternList.clear();
  srand(static_cast<unsigned int>(time(NULL)));

  // Push the start wall;
  PatternTemplate *patt = manager.getPattern(THE_WALL + 1);
  patt->setPos(Vector::Vector2<int>(0, -1));
  _patternList.push_back(patt);
  // Push the start pattern
  patt = manager.getPattern(START_PATTERN);
  Vector::Vector2<int> pos = Vector::Vector2<int>(0, 0);
  patt->setPos(pos);
  _patternList.push_back(patt);

  // Add random patterns
  while (_patternList.size() < size)
  {
    patt = manager.getPattern(patt->getRandomPattern(difficulty));
    pos = Vector::Vector2<int>(pos.x() + 1, pos.y());
    patt->setPos(pos);
    _patternList.push_back(patt);
  }

  // Push the end pattern
  patt = manager.getPattern(END_PATTERN);
  pos = Vector::Vector2<int>(pos.x() + 1, pos.y());
  patt->setPos(pos);
  _patternList.push_back(patt);
  // Push the end wall
  patt = manager.getPattern(THE_WALL);
  pos = Vector::Vector2<int>(pos.x(), pos.y() - 1);
  patt->setPos(pos);
  _patternList.push_back(patt);

  // Create the blocks in the scene
  Scene &scene = Scene::getInstance();
  for (auto it = _patternList.begin(); it != _patternList.end(); ++it)
  {
    //// LogInfo() << "ADD PATTERN " << (*it)->getPatternTemplate() << " at pos " << (*it)->getPos().x() << "/" << (*it)->getPos().y();
    std::string pattern = (*it)->getPatternTemplate();
    for (int cpt = 0; cpt < pattern.size(); ++cpt)
    {
      float posX = 5.f * (*it)->getPos().x();
      float posY = 5.f * (*it)->getPos().y();
      Vector::Vector2<float> pos = Vector::Vector2<float>((posX + (cpt % 5)) * BLOCK_SIZE, (posY + (cpt / 5)) * BLOCK_SIZE);
      GameObject *tmp;

      if (pattern.at(cpt) == 'B')
        scene.addGameObject((new Block("Block", pos, Vector::Vector2<float>(BLOCK_SIZE, BLOCK_SIZE)))
        ->addAnimation("default", manager.getAnimation(11)->setSpriteSize(Vector::Vector2<float>(BLOCK_SIZE, BLOCK_SIZE))));
      /*if (pattern.at(cpt) == 'E')
      {
        tmp = new Block("InviBlock", pos, Vector::Vector2<float>(BLOCK_SIZE, BLOCK_SIZE));
        tmp->addAnimation("default", manager.getAnimation(15)->setSpriteSize(Vector::Vector2<float>(BLOCK_SIZE, BLOCK_SIZE)));
        tmp->removeLayer(Layer::WALL);
        tmp->getAnimator().setColor(sf::Color(255, 255, 255, 70));
        scene.addGameObject(tmp);
      }*/
      else if (pattern.at(cpt) == 'D')
		  scene.addEnd((EndBlock *)(new EndBlock("EndBlock", pos - Vector::Vector2<float>(0, 236.f), Vector::Vector2<float>(61.f, 336.f)))
        ->addAnimation("default", manager.getAnimation(14)->setSpriteSize(Vector::Vector2<float>(61.f, 336.f))));
      else if (pattern.at(cpt) == 'S')
        _startPos = pos;
    }
    delete *it;
  }
}

const Vector::Vector2<float> &MapGenerator::getStartPos() const
{
  return _startPos;
}