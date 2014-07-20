#ifndef EMOTIONAL_TTS_H
# define EMOTIONAL_TTS_H

# include <iostream>
# include <alcommon/almodule.h>

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
class EmotionalTextToSpeech : public AL::ALModule
{
public:
  EmotionalTextToSpeech(boost::shared_ptr<AL::ALBroker> broker,
           const std::string &name);

  virtual ~EmotionalTextToSpeech();

  /**
   * Overloading ALModule::init().
   * This is called right after the module has been loaded
   */
  virtual void init();

    std::vector<std::string> getAvailableLanguages();

    std::vector<std::string> getAvailableVoices();

    std::string getLanguage();

    float getParameter(const std::string& parameter);

    std::vector<std::string> getSupportedLanguages();

    std::string getVoice();

    float getVolume();

    void loadVoicePreference(const std::string& preferencesFileSuffix);

    std::string locale();

    void say(const std::string& stringToSay);

    void say(const std::string& stringToSay, const std::string& language);

    void sayToFile(const std::string& stringToSay, const std::string& fileName);

    void setLanguage(const std::string& language);

    void setLanguageDefaultVoice(const std::string& language, const std::string& voice);

    void setParameter(const std::string& parameter, const float& value);

    void setVoice(const std::string& voiceID);

    void setVolume(const float& volume);

    void stopAll();

};
#endif // EMOTIONAL_TTS_H
