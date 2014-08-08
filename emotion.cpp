#include "emotion.h"

#include <iostream>
#include <alcommon/albroker.h>

Emotion::Emotion(boost::shared_ptr<AL::ALBroker> broker)
  : AL::ALModule(broker, EMOTION_MODULE)
{
  mModuleNames[MOTION_MODULE] = MOTION_MODULE_ADAPTOR;
  mModuleNames[TTS_MODULE] = TTS_MODULE_ADAPTOR;
  mModuleNames[LED_MODULE] = LED_MODULE_ADAPTOR;

  // Describe the module here. This will appear on the webpage
  setModuleDescription("This module provides access to the emotional model and the adaptor modules that wrap the standard modules");

  /**
   * addParam(<attribut_name>, <attribut_descrption>);
   * This enables to document the parameters of the method.
   * It is not compulsory to write this line.
   */
  functionName("getProxyName", getName(), "Return the name of the module to use instead of the named standard proxy");
  addParam("std::string", "The name of the standard module");
  setReturn("std::string", "The name of the module to use instead");
  BIND_METHOD(Emotion::getProxyName);
}

Emotion::~Emotion()
{
}

void Emotion::init()
{

}



std::string
Emotion::getProxyName(const std::string& proxyName)
{
  std::map<std::string, std::string>::iterator it;
  it = mModuleNames.find(proxyName);
  if (it == mModuleNames.end()) {
    /* module name not found in map so return name unchanged */
    return proxyName;
  } else {
    /* return name of adaptor for this module */
    return it->second;
  }
}
