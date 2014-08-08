#ifndef EMOTIONAL_LEDS_H
# define EMOTIONAL_LEDS_H

# include <iostream>
# include <alcommon/almodule.h>

#include "emotion.h"

namespace AL
{
  // This is a forward declaration of AL:ALBroker which
  // avoids including <alcommon/albroker.h> in this header
  class ALBroker;
}

/**
 * This class inherits AL::ALModule. This allows it to bind methods
 * and be run as a remote executable within NAOqi
 */
class EmotionalLeds : public AL::ALModule
{
public:
  EmotionalLeds(boost::shared_ptr<AL::ALBroker> broker);

  virtual ~EmotionalLeds();

  /**
   * Overloading ALModule::init().
   * This is called right after the module has been loaded
   */
  virtual void init();

    void createGroup(const std::string& groupName, const std::vector<std::string>& ledNames);

    void earLedsSetAngle(const int& degrees, const float& duration, const bool& leaveOnAtEnd);

    void fade(const std::string& name, const float& intensity, const float& duration);

    void fadeListRGB(const std::string& name, const AL::ALValue& rgbList, const AL::ALValue& timeList);

    void fadeRGB(const std::string& name, const int& rgb, const float& duration);

    AL::ALValue getIntensity(const std::string& name);

    std::vector<std::string> listGroup(const std::string& groupName);

    std::vector<std::string> listGroups();

    std::vector<std::string> listLED(const std::string& name);

    std::vector<std::string> listLEDs();

    void off(const std::string& name);

    void on(const std::string& name);

    void randomEyes(const float& duration);

    void rasta(const float& duration);

    void reset(const std::string& name);

    void rotateEyes(const int& rgb, const float& timeForRotation, const float& totalDuration);

    void setIntensity(const std::string& name, const float& intensity);

};
#endif // EMOTIONAL_LEDS_H
