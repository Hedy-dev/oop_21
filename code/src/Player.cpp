#include "pch.hpp"

#include "Player.hpp"

Player::Player() 
{ 
  Logger::getInstance().subscribe(this);
}

Player::~Player() { }

unsigned short Player::dealDamage(unsigned short damage)
{
  std::stringstream logStream;
  log.setLogType(Log::Type::MOVEMENT);
  unsigned short CurrentHealthPlayer = health + defense;
  if (damage >= CurrentHealthPlayer) {

    
    logStream << "Player is dead" << std::endl;
    
    log << logStream.str();
    //std::cout << "Player is dead" << std::endl;
    return 0;
  }

  health = CurrentHealthPlayer - damage;
  
  logStream << "Player's current health: " << health << std::endl;
  log << logStream.str();
  //std::cout << "Player's current health: " << health << std::endl;
  return health;
}

unsigned short Player::defenseUp(unsigned short defenseUp)
{
  return changeParameters(defenseUp, defenseUp, PlayerParameter::DEFENCE);

}

unsigned short Player::attackUp(unsigned short powerUp)
{
  return changeParameters(attack, powerUp, PlayerParameter::ATTACK);
}

unsigned short Player::healthUp(unsigned short healthUp)
{
  return changeParameters(health, healthUp, PlayerParameter::HEALTH);
}

unsigned short Player::changeParameters(unsigned short parameter, unsigned short change,
  PlayerParameter playerParameter)
{
  std::string parameterName;
  if (playerParameter == PlayerParameter::HEALTH) {
    parameterName = "health";
  } else if (playerParameter == PlayerParameter::ATTACK) {
    parameterName = "attack";
  } else if (playerParameter == PlayerParameter::DEFENCE) {
    parameterName = "defence";
  }

  unsigned short currentPlayerParameter = parameter + change;
  std::stringstream logStream;
  log.setLogType(Log::Type::MOVEMENT);
  if (currentPlayerParameter <= 100) {
    parameter = currentPlayerParameter;

    logStream << "Player's current " << parameterName << ": " << parameter << std::endl;

    
    log << logStream.str();
    
  } else {
    parameter = 100;
    logStream << "Player's current " << parameterName << " is max " << std::endl;
    log << logStream.str();
  }
  
  return parameter;
}

void Player::serialize(std::ofstream& ofs)
{
  CellContent::serialize(ofs);

  ofs << health << std::endl;
  ofs << attack << std::endl;
  ofs << defense << std::endl;
}

void Player::deserialize(std::ifstream& ifs)
{
  ifs >> health;
  ifs >> attack;
  ifs >> defense;
}
