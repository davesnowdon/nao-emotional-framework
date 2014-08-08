#ifndef EMOTION_H
# define EMOTION_H

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
class Emotion : public AL::ALModule
{
public:
  Emotion(boost::shared_ptr<AL::ALBroker> broker,
           const std::string &name);

  virtual ~Emotion();

  /**
   * Overloading ALModule::init().
   * This is called right after the module has been loaded
   */
  virtual void init();

  // Return the name of the proxy to use instead of the named
  // standard proxy
  std::string getProxyName(const std::string& proxyName);
};
#endif // EMOTION_H
