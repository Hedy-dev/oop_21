#pragma once

class ExitCellReachRequirement
{
public:
  ExitCellReachRequirement(bool isTurnedOn) : isTurnedOn(isTurnedOn) { }

  bool isTurnedOn;

  bool descriptionExitCellReachRequirement();
};