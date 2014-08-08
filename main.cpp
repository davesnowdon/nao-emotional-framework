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

extern "C"
{
  ALCALL int _createModule(boost::shared_ptr<AL::ALBroker> broker)
  {
    // init broker with the main broker instance
    // from the parent executable
    AL::ALBrokerManager::setInstance(broker->fBrokerManager.lock());
    AL::ALBrokerManager::getInstance()->addBroker(broker);
    // create module instances
    AL::ALModule::createModule<Emotion>(broker);
    AL::ALModule::createModule<EmotionalMotion>(broker);
    AL::ALModule::createModule<EmotionalTextToSpeech>(broker);
    AL::ALModule::createModule<EmotionalLeds>(broker);
    return 0;
  }

  ALCALL int _closeModule(  )
  {
    return 0;
  }
};

#ifdef FRAMEWORK_IS_REMOTE
int main()
{
  std::cout << "Hello, world" << std::endl;
  return 0;
}
#endif
