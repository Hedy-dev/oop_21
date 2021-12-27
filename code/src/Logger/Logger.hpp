#pragma once

#include "Subscriber.hpp"

/*!
 * \class Singleton
 * \brief Класс, реализующий журналирование данных. Singleton. Чтобы вызвать функцию
 * i.e. function() используйте: `Singleton::getInstance().function()`.
 */
class Logger : public Subscriber
{
public:
  /*! \brief Функция получения ссылки на экземпляр класса для работы. */
  static Logger& getInstance();

  void onPublish(const std::string& message) override;

  void setConsoleOutput(bool newCondition);
  void setFileOutput(bool newCondition);
                                                           
private:
  Logger();
  ~Logger();
  Logger(const Logger&) = delete;
  Logger& operator=(const Logger&) = delete;
  Logger(Logger&&) = delete;
  Logger& operator=(Logger&&) = delete;

  const std::string logFileName = "game.log";
  std::ofstream oLogStream;

  bool consoleOutput = true;
  bool fileOutput = true;
};
