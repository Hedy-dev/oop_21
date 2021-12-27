#include "pch.hpp"

#include "Item.hpp"

Item::Item()
{
  Logger::getInstance().subscribe(this);
}

Item::~Item() {}; // Модификаторы только в декларации, а не в реализации 

void Item::itemSpecialProperty()
{
  std::stringstream logStream;
  log.setLogType(Log::Type::MOVEMENT);
  logStream << "Attack: " << attackBonus << std::endl;
  log << logStream.str();
  logStream.str(std::string());
  logStream << "Defense: " << defenseBonus << std::endl;
  log << logStream.str();
  logStream.str(std::string());
  logStream << "Health: " << healthBonus << std::endl;
  log << logStream.str();
}

void Item::serialize(std::ofstream& ofs)
{
  CellContent::serialize(ofs);

  ofs << attackBonus << std::endl;
  ofs << defenseBonus << std::endl;
  ofs << healthBonus << std::endl;
}

void Item::deserialize(std::ifstream& ifs)
{
  ifs >> attackBonus;
  ifs >> defenseBonus;
  ifs >> healthBonus;
}