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
