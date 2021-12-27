#pragma once

#include "Publisher.hpp"
#include "LocalLogger.hpp"

// Класс, добавляющий в Publisher работу с логами. Можно было бы добавить этот 
// функционал в сам Publisher, но тогда это уже был бы не совсем Publisher, он
// был бы уже заточен под работу с логами. Каждый класс должен делать то, что
// говорится в его имени. Publisher только быть publisher'ом и не более.
class LogPublisher : public Publisher
{
protected:
  LocalLogger log = LocalLogger(this);
};
