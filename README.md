nao-emotional-framework
=======================

A framework to allow NAO applications to share an implementation of an emotional model and provide a standard means of modifying rebot behaviour in response to emotional state.

We make a distinction between the internal state of an emotional model and the external representation of emotional state. The external state should be simple, expressive and generic - it needs to describe only the instantaneous state of the robot not how or why it arrived at that state. In contrast the internal state of the model needs to be considerably richer as it needs to encode how and why the robot reached a given state and how current events will change that state.

The ALEmotion framework aims to allow models to manage a rich internal state whilst using a simple and generic external representation to allow a loose coupling with other behaviours.

##Components of a robot’s emotional system

We’ve broken an emotional system down into several components:
- **Application** - This is a NAO application/behaviour. It can be either unaware of emotional state and yet benefit from the robot’s eye colour, speech and movement being emotionally adapted or it can be aware of the robot’s emotional state and interact with it either by changing its behaviour based on the emotional state or feeding the model with emotionally significant events.
- **Model** - this is the component that decides and tracks what the robot is feeling based on internal and external events. The model may have other components such as short & long-term memory. Long-term memory will probably be visible outside of the model but that is not shown here.
- **Recognition** - these components detect emotionally significant input - for example is a person happy or sad based on voice tone or facial expression.
- **Expression** - these components express how the robot feels by altering movement, LED colour, body language and voice parameters. Currently these robot expressions are hard coded e.g. when “hello” is said the robot always gives a happy wave.
- **Transport** - this is the mechanism that exchanges emotional data between components. In practice this will be based on ALMemory and (possibly) some additional modules (see below).
- **Adaptors** - these components will dynamically express how the robot feels by altering movement, LED colour, body language and voice parameters. These robot expressions are driven by the emotional model.

##ALEmotion objectives

Our objectives for ALEmotion are :
- To allow different emotional models and personalities to be used on NAO as a plugin (or service) without having to make changes to other applications.
Emotional expression should be easy for developers to include - a developer should not have to work hard to allow the emotional state of the robot to show in his/her applications. For example the eye colour, speech settings and movement style of the robot should change according to the robot’s emotional state without requiring explicit action from the developer.
- To separate the internal state of the emotional model from the externally visible state. While there appears to be little agreement between different emotional models it does appear to be possible to encode enough information to express emotion using a few scalar values, for example VA (Valence & Arousal) or PAD (Pleasure Arousal Dominance).
- Use ALMemory and the existing events mechanism as they are probably the best way to share the external representation of the model (for example have memory keys /emotion/valence & /emotion/arousal).
- We may want to use multiple models so that we can model the state of the robot and that of other people. The actual models may not be of the same type but the external representation (eg VA or PAD) should be the same.
- We assume an emotional model is not the same as personality. It is probably desirable that people can choose a personality for the robot and it should be possible for a single model to allow different personalities or for different personalities to have different underlying models. In other words end-users probably will not care that "witty sarcastic robot" is implemented using one emotional model and "sweet good natured robot" is implemented using another model. That should be possible.

##Usage
The framework comes with three choreographe projects:
- **installer** - This is an interactive application that allows the native library that implements the emotional framework to be installed and uninstalled.
- **box library** - This contains a box that installs the helper functions into the global python scope to make them available to all choreographe boxes
- **demo** - A demo application that demonstrates how to replace the ALMotion, ALTextToSpeech and ALLeds proxies with the emotional adaptors.

The helper functions are the following:
- getEmotionalProxy(proxyName) - accepts an arbitrary module name and returns a proxy. Since Emotion.getProxyName() returns the proxy name unchanged if it is not wrapped by the framework it is safe to use getEmotionalProxy(proxyName) as a drop-in replacement for all invocations of ALProxy.
- getEmotionalMotion() - returns a proxy to the adapted ALMotion
- getEmotionalTTS() - returns a proxy to the adapted ALTextToSpeech
- getEmotionalAnimatedTTS() - returns a proxy to the adapted ALAnimatedSpeech
- getEmotionalLEDs() - returns a proxy to the adapted ALLeds

##ALMemory Usage
The framework uses the following ALMemory structure under the top-level "Emotion" key. The list contained in Emotion/Current is generated by the active emotional model.

- Emotion (top-level):

	+ Emotion/Current -> [valence, arousal] or [pleasure, arousal, dominance]
	+ Emotion/Mood -> [valence, arousal] or [pleasure, arousal, dominance]
	+ Emotion/Personality -> TBD
	+ Emotion/Parameters/EmotionsEnabled true/false (default = true)
	+ Emotion/Parameters/LEDS/RastaEyesEnabled true/false (defaut = false)

## Building
In order to build the emotional framework you need to have at least the following installed
- [cmake](http://www.cmake.org/)
- [qibuild](http://doc.aldebaran.com/qibuild/)
- [NAOqi SDK](https://community.aldebaran.com/en/resources/software) - in order to build the framework to run on your computer
- [NAOqi cross toolchain](https://community.aldebaran.com/en/resources/software) -  in order to build the framework to run on the robot

There are two helper scripts in the top-level of the project:
- make-local.sh - this configures qibuild to build the project to run locally (on the robot)
- make-remote.sh - this configures qibuild to make the project for remote (off robot) execution and then builds the project

These scripts require that the following environment variables are set:
- ROBOT_TOOLCHAIN - the name of the qibuild toolchain to use to build code to run on the robot
- PC_TOOLCHAIN - the name of the qibuild toolchain to use to build code to run on your computer (off robot)

To install the framework on the robot
- run make-local.sh - this builds the native components and copies them to the choreographe installer  project in the choreographe/installer directory
- open the installer project in choreographe and run it on your robot. If the installer finds the framework is already installed it will allow you to uninstall it. Currently the installer does not support upgrades so you'll need to do an uninstall followed by a re-install to upgrade to a newer version of the library

To run the framework off robot
- run make-remote.sh
- you can find the built components in build-${PC_TOOLCHAIN}/sdk/bin
- you can then run nao-emotional-framework --pip <robot address> You can also use the --pport option to specify the port to use if you need to use a port that is not the default 9559
