def getEmotionalProxy(proxyName):
    emotions = ALProxy("Emotion")
    adaptorName = emotions.getProxyName(proxyName)
    return ALProxy(adaptorName)

def getEmotionalMotion():
    return getEmotionalProxy("ALMotion");

def getEmotionalTTS():
    return getEmotionalProxy("ALTextToSpeech");

def getEmotionalAnimatedTTS():
    return getEmotionalProxy("ALAnimatedSpeech");

def getEmotionalLEDs():
    return getEmotionalProxy("ALLeds");
