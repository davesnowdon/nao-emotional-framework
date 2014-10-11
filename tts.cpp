#include "tts.h"

#include <iostream>
#include <alcommon/albroker.h>

EmotionalTextToSpeech::EmotionalTextToSpeech(boost::shared_ptr<AL::ALBroker> broker)
  : AL::ALModule(broker, TTS_MODULE_ADAPTOR)
{
  // Describe the module here. This will appear on the webpage
  setModuleDescription("Emotional wrapper for ALTextToSpeech.");

  functionName("getAvailableLanguages", getName(), "Outputs the languages installed on the system.");
  setReturn("std::vector<std::string>", "Array of std::string that contains the languages installed on the system.");
  BIND_METHOD(EmotionalTextToSpeech::getAvailableLanguages);

  functionName("getAvailableVoices", getName(), "Outputs the available voices. The returned list contains the voice IDs.");
  setReturn("std::vector<std::string>", "Array of std::string containing the voices installed on the system.");
  BIND_METHOD(EmotionalTextToSpeech::getAvailableVoices);

  functionName("getLanguage", getName(), "Returns the language currently used by the text-to-speech engine.");
  setReturn("std::string", "Language of the current voice.");
  BIND_METHOD(EmotionalTextToSpeech::getLanguage);

  functionName("getParameter", getName(), "Returns the value of one of the voice parameters. The available parameters are: pitchShift, doubleVoice,doubleVoiceLevel and doubleVoiceTimeShift");
  addParam("pParameterName", "Name of the parameter");
  setReturn("float", "Value of the specified parameter");
  BIND_METHOD(EmotionalTextToSpeech::getParameter);

  functionName("getSupportedLanguages", getName(), "Outputs all the languages supported (may be installed or not).");
  setReturn("std::vector<std::string>", "Array of std::string that contains all the supported languages (may be installed or not).");
  BIND_METHOD(EmotionalTextToSpeech::getSupportedLanguages);

  functionName("getVoice", getName(), "Returns the voice currently used by the text-to-speech engine.");
  setReturn("std::string", "Name of the current voice");
  BIND_METHOD(EmotionalTextToSpeech::getVoice);

  functionName("getVolume", getName(), "Fetches the current volume the text to speech.");
  setReturn("float", "Volume (integer between 0 and 100).");
  BIND_METHOD(EmotionalTextToSpeech::getVolume);

  functionName("loadVoicePreference", getName(), "Loads a set of voice parameters defined in a xml file contained in the preferences folder.The name of the xml file must begin with ALTextToSpeech_Voice_");
  addParam("pPreferenceName", "Name of the voice preference.");
  BIND_METHOD(EmotionalTextToSpeech::loadVoicePreference);

  functionName("locale", getName(), "Get the locale associate to the current language.");
  setReturn("std::string", "A string with xx_XX format (region_country)");
  BIND_METHOD(EmotionalTextToSpeech::locale);

  functionName("say", getName(), "Performs the text-to-speech operations : it takes a std::string as input and outputs a sound in both speakers. String encoding must be UTF8.");
  addParam("stringToSay", "Text to say, encoded in UTF-8.");
  AL::completeAndCheck<
    EmotionalTextToSpeech,
    const std::string&,
    void>
    (&EmotionalTextToSpeech::say, getCurrentMethodDescription());
  bindMethodOverload(AL::createFunctor<EmotionalTextToSpeech,
                     std::string,
                     void>
  (this, &EmotionalTextToSpeech::say));

  functionName("say", getName(), "Performs the text-to-speech operations in a specific language: it takes a std::string as input and outputs a sound in both speakers. String encoding must be UTF8. Once the text is said, the language is set back to its initial value.");
  addParam("std::string", "Text to say, encoded in UTF-8");
  addParam("std::string", "Language used to say the text.");
  AL::completeAndCheck<
    EmotionalTextToSpeech,
    const std::string&,
    const std::string&,
    void>
    (&EmotionalTextToSpeech::say, getCurrentMethodDescription());
  bindMethodOverload(AL::createFunctor<EmotionalTextToSpeech,
                     std::string,
                     std::string,
                     void>
  (this, &EmotionalTextToSpeech::say));

  functionName("sayToFile", getName(), "Performs the text-to-speech operations: it takes a std::string as input and outputs the corresponding audio signal in the specified file.");
  addParam("std::string", "Text to say, encoded in UTF-8");
  addParam("std::string", "RAW file where to store the generated signal. The signal is encoded with a sample rate of 22050Hz, format S16_LE, 2 channels.");
  BIND_METHOD(EmotionalTextToSpeech::sayToFile);

  functionName("setLanguage", getName(), "Changes the language used by the Text-to-Speech engine. It automatically changes the voice used since each of them is related to a unique language. If you want that change to take effect automatically after reboot of your robot, refer to the robot web page (setting page).");
  addParam("std::string", "Language name. Must belong to the languages available in TTS (can be obtained with the getAvailableLanguages method).  It should be an identifier std::string.");
  BIND_METHOD(EmotionalTextToSpeech::setLanguage);

  functionName("setLanguageDefaultVoice", getName(), "Sets a voice as the default voice for the corresponding language");
  addParam("std::string", "The language among those available on your robot as a String");
  addParam("std::string", " The voice among those available on your robot as a String");
  BIND_METHOD(EmotionalTextToSpeech::setLanguageDefaultVoice);

  functionName("setParameter", getName(), "Changes the parameters of the voice. ");
  addParam("std::string", "Name of the parameter");
  addParam("float", "Value of the parameter");
  BIND_METHOD(EmotionalTextToSpeech::setParameter);

  functionName("setVoice", getName(), "Changes the voice used by the text-to-speech engine. The voice identifier must belong to the installed voices, that can be listed using the 'getAvailableVoices' method. If the voice is not available, it remains unchanged. No exception is thrown in this case. For the time being, only two voices are available by default : Kenny22Enhanced (English voice) and Julie22Enhanced (French voice)");
  addParam("std::string", "The voice");
  BIND_METHOD(EmotionalTextToSpeech::setVoice);

  functionName("setVolume", getName(), "Sets the volume of text-to-speech output.");
  addParam("float", "Volume (between 0.0 and 1.0)");
  BIND_METHOD(EmotionalTextToSpeech::setVolume);

  functionName("stopAll", getName(), "This method stops the current and all the pending tasks immediately.");
  BIND_METHOD(EmotionalTextToSpeech::stopAll);

  // TODO add error checking for proxy creation
  ttsProxy = ALTextToSpeechProxyPtr(new AL::ALTextToSpeechProxy(broker));
}

