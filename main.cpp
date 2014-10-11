/*
 * Copyright (c) 2014 Dave Snowdon & Mike McFarlane
 *
 * Main module to run brokers remote from robot
 */
#include <iostream>

#include <boost/shared_ptr.hpp>

#include <alcommon/albroker.h>
#include <alcommon/albrokermanager.h>

#include "emotion.h"
#include "motion.h"
#include "tts.h"
#include "leds.h"
#include "animated-speech.h"

#ifdef FRAMEWORK_IS_REMOTE
# define ALCALL
#else
// when not remote, we're in a dll, so export the entry point
# ifdef _WIN32
#  define ALCALL __declspec(dllexport)
# else
#  define ALCALL
# endif
#endif

void
createEmotionModules(boost::shared_ptr<AL::ALBroker> broker)
{
  AL::ALModule::createModule<Emotion>(broker);
  AL::ALModule::createModule<EmotionalMotion>(broker);
  AL::ALModule::createModule<EmotionalTextToSpeech>(broker);
    AL::ALModule::createModule<EmotionalAnimatedSpeech>(broker, "EmotionalAnimatedSpeech");
  AL::ALModule::createModule<EmotionalLeds>(broker);
 }


extern "C"
{

  ALCALL int _createModule(boost::shared_ptr<AL::ALBroker> broker)
  {
    // init broker with the main broker instance
    // from the parent executable
    AL::ALBrokerManager::setInstance(broker->fBrokerManager.lock());
    AL::ALBrokerManager::getInstance()->addBroker(broker);
    // create module instances
    createEmotionModules(broker);
    return 0;
  }

  ALCALL int _closeModule(  )
  {
    return 0;
  }
};


#ifdef FRAMEWORK_IS_REMOTE
int
main(int argc, char* argv[])
{
 // We will try to connect our broker to a running NAOqi
  int pport = 9559;
  std::string pip = "127.0.0.1";

  // command line parse option
  // check the number of arguments
  if (argc != 1 && argc != 3 && argc != 5) {
    std::cerr << "Wrong number of arguments!" << std::endl;
    std::cerr << "Usage: mymodule [--pip robot_ip] [--pport port]" << std::endl;
    exit(2);
  }

  // if there is only one argument it should be IP or PORT
  if (argc == 3) {
    if (std::string(argv[1]) == "--pip") {
      pip = argv[2];
    } else if (std::string(argv[1]) == "--pport") {
      pport = atoi(argv[2]);
    } else {
      std::cerr << "Wrong number of arguments!" << std::endl;
      std::cerr << "Usage: mymodule [--pip robot_ip] [--pport port]" << std::endl;
      exit(2);
    }
  }

  // Sepcified IP or PORT for the connection
  if (argc == 5) {
    if (std::string(argv[1]) == "--pport"
        && std::string(argv[3]) == "--pip") {
      pport = atoi(argv[2]);
      pip = argv[4];
    } else if (std::string(argv[3]) == "--pport"
               && std::string(argv[1]) == "--pip") {
      pport = atoi(argv[4]);
      pip = argv[2];
    } else {
      std::cerr << "Wrong number of arguments!" << std::endl;
      std::cerr << "Usage: mymodule [--pip robot_ip] [--pport port]" << std::endl;
      exit(2);
    }
  }

  // Need this to for SOAP serialization of floats to work
  setlocale(LC_NUMERIC, "C");

  // A broker needs a name, an IP and a port:
  const std::string brokerName = "mybroker";
  // FIXME: would be a good idea to look for a free port first
  int brokerPort = 54000;
  // listen port of the broker (here an anything)
  const std::string brokerIp = "0.0.0.0";


  // Create your own broker
  boost::shared_ptr<AL::ALBroker> broker;
  try {
    broker = AL::ALBroker::createBroker(
        brokerName,
        brokerIp,
        brokerPort,
        pip,
        pport,
        0    // you can pass various options for the broker creation,
             // but default is fine
      );
  } catch(...) {
    std::cerr << "Fail to connect broker to: "
              << pip
              << ":"
              << pport
              << std::endl;

    AL::ALBrokerManager::getInstance()->killAllBroker();
    AL::ALBrokerManager::kill();

    return 1;
  }

  // Deal with ALBrokerManager singleton (add your broker into NAOqi)
  AL::ALBrokerManager::setInstance(broker->fBrokerManager.lock());
  AL::ALBrokerManager::getInstance()->addBroker(broker);

  // Create all the modules for the emotional framework
  createEmotionModules(broker);

  while (true) {
    qi::os::sleep(1);
  }

  return 0;
}
#endif
