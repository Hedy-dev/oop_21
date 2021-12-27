#pragma once

#include "CellContent.hpp"

class NonTraversable : public CellContent
{
public:
  NonTraversable();
  ~NonTraversable();

  void nonTraversable();
};