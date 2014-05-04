#include "leds.h"

#include <iostream>
#include <alcommon/albroker.h>

EmotionalLeds::EmotionalLeds(boost::shared_ptr<AL::ALBroker> broker,
                   const std::string& name)
  : AL::ALModule(broker, name)
{
  setModuleDescription("Emotionally modified LEDs");

  functionName("createGroup", getName(), "Makes a group name for ease of setting multiple LEDs.");
  addParam("groupName", "");
  addParam("ledNames", "");
  BIND_METHOD(EmotionalLeds::createGroup);

  functionName("earLedsSetAngle", getName(), "An animation to show a direction with the ears.");
  addParam("degrees", "");
  addParam("duration", "");
  addParam("leaveOnAtEnd", "");
  BIND_METHOD(EmotionalLeds::earLedsSetAngle);

  functionName("fade", getName(), "Sets the intensity of a LED or Group of LEDs within a given time.");
  addParam("name", "");
  addParam("intensity", "");
  addParam("duration", "");
  BIND_METHOD(EmotionalLeds::fade);

  functionName("fadeListRGB", getName(), "Chain a list of color for a device, as the motion.doMove command.");
  addParam("name", "");
  addParam("rgbList", "");
  addParam("timeList", "");
  BIND_METHOD(EmotionalLeds::fadeListRGB);

  functionName("fadeRGB", getName(), "Sets the intensity of a led. If the name matches an RGB led, all channels are set to the same value.");
  addParam("name", "");
  addParam("rgb", "");
  addParam("duration", "");
  BIND_METHOD(EmotionalLeds::fadeRGB);

  functionName("getIntensity", getName(), "Gets the intensity of a LED.");
  addParam("name", "");
  setReturn("AL::ALValue", "");
  BIND_METHOD(EmotionalLeds::getIntensity);

  functionName("listGroup", getName(), "Lists the devices in the group.");
  addParam("", "");
  setReturn("std::vector<std::string>", "");
  BIND_METHOD(EmotionalLeds::listGroup);

  functionName("listGroups", getName(), "Lists available group names.");
  setReturn("std::vector<std::string>", "");
  BIND_METHOD(EmotionalLeds::listGroups);

  functionName("listLED", getName(), "Lists the devices aliased by a short LED name.");
  addParam("", "");
  setReturn("std::vector<std::string>", "");
  BIND_METHOD(EmotionalLeds::listLED);

  functionName("listLEDs", getName(), "Lists the short LED names.");
  setReturn("std::vector<std::string>", "");
  BIND_METHOD(EmotionalLeds::listLEDs);

  functionName("off", getName(), "Switch to a minimum intensity a LED or Group of LEDs.");
  addParam("name", "");
  BIND_METHOD(EmotionalLeds::off);

  functionName("on", getName(), "Switch to a maximum intensity a LED or Group of LEDs.");
  addParam("name", "");
  BIND_METHOD(EmotionalLeds::on);

  functionName("randomEyes", getName(), "Launch a random animation in eyes");
  addParam("duration", "");
  BIND_METHOD(EmotionalLeds::randomEyes);

  functionName("rasta", getName(), "Launch a green/yellow/red rasta animation on all body.");
  addParam("duration", "");
  BIND_METHOD(EmotionalLeds::rasta);

  functionName("reset", getName(), "Resets the state of the leds to default");
  addParam("name", "");
  BIND_METHOD(EmotionalLeds::reset);

  functionName("rotateEyes", getName(), "Launch a rotation using the leds of the eyes.");
  addParam("rgb", "");
  addParam("timeForRotation", "");
  addParam("totalDuration", "");
  BIND_METHOD(EmotionalLeds::rotateEyes);

  functionName("setIntensity", getName(), "Sets the intensity of a LED or Group of LEDs.");
  addParam("name", "");
  addParam("intensity", "");
  BIND_METHOD(EmotionalLeds::setIntensity);

}

EmotionalLeds::~EmotionalLeds()
{
}

void
EmotionalLeds::init()
{
}

void
EmotionalLeds::createGroup(const std::string& groupName, const std::vector<std::string>& ledNames)
{
}


void
EmotionalLeds::earLedsSetAngle(const int& degrees, const float& duration, const bool& leaveOnAtEnd)
{
}


void
EmotionalLeds::fade(const std::string& name, const float& intensity, const float& duration)
{
}


void
EmotionalLeds::fadeListRGB(const std::string& name, const AL::ALValue& rgbList, const AL::ALValue& timeList)
{
}


void
EmotionalLeds::fadeRGB(const std::string& name, const int& rgb, const float& duration)
{
}


AL::ALValue
EmotionalLeds::getIntensity(const std::string& name)
{
}


std::vector<std::string>
EmotionalLeds::listGroup(const std::string& groupName)
{
}


std::vector<std::string>
EmotionalLeds::listGroups()
{
}


std::vector<std::string>
EmotionalLeds::listLED(const std::string& name)
{
}


std::vector<std::string>
EmotionalLeds::listLEDs()
{
}


void
EmotionalLeds::off(const std::string& name)
{
}


void
EmotionalLeds::on(const std::string& name)
{
}


void
EmotionalLeds::randomEyes(const float& duration)
{
}


void
EmotionalLeds::rasta(const float& duration)
{
}


void
EmotionalLeds::reset(const std::string& name)
{
}


void
EmotionalLeds::rotateEyes(const int& rgb, const float& timeForRotation, const float& totalDuration)
{
}


void
EmotionalLeds::setIntensity(const std::string& name, const float& intensity)
{
}
