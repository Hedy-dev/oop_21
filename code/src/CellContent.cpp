#include "pch.hpp"

#include "CellContent.hpp"

CellContent::CellContent() { }
CellContent::~CellContent() { }

Entity CellContent::getContentType()
{
  return _cellContentType;
}

void CellContent::serialize(std::ofstream& ofs)
{
  ofs << static_cast<unsigned short>(_cellContentType) << std::endl;
}

void CellContent::deserialize(std::ifstream& ifs)
{
  unsigned short cellContentType; 
  ifs >> cellContentType;
  _cellContentType = static_cast<Entity>(cellContentType);
}

void CellContent::setContentType(Entity cellContentType)  // virtual - переопределение override - функция определенная в базовом классе
{
  _cellContentType = cellContentType;
}
