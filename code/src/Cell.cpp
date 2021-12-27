#include "pch.hpp"

#include "Cell.hpp"

Cell::Cell() { }
Cell::~Cell() { }


Entity Cell::getCellContentType()
{
  return _cellContent->getContentType();
}
