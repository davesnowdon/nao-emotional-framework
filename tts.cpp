#include "tts.h"

#include <iostream>
#include <alcommon/albroker.h>

EmotionalTextToSpeech::EmotionalTextToSpeech(boost::shared_ptr<AL::ALBroker> broker,
                   const std::string& name)
  : AL::ALModule(broker, name)
{
  // Describe the module here. This will appear on the webpage
  setModuleDescription("Emotionally modified speech.");

  // // Pattern:
  // functionName("name", getName(), "description");
  // addParam("param", "");
  // setReturn("return", "");
  // BIND_METHOD(EmotionalTextToSpeech::name);

  functionName("getAvailableLanguages", getName(), "Returns the list of the languages currently installed on the system.");
  setReturn("std::vector<std::string>", "");
  BIND_METHOD(EmotionalTextToSpeech::getAvailableLanguages);

  functionName("getAvailableVoices", getName(), "Returns the list of the voices currently installed on the system. Each voice is given in English.");
  setReturn("std::vector<std::string>", "");
  BIND_METHOD(EmotionalTextToSpeech::getAvailableVoices);

  functionName("getLanguage", getName(), "Returns the language currently used by the text to speech engine.");
  setReturn("std::string", "");
  BIND_METHOD(EmotionalTextToSpeech::getLanguage);

  functionName("getParameter", getName(), "Returns the value of one of the text to speech engine parameters. The available parameters are: “pitchShift”, “doubleVoice”,”doubleVoiceLevel” and “doubleVoiceTimeShift”. Please refers to ALTextToSpeechProxy::setParameter() for details about this parameters.");
  addParam("parameter", "");
  setReturn("float", "");
  BIND_METHOD(EmotionalTextToSpeech::getParameter);

  functionName("getSupportedLanguages", getName(), "Returns the list of all supported languages.");
  addParam("param", "");
  setReturn("std::vector<std::string>", "");
  BIND_METHOD(EmotionalTextToSpeech::getSupportedLanguages);

  functionName("getVoice", getName(), "Returns the voice currently used by the text to speech engine.");
  addParam("param", "");
  setReturn("std::string", "");
  BIND_METHOD(EmotionalTextToSpeech::getVoice);

  functionName("getVolume", getName(), "Gets the current gain applied to the signal synthesized by the text to speech engine. The default value is 1.0.");
  addParam("param", "");
  setReturn("float", "");
  BIND_METHOD(EmotionalTextToSpeech::getVolume);

  functionName("loadVoicePreference", getName(), "Loads a voice and the related set of voice parameters defined in a XML file contained in the preferences folder. The name of the XML file must be of the form ALTextToSpeech_Voice_preferencesFileSuffix. The official voice in each language is defined in this way. Please refers to Tutorial for further details.");
  addParam("preferencesFileSuffix", "");
  BIND_METHOD(EmotionalTextToSpeech::loadVoicePreference);

  functionName("locale", getName(), "Returns the locale associated to the current language set on the robot. The format is xx_XX (examples: en_US, fr_FR, ja_JP, de_DE, ...)");
  setReturn("std::string", "");
  BIND_METHOD(EmotionalTextToSpeech::locale);

  functionName("say", getName(), "Says the specified string of characters.");
  addParam("stringToSay", "");
  BIND_METHOD(EmotionalTextToSpeech::say);

  functionName("say", getName(), "Says the specified string of characters in the specified language.");
  addParam("stringToSay", "");
  addParam("language", "");
  BIND_METHOD(EmotionalTextToSpeech::say);

  functionName("sayToFile", getName(), "Works similarly to ALTextToSpeechProxy::say() but the synthesized signal is recorded into the specified file instead of being sent to the robot’s loudspeakers. The signal is encoded with a sample rate of 22050Hz (European languages) and 16000Hz (Asian languages), format S16_LE, 1 channel.");
  addParam("stringToSay", "");
  addParam("fileName", "");
  BIND_METHOD(EmotionalTextToSpeech::sayToFile);

  functionName("setLanguage", getName(), "Sets the language currently used by the text to speech system. Each NAOqi restart will however reset that setting to the default language that can be set on the robot’s web page.");
  addParam("language", "");
  BIND_METHOD(EmotionalTextToSpeech::setLanguage);

  functionName("setLanguageDefaultVoice", getName(), "Sets the voice to be used by default with a specified language.");
  addParam("language", "");
  addParam("voice", "");
  BIND_METHOD(EmotionalTextToSpeech::setLanguageDefaultVoice);

  functionName("setParameter", getName(), "Sets parameters of the text to speech engine.");
  addParam("parameter", "");
  addParam("value", "")
  BIND_METHOD(EmotionalTextToSpeech::setParameter);

  functionName("setVoice", getName(), "Changes the voice used by the text-to-speech engine. The voice identifier must belong to the installed voices, that can be listed using the ALTextToSpeechProxy::getAvailableVoices() method.");
  addParam("voiceID", "");
  BIND_METHOD(EmotionalTextToSpeech::setVoice);

  functionName("setVolume", getName(), "Sets the current gain applied to the signal synthesized by the text to speech engine. The default value is 1.0.");
  addParam("volume", "");
  BIND_METHOD(EmotionalTextToSpeech::setVolume);

  functionName("stopAll", getName(), "This method stops the current and all the pending tasks immediately.");
  BIND_METHOD(EmotionalTextToSpeech::stopAll);
  
}

EmotionalTextToSpeech::~EmotionalTextToSpeech()
{
}

std::vector<std::string> 
EmotionalTextToSpeech::getAvailableLanguages()
{
}

std::vector<std::string> 
EmotionalTextToSpeech::getAvailableVoices()
{
}

std::string 
EmotionalTextToSpeech::getLanguage()
{
}

float 
EmotionalTextToSpeech::getParameter(const std::string& parameter)
{
}

std::vector<std::string> 
EmotionalTextToSpeech::getSupportedLanguages()
{
}

std::string 
EmotionalTextToSpeech::getVoice()
{
}

float 
EmotionalTextToSpeech::getVolume()
{
}

void 
EmotionalTextToSpeech::loadVoicePreference(const std::string& preferencesFileSuffix)
{
}

std::string 
EmotionalTextToSpeech::locale()
{
}

void 
EmotionalTextToSpeech::say(const std::string& stringToSay)
{
}

void 
EmotionalTextToSpeech::say(const std::string& stringToSay, const std::string& language)
{
}

void 
EmotionalTextToSpeech::sayToFile(const std::string& stringToSay, const std::string& fileName)
{
}

void 
EmotionalTextToSpeech::setLanguage(const std::string& language)
{
}

void 
EmotionalTextToSpeech::setLanguageDefaultVoice(const std::string& language, const std::string& voice)
{
}

void 
EmotionalTextToSpeech::setParameter(const std::string& parameter, const float& value)
{
}

void 
EmotionalTextToSpeech::setVoice(const std::string& voiceID)
{
}

void 
EmotionalTextToSpeech::setVolume(const float& volume)
{
}

void 
EmotionalTextToSpeech::stopAll()
{
}
