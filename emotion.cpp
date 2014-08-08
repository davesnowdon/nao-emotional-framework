#include "emotion.h"

#include <iostream>
#include <alcommon/albroker.h>

Emotion::Emotion(boost::shared_ptr<AL::ALBroker> broker,
                   const std::string& name)
  : AL::ALModule(broker, name)
{
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
  return "";
}