EmotionalTextToSpeech::~EmotionalTextToSpeech()
{
}

void
EmotionalTextToSpeech::init()
{
}

std::vector<std::string>
EmotionalTextToSpeech::getAvailableLanguages()
{
  return ttsProxy->getAvailableLanguages();
}

std::vector<std::string>
EmotionalTextToSpeech::getAvailableVoices()
{
  return ttsProxy->getAvailableVoices();
}

std::string
EmotionalTextToSpeech::getLanguage()
{
  return ttsProxy->getLanguage();
}

float
EmotionalTextToSpeech::getParameter(const std::string& pParameterName)
{
  return ttsProxy->getParameter(pParameterName);
}

std::vector<std::string>
EmotionalTextToSpeech::getSupportedLanguages()
{
  return ttsProxy->getSupportedLanguages();
}

std::string
EmotionalTextToSpeech::getVoice()
{
  return ttsProxy->getVoice();
}

float
EmotionalTextToSpeech::getVolume()
{
  return ttsProxy->getVolume();
}

void
EmotionalTextToSpeech::loadVoicePreference(const std::string& pPreferenceName)
{
  ttsProxy->loadVoicePreference(pPreferenceName);
}

std::string
EmotionalTextToSpeech::locale()
{
  return ttsProxy->locale();
}

void
EmotionalTextToSpeech::say(const std::string& stringToSay)
{
  ttsProxy->say(stringToSay);
}

void
EmotionalTextToSpeech::say(const std::string& stringToSay, const std::string& language)
{
  ttsProxy->say(stringToSay, language);
}

void
EmotionalTextToSpeech::sayToFile(const std::string& pStringToSay, const std::string& pFileName)
{
  ttsProxy->sayToFile(pStringToSay, pFileName);
}

void
EmotionalTextToSpeech::setLanguage(const std::string& pLanguage)
{
  ttsProxy->setLanguage(pLanguage);
}

void
EmotionalTextToSpeech::setLanguageDefaultVoice(const std::string& language, const std::string& voice)
{
  ttsProxy->setLanguageDefaultVoice(language, voice);
}

void
EmotionalTextToSpeech::setParameter(const std::string& pEffectName, const float& pEffectValue)
{
  ttsProxy->setParameter(pEffectName, pEffectValue);
}

void
EmotionalTextToSpeech::setVoice(const std::string& pVoiceID)
{
  ttsProxy->setVoice(pVoiceID);
}

void
EmotionalTextToSpeech::setVolume(const float& volume)
{
  ttsProxy->setVolume(volume);
}

void
EmotionalTextToSpeech::stopAll()
{
  ttsProxy->stopAll();
}
