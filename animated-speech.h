#ifndef EMOTIONAL_ANIMATED_SPEECH_H
# define EMOTIONAL_ANIMATED_SPEECH_H

# include <iostream>
# include <alcommon/almodule.h>
# include <alproxies/alanimatedspeechproxy.h>

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
class EmotionalAnimatedSpeech : public AL::ALModule
{
public:
  EmotionalAnimatedSpeech(boost::shared_ptr<AL::ALBroker> broker,
           const std::string &name);

  virtual ~EmotionalAnimatedSpeech();

  /**
   * Overloading ALModule::init().
   * This is called right after the module has been loaded
   */
  virtual void init();

    void say(const std::string& text);

    void say(const std::string& text, const AL::ALValue& configuration);

    void setBodyLanguageMode(unsigned int bodyLanguageMode);

    void setBodyLanguageModeFromStr(const std::string& stringBodyLanguageMode);

    unsigned int getBodyLanguageMode();

    std::string getBodyLanguageModeToStr();

    void addTagsToWords(const AL::ALValue& tagsToWords);

    void declareAnimationsPackage(const std::string& animationsPackage);

    void declareTagForAnimations(const AL::ALValue& tagsToAnimations);

    typedef boost::shared_ptr<AL::ALAnimatedSpeechProxy> ALAnimatedSpeechProxyPtr;

private:
    ALAnimatedSpeechProxyPtr animatedSpeechProxy;
};
#endif // EMOTIONAL_ANIMATED_SPEECH_H
