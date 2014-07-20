/*
 * Copyright (c) 2012, 2013 Aldebaran Robotics. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the COPYING file.
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

extern "C"
{
  ALCALL int _createModule(boost::shared_ptr<AL::ALBroker> broker)
  {
    // init broker with the main broker instance
    // from the parent executable
    AL::ALBrokerManager::setInstance(broker->fBrokerManager.lock());
    AL::ALBrokerManager::getInstance()->addBroker(broker);
    // create module instances
    AL::ALModule::createModule<Emotion>(broker, "Emotion");
    AL::ALModule::createModule<EmotionalMotion>(broker, "EmotionalMotion");
    AL::ALModule::createModule<EmotionalTextToSpeech>(broker, "EmotionalTextToSpeech");
    AL::ALModule::createModule<EmotionalLeds>(broker, "EmotionalLeds");
    AL::ALModule::createModule<EmotionalAnimatedSpeech>(broker, "EmotionalAnimatedSpeech");
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
