#pragma once

#include <iostream>
#include <memory> 
#include <type_traits>
#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <vector>
#include <list>
#include <string>
#include <sstream>
#include <fstream>
#include <stdexcept>
// #include <filesystem>

#ifdef _WIN32
  #include <conio.h>
#elif __APPLE__
  #include <curses.h>
#endif

enum class Entity : unsigned short {
  TRAVERSABLE, // проходимый => пустой
  NON_TRAVERSABLE,
  PLAYER = 101,
  ENEMY = 102,
  ITEM = 103
};

enum class Special : unsigned short {
  NON_SPECIAL,
  ENTRY,
  EXIT
};

enum class Direction : unsigned short {
  UP,
  DOWN,
  LEFT,
  RIGHT,
  NONE
};

namespace Log {
  enum class Type : unsigned short {
    GENERAL, // Все остальное
    BATTLE,  // Бой
    MOVEMENT // Связь с перемещением
  };
}

struct Point
{
  short x, y;
};

enum TypeRule {
  TEnemiesKilledRequirement,
  TExitCellReachRequirement,
  TCollectedItemRequirement
};
