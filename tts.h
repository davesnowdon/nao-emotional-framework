#ifndef EMOTIONAL_TTS_H
# define EMOTIONAL_TTS_H

# include <iostream>
# include <alcommon/almodule.h>
# include <alproxies/altexttospeechproxy.h>

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
class EmotionalTextToSpeech : public AL::ALModule
{
public:
  EmotionalTextToSpeech(boost::shared_ptr<AL::ALBroker> broker);

  virtual ~EmotionalTextToSpeech();

  /**
   * Overloading ALModule::init().
   * This is called right after the module has been loaded
   */
  virtual void init();
    /// <summary>
    /// Outputs the languages installed on the system.
    /// </summary>
    /// <returns> Array of std::string that contains the languages installed on the system. </returns>
    std::vector<std::string> getAvailableLanguages();

    /// <summary>
    /// Outputs the available voices. The returned list contains the voice IDs.
    /// </summary>
    /// <returns>  Array of std::string containing the voices installed on the system. </returns>
    std::vector<std::string> getAvailableVoices();

    /// <summary>
    /// Returns the language currently used by the text-to-speech engine.
    /// </summary>
    /// <returns> Language of the current voice. </returns>
    std::string getLanguage();

    /// <summary>
    /// Returns the value of one of the voice parameters. The available parameters are: "pitchShift", "doubleVoice","doubleVoiceLevel" and "doubleVoiceTimeShift"
    /// </summary>
    /// <param name="pParameterName"> Name of the parameter. </param>
    /// <returns> Value of the specified parameter </returns>
    float getParameter(const std::string& pParameterName);

    /// <summary>
    /// Outputs all the languages supported (may be installed or not).
    /// </summary>
    /// <returns> Array of std::string that contains all the supported languages (may be installed or not). </returns>
    std::vector<std::string> getSupportedLanguages();

    /// <summary>
    /// Returns the voice currently used by the text-to-speech engine.
    /// </summary>
    /// <returns> Name of the current voice </returns>
    std::string getVoice();

    /// <summary>
    /// Fetches the current volume the text to speech.
    /// </summary>
    /// <returns> Volume (integer between 0 and 100). </returns>
    float getVolume();

    /// <summary>
    /// Loads a set of voice parameters defined in a xml file contained in the preferences folder.The name of the xml file must begin with ALTextToSpeech_Voice_
    /// </summary>
    /// <param name="pPreferenceName"> Name of the voice preference. </param>
    void loadVoicePreference(const std::string& pPreferenceName);

    /// <summary>
    /// Get the locale associate to the current language.
    /// </summary>
    /// <returns> A string with xx_XX format (region_country) </returns>
    std::string locale();

    /// <summary>
    /// Performs the text-to-speech operations : it takes a std::string as input and outputs a sound in both speakers. String encoding must be UTF8.
    /// </summary>
    /// <param name="stringToSay"> Text to say, encoded in UTF-8. </param>
    void say(const std::string& stringToSay);

    /// <summary>
    /// Performs the text-to-speech operations in a specific language: it takes a std::string as input and outputs a sound in both speakers. String encoding must be UTF8. Once the text is said, the language is set back to its initial value.
    /// </summary>
    /// <param name="stringToSay"> Text to say, encoded in UTF-8. </param>
    /// <param name="language"> Language used to say the text. </param>
    void say(const std::string& stringToSay, const std::string& language);

    /// <summary>
    /// Performs the text-to-speech operations: it takes a std::string as input and outputs the corresponding audio signal in the specified file.
    /// </summary>
    /// <param name="pStringToSay"> Text to say, encoded in UTF-8. </param>
    /// <param name="pFileName"> RAW file where to store the generated signal. The signal is encoded with a sample rate of 22050Hz, format S16_LE, 2 channels. </param>
    void sayToFile(const std::string& pStringToSay, const std::string& pFileName);

    /// <summary>
    /// Changes the language used by the Text-to-Speech engine. It automatically changes the voice used since each of them is related to a unique language. If you want that change to take effect automatically after reboot of your robot, refer to the robot web page (setting page).
    /// </summary>
    /// <param name="pLanguage"> Language name. Must belong to the languages available in TTS (can be obtained with the getAvailableLanguages method).  It should be an identifier std::string. </param>
    void setLanguage(const std::string& pLanguage);

    /// <summary>
    /// Sets a voice as the default voice for the corresponding language
    /// </summary>
    /// <param name="Language"> The language among those available on your robot as a String </param>
    /// <param name="Voice"> The voice among those available on your robot as a String </param>
    void setLanguageDefaultVoice(const std::string& Language, const std::string& Voice);

    /// <summary>
    /// Changes the parameters of the voice. The available parameters are:
    ///  	 pitchShift: applies a pitch shifting to the voice. The value indicates the ratio between the new fundamental frequencies and the old ones (examples: 2.0: an octave above, 1.5: a quint above). Correct range is (1.0 -- 4), or 0 to disable effect.
    ///  	 doubleVoice: adds a second voice to the first one. The value indicates the ratio between the second voice fundamental frequency and the first one. Correct range is (1.0 -- 4), or 0 to disable effect
    ///  	 doubleVoiceLevel: the corresponding value is the level of the double voice (1.0: equal to the main voice one). Correct range is (0 -- 4).
    ///  	 doubleVoiceTimeShift: the corresponding value is the delay between the double voice and the main one. Correct range is (0 -- 0.5)
    ///  If the effect value is not available, the effect parameter remains unchanged.
    /// </summary>
    /// <param name="pEffectName"> Name of the parameter. </param>
    /// <param name="pEffectValue"> Value of the parameter. </param>
    void setParameter(const std::string& pEffectName, const float& pEffectValue);

    /// <summary>
    /// Changes the voice used by the text-to-speech engine. The voice identifier must belong to the installed voices, that can be listed using the 'getAvailableVoices' method. If the voice is not available, it remains unchanged. No exception is thrown in this case. For the time being, only two voices are available by default : Kenny22Enhanced (English voice) and Julie22Enhanced (French voice)
    /// </summary>
    /// <param name="pVoiceID"> The voice (as a std::string). </param>
    void setVoice(const std::string& pVoiceID);

    /// <summary>
    /// Sets the volume of text-to-speech output.
    /// </summary>
    /// <param name="volume"> Volume (between 0.0 and 1.0). </param>
    void setVolume(const float& volume);

    /// <summary>
    /// This method stops the current and all the pending tasks immediately.
    /// </summary>
    void stopAll();

    typedef boost::shared_ptr<AL::ALTextToSpeechProxy> ALTextToSpeechProxyPtr;

private:
    ALTextToSpeechProxyPtr ttsProxy;
};
#endif // EMOTIONAL_TTS_H
