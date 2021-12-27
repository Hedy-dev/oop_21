#include "pch.hpp"
#include "Enemy.hpp"

Enemy::Enemy(std::shared_ptr<Strategy> strategy) //поменять
{
  setStrategy(strategy);
  Logger::getInstance().subscribe(this);
}

unsigned short Enemy::attack()
{
  std::stringstream logStream;
  log.setLogType(Log::Type::BATTLE);
  logStream << "Damage: " << damage << std::endl;
  log << logStream.str();
  return damage;
}

unsigned short Enemy::dealDamage(unsigned short playerDamage)
{
  std::stringstream logStream;
  log.setLogType(Log::Type::BATTLE);
  if (playerDamage >= health){
    logStream << "Emeny is dead." << std::endl;
    log << logStream.str();
    return 0;
  } 
  
  health -= playerDamage;
  return health;
}

std::shared_ptr<Strategy> Enemy::getStrategy()
{
  return _strategy;
}

void Enemy::setStrategy(std::shared_ptr<Strategy> strategy)
{
  _strategy = strategy;
}

Direction Enemy::makeDecision(Point enemy, Point player)
{
  return _strategy->makeDecision(enemy, player);
}

void Enemy::serialize(std::ofstream& ofs)
{
  CellContent::serialize(ofs);

  ofs << static_cast<unsigned short>(_strategy->getStrategyEnum()) << std::endl;
  ofs << health << std::endl;
  ofs << damage << std::endl;
}

void Enemy::deserialize(std::ifstream& ifs)
{
  unsigned short strategyEnum;
  ifs >> strategyEnum;

  if (strategyEnum == StrategyEnum::FLEE) {
    setStrategy(std::make_shared<Flee>());
  } else if (strategyEnum == StrategyEnum::ATTACK) {
    setStrategy(std::make_shared<Attack>());
  } else if (strategyEnum == StrategyEnum::PASSIVE) {
    setStrategy(std::make_shared<Passive>());
  }
  
  ifs >> health;
  ifs >> damage;
}