#ifndef EMOTION_H
# define EMOTION_H

#include <map>
# include <iostream>
# include <alcommon/almodule.h>

namespace AL
{
  // This is a forward declaration of AL:ALBroker which
  // avoids including <alcommon/albroker.h> in this header
  class ALBroker;
}

const std::string EMOTION_MODULE = "Emotion";
const std::string MOTION_MODULE = "ALMotion";
const std::string MOTION_MODULE_ADAPTOR = "EmotionalMotion";
const std::string TTS_MODULE = "ALTextToSpeech";
const std::string TTS_MODULE_ADAPTOR = "EmotionalTextToSpeech";
const std::string LED_MODULE = "ALLeds";
const std::string LED_MODULE_ADAPTOR = "EmotionalLeds";


class Emotion : public AL::ALModule
{
public:
  Emotion(boost::shared_ptr<AL::ALBroker> broker);

  virtual ~Emotion();

  /**
   * Overloading ALModule::init().
   * This is called right after the module has been loaded
   */
  virtual void init();

  // Return the name of the proxy to use instead of the named
  // standard proxy
  std::string getProxyName(const std::string& proxyName);

private:
  std::map<std::string, std::string> mModuleNames;
};
#endif // EMOTION_H
