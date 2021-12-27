#pragma once

class LoadException
{
public:
  LoadException(std::string errString) : errString(errString) { }
  virtual ~LoadException() { }

  std::string getErrString() const
  {
    return errString;
  }

private:
  std::string errString;
};