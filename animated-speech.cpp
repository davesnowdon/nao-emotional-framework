#include "animated-speech.h"

#include <iostream>
#include <alcommon/albroker.h>

EmotionalAnimatedSpeech::EmotionalAnimatedSpeech(boost::shared_ptr<AL::ALBroker> broker,
                   const std::string& name)
  : AL::ALModule(broker, name)
{
  // Describe the module here. This will appear on the webpage
  setModuleDescription("Emotional modified animated speech.");

  // // Pattern:
  // functionName("name", getName(), "description");
  // addParam("param", "");
  // setReturn("return", "");
  // BIND_METHOD(EmotionalAnimatedSpeech::name);

  functionName("say", getName(), "Say the annotated text given in parameter and animate it with animations inserted in the text. The current Animated Speech configuration will be used.");
  addParam("text", "");
  AL::completeAndCheck<
    EmotionalAnimatedSpeech,
    const std::string&,
    void>
    (&EmotionalAnimatedSpeech::say, getCurrentMethodDescription());
  bindMethodOverload(AL::createFunctor<EmotionalAnimatedSpeech,
                     std::string,
                     void>
  (this, &EmotionalAnimatedSpeech::say));

  functionName("say", getName(), "Say the annotated text given in parameter and animate it with animations inserted in the text. The given configuration will be used. For the unset parameters, their default value will be used.");
  addParam("text", "");
  addParam("configuration", "");
  AL::completeAndCheck<
    EmotionalAnimatedSpeech,
    const std::string&,
    const AL::ALValue&,
    void>
    (&EmotionalAnimatedSpeech::say, getCurrentMethodDescription());
  bindMethodOverload(AL::createFunctor<EmotionalAnimatedSpeech,
                     std::string,
                     AL::ALValue,
                     void>
  (this, &EmotionalAnimatedSpeech::say));

  functionName("setBodyLanguageMode", getName(), "Set the current body language mode.");
  addParam("bodyLanguageMode", "");
  BIND_METHOD(EmotionalAnimatedSpeech::setBodyLanguageMode);

  functionName("setBodyLanguageModeFromStr", getName(), "Set the current body language mode from a string.");
  addParam("stringBodyLanguageMode", "");
  BIND_METHOD(EmotionalAnimatedSpeech::setBodyLanguageModeFromStr);

  functionName("getBodyLanguageMode", getName(), "Get the current body language mode.");
  setReturn("unsigned int", "");
  BIND_METHOD(EmotionalAnimatedSpeech::getBodyLanguageMode);

  functionName("getBodyLanguageModeToStr", getName(), "Get a string corresponding to the current body language mode.");
  setReturn("unsigned int", "");
  BIND_METHOD(EmotionalAnimatedSpeech::getBodyLanguageModeToStr);

  functionName("addTagsToWords", getName(), "Link some words to some specific animation tags.");
  addParam("tagsToWords", "");
  BIND_METHOD(EmotionalAnimatedSpeech::addTagsToWords);

  functionName("declareAnimationsPackage", getName(), "Allows using animations contained in the specified package as tagged animations.");
  addParam("animationsPackage", "");
  BIND_METHOD(EmotionalAnimatedSpeech::declareAnimationsPackage);

  functionName("declareTagForAnimations", getName(), "Dynamically associate tags and animations.");
  addParam("tagsToAnimations", "");
  BIND_METHOD(EmotionalAnimatedSpeech::declareTagForAnimations);

  // TODO add error checking for proxy creation
  animatedSpeechProxy = ALAnimatedSpeechProxyPtr(new AL::ALAnimatedSpeechProxy(broker));
}

EmotionalAnimatedSpeech::~EmotionalAnimatedSpeech()
{
}

void
EmotionalAnimatedSpeech::init()
{
}

void
EmotionalAnimatedSpeech::say(const std::string& text)
{
  animatedSpeechProxy->say(text);
}

void
EmotionalAnimatedSpeech::say(const std::string& text, const AL::ALValue& configuration)
{
  // TODO The Aldebaran proxy does not seem to implement this overload
  animatedSpeechProxy->say(text);
}

void
EmotionalAnimatedSpeech::setBodyLanguageMode(unsigned int bodyLanguageMode)
{
  animatedSpeechProxy->setBodyLanguageMode(bodyLanguageMode);
}

void
EmotionalAnimatedSpeech::setBodyLanguageModeFromStr(const std::string& stringBodyLanguageMode)
{
  animatedSpeechProxy->setBodyLanguageModeFromStr(stringBodyLanguageMode);
}

unsigned int
EmotionalAnimatedSpeech::getBodyLanguageMode()
{
  return animatedSpeechProxy->getBodyLanguageMode();
}

std::string
EmotionalAnimatedSpeech::getBodyLanguageModeToStr()
{
  return animatedSpeechProxy->getBodyLanguageModeToStr();
}

void
EmotionalAnimatedSpeech::addTagsToWords(const AL::ALValue& tagsToWords)
{
  //TODO Does not seem to be implemented in Aldebaran proxy
  //animatedSpeechProxy->addTagsToWords(tagsToWords);
}

void
EmotionalAnimatedSpeech::declareAnimationsPackage(const std::string& animationsPackage)
{
  //TODO Does not seem to be implemented in Aldebaran proxy
  //animatedSpeechProxy->declareAnimationsPackage(animationsPackage);
}

void
EmotionalAnimatedSpeech::declareTagForAnimations(const AL::ALValue& tagsToAnimations)
{
  //TODO Does not seem to be implemented in Aldebaran proxy
  //animatedSpeechProxy->declareTagForAnimations(tagsToAnimations);
}
