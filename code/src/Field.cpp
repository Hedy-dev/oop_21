#include "pch.hpp"

#include "Field.hpp"

Field::Field(Game* parent, unsigned short width, unsigned short heigth) : parent(parent)
{
  if ((width < 2) || (heigth < 2)){
    std::cout << "Invalid parameters entered. Parameters will be adjusted.";
    if (width < 2) {
      width = 2;
    } if (heigth < 2) {
      heigth = 2;
    }

    std::cout << "Field created with this dimentions: width: " 
    << width << "heigth: " << heigth << std::endl;
  }

  _width = width;
  _heigth = heigth;

  _widthMaxIndex = _width - 1;
  _heigthMaxIndex = _heigth - 1;

  buildField();
}

Field::~Field() 
{
  deleteFieldCells();
}

void Field::deleteFieldCells()
{
  for (unsigned i = 0; i < _width; ++i) {
    delete[] field_contents[i];
  }

  delete[] field_contents;
}

Field::Field(const Field& other) 
{
  *this = other;
}

Field::Field(Field&& other)
{
  *this = std::move(other);
}

Field& Field::operator=(const Field& other)
{
  copyStackValues(this, other);

  if (this->field_contents != nullptr) {
    this->deleteFieldCells();
  }
  // 
  this->fieldBuilder->createFieldCells();
  for (unsigned short i = 0; i < _width; i++) {
    for (unsigned short j = 0; j < _heigth; j++) {
      this->field_contents[i][j] = other.field_contents[i][j]; 
    }
  }

  return *this;
}

Field& Field::operator=(Field&& other)
{
  copyStackValues(this, other);
  other._width = 0;
  other._heigth = 0;
  other._widthMaxIndex = 0;
  other._heigthMaxIndex = 0;

  this->field_contents = other.field_contents;
  other.field_contents = nullptr;

  return *this;
}

unsigned short Field::getWidth()
{
  return _width;
}

unsigned short Field::getHeigth()
{
  return _heigth;
}

Cell Field::getCell(unsigned short width, unsigned short heigth)
{
  return field_contents[width][heigth];
}

void Field::buildField()
{
  fieldBuilder = std::make_unique<FieldBuilder>(this);
  fieldBuilder->initializeField();
}

bool Field::newCellParametersIsValid(Entity entity, Special special)
{
  if (entity == Entity::NON_TRAVERSABLE && special == Special::EXIT) {
    return false;
  } if (entity == Entity::NON_TRAVERSABLE && special == Special::ENTRY) {
    return false;
  }

  return true;
}

void Field::printField()
{
  if (field_contents == nullptr) {
    return;
  }

  for (unsigned short i = 0; i < _width; i++) {
    for (unsigned short j = 0; j < _heigth; j++) {
      std::cout << static_cast<unsigned short>(field_contents[i][j].getCellContentType()) << ' ';
      if ((i == entry.x) && (j == entry.y)) {
        std::cout << "ent";
      } else if ((i == exit.x) && (j == exit.y)) {
        std::cout << "ext";
      }
      std::cout << '\t';
      
    }

    std::cout << std::endl;
  }

  std::cout << std::endl;
}

void Field::copyStackValues(Field* destination, const Field& source)
{
  destination->_width = source._width;
  destination->_heigth = source._heigth;
  destination->_widthMaxIndex = destination->_width - 1;
  destination->_heigthMaxIndex = destination->_heigth - 1;
}

void Field::serialize(std::ofstream& ofs)
{
  ofs << entry.x << std::endl;
  ofs << entry.y << std::endl;

  ofs << exit.x << std::endl;
  ofs << exit.y << std::endl;

  ofs << _width << std::endl;
  ofs << _heigth << std::endl;

  for (unsigned short i = 0; i < _width; ++i) {
    for (unsigned short j = 0; j < _heigth; ++j) {
      serializeCell(field_contents[i][j], ofs);
    }
  }
}

void Field::serializeCell(Cell& cell, std::ofstream& ofs)
{
  auto currentCellContentType = cell.getCellContentType();

  if (currentCellContentType == Entity::ENEMY) {
    auto content = cell.getCellContent<Enemy>();
    content->serialize(ofs);
  } else if (currentCellContentType == Entity::ITEM) {
    auto content = cell.getCellContent<Item>();
    content->serialize(ofs);
  } else if (currentCellContentType == Entity::TRAVERSABLE || currentCellContentType == Entity::NON_TRAVERSABLE) {
    ofs << static_cast<unsigned short>(currentCellContentType) << std::endl;
  } else if (currentCellContentType == Entity::PLAYER) {
    auto content = cell.getCellContent<Player>();
    content->serialize(ofs);
  }
}

void Field::deserialize(std::ifstream& ifs)
{
  ifs >> entry.x;
  ifs >> entry.y;

  ifs >> exit.x;
  ifs >> exit.y;

  ifs >> _width;
  ifs >> _heigth;

  fieldBuilder = std::make_unique<FieldBuilder>(this);
  fieldBuilder->createFieldCells();

  for (unsigned short i = 0; i < _width; ++i) {
    for (unsigned short j = 0; j < _heigth; ++j) {
      field_contents[i][j].setCellContent(deserializeCell(ifs));
    }
  }
}

std::shared_ptr<CellContent> Field::deserializeCell(std::ifstream& ifs)
{
  std::shared_ptr<CellContent> result = std::make_shared<CellContent>();
  result->deserialize(ifs);

  auto currentCellContentType = result->getContentType();

  if (currentCellContentType == Entity::ENEMY) {
    auto enemy = std::make_shared<Enemy>();
    enemy->deserialize(ifs);
    result = std::dynamic_pointer_cast<CellContent>(enemy);
  } else if (currentCellContentType == Entity::ITEM) {
    auto item = std::make_shared<Item>();
    item->deserialize(ifs);
    result = std::dynamic_pointer_cast<CellContent>(item);
  } else if (currentCellContentType == Entity::TRAVERSABLE) {
    result = std::make_shared<Traversable>();
  } else if (currentCellContentType == Entity::NON_TRAVERSABLE) {
    result = std::make_shared<NonTraversable>();
  } else if (currentCellContentType == Entity::PLAYER) {
    std::shared_ptr<Player> player = std::make_shared<Player>();
    player->deserialize(ifs);
    result = std::dynamic_pointer_cast<CellContent>(player);
  }

  result->setContentType(currentCellContentType);
  return result;
}
