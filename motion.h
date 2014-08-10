#ifndef EMOTIONAL_MOTION_H
# define EMOTIONAL_MOTION_H

# include <iostream>
# include <alcommon/almodule.h>
# include <alproxies/almotionproxy.h>

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
class EmotionalMotion : public AL::ALModule
{
public:
  EmotionalMotion(boost::shared_ptr<AL::ALBroker> broker);

  virtual ~EmotionalMotion();

  /**
   * Overloading ALModule::init().
   * This is called right after the module has been loaded
   */
  virtual void init();

    // todo: should deprecated methods be included?? - Currently not included to speed development.
    // todo: should events be included?? - Currently not included.
    // todo: should NAO and Pepper specific methods be differentiated from each other?? - Currently not.

    // Stiffness control API

    void wakeUp();

    void rest();

    bool robotIsWakeUp();

    void stiffnessInterpolation(const AL::ALValue& names, const AL::ALValue& stiffnessLists, const AL::ALValue& timeLists);

    void setStiffnesses(const AL::ALValue& names, const AL::ALValue& stiffnesses);

    std::vector<float> getStiffnesses(const AL::ALValue& jointName);

    // Joint control API

    void angleInterpolation(const AL::ALValue& names, const AL::ALValue& angleLists, const AL::ALValue& timeLists, const bool& isAbsolute);

    void angleInterpolationWithSpeed(const AL::ALValue& names, const AL::ALValue& targetAngles, const float& maxSpeedFraction);

    void angleInterpolationBezier(const std::vector<std::string>& jointNames, const AL::ALValue& times, const AL::ALValue& controlPoints);

    void setAngles(const AL::ALValue& names, const AL::ALValue& angles, const float& fractionMaxSpeed);

    void changeAngles(const AL::ALValue& names, const AL::ALValue& changes, const float& fractionMaxSpeed);

    std::vector<float> getAngles(const AL::ALValue& names, const bool& useSensors);

    void closeHand(const std::string& handName);

    void openHand(const std::string& handName);

    // Locomotion control API

    void move(const float& x, const float& y, const float& theta);

    void move(const float& x, const float& y, const float& theta, const AL::ALValue& moveConfig);

    void moveToward(const float& x, const float& y, const float& theta);

    void moveToward(const float& x, const float& y, const float& theta, const AL::ALValue& moveConfig);

    void moveTo(const float& x, const float& y, const float& theta);

    void moveTo(const float& x, const float& y, const float& theta, const AL::ALValue& moveConfig);

    void moveTo(const AL::ALValue& controlPoints);

    void moveTo(const AL::ALValue& controlPoints, const AL::ALValue& moveConfig);

    void moveTo(const float& x, const float& y, const float& theta, const float& pTime);

    void setFootSteps(const std::vector<std::string>& legName, const AL::ALValue& footSteps, const std::vector<float>& timeList, const bool& clearExisting);

    void setFootStepsWithSpeed(const std::vector<std::string>& legName, const AL::ALValue& footSteps, const std::vector<float>& fractionMaxSpeed, const bool& clearExisting);

    AL::ALValue getFootSteps();

    void moveInit();

    void waitUntilWalkIsFinished();

    void waitUntilMoveIsFinished();

    bool moveIsActive();

    void stopWalk();

    void stopMove();

    AL::ALValue getMoveConfig(const std::string& config);

    std::vector<float> getRobotPosition(const bool& useSensors);

    std::vector<float> getNextRobotPosition();

    std::vector<float> getRobotVelocity();

    bool getMoveArmsEnabled(const std::string& chainName);

    void setMoveArmsEnabled(const bool& leftArmEnable, const bool& rightArmEnable);

    // Cartesian control API

    void positionInterpolations(const AL::ALValue& effectorNames, const AL::ALValue& frames, const AL::ALValue& paths, const AL::ALValue& axisMasks, const AL::ALValue& relativeTimes);

    void setPositions(const AL::ALValue& effectorNames, const AL::ALValue& frame, const AL::ALValue& position, const float& fractionMaxSpeed, const AL::ALValue& axisMask);

    std::vector<float> getPosition(const std::string& name, const int& frame, const bool& useSensorValues);

    void transformInterpolations(const AL::ALValue& effectorNames, const AL::ALValue& frames, const AL::ALValue& paths, const AL::ALValue& axisMasks, const AL::ALValue& relativeTimes);

    void setTransforms(const std::string& effectorName, const int& frame, const std::vector<float>& transform, const float& fractionMaxSpeed, const int& axisMask);

    std::vector<float> getTransform(const std::string& name, const int& frame, const bool& useSensorValues);

    // Whole Body control API

    void wbEnable(const bool& isEnabled);

    void wbFootState(const std::string& stateName, const std::string& supportLeg);

    void wbEnableBalanceConstraint(const bool& isEnable, const std::string& supportLeg);

    void wbGoToBalance(const std::string& supportLeg, const float& duration);

    void wbEnableEffectorControl(const std::string& effectorName, const bool& isEnabled);

    void wbSetEffectorControl(const std::string& effectorName, const AL::ALValue& targetCoordinate);

    void wbEnableEffectorOptimization(const std::string& effectorName, const bool& isEnabled);

    // Self-collision avoidance API

    bool setCollisionProtectionEnabled(const std::string& ChainName, const bool& Enable);

    bool getCollisionProtectionEnabled(const std::string& ChainName);

    std::string isCollision(const std::string& ChainName);

    // External-collision avoidance API

    std::vector<float> getChainClosestObstaclePosition(const std::string& chainName, const int& frame);

    bool getExternalCollisionProtectionEnabled(const std::string& name);

    float getOrthogonalSecurityDistance();

    float getTangentialSecurityDistance();

    void setExternalCollisionProtectionEnabled(const std::string& name, const bool& enable);

    void setOrthogonalSecurityDistance(const float& distance);

    void setTangentialSecurityDistance(const float& distance);

    //Fall manager API

    void setFallManagerEnabled(const bool& enable);

    bool getFallManagerEnabled();

    // Smart Stiffness API

    void setSmartStiffnessEnabled(const bool& enable);

    bool getSmartStiffnessEnabled();

    // Diagnosis effect API

    void setDiagnosisEffectEnabled(const bool& enable);

    bool getDiagnosisEffectEnabled();

    // Push Recovery API

    void setPushRecoveryEnabled(const bool& enable);

    bool getPushRecoveryEnabled(void);

    // Idle API

    void setIdlePostureEnabled(const std::string& pChainName, const bool& pEnable);

    bool getIdlePostureEnabled(const std::string& pChainName);

    void setBreathEnabled(const std::string& pChainName, const bool& pEnable);

    bool getBreathEnabled(const std::string& pChainName);

    void setBreathConfig(const AL::ALValue& pConfig);

    AL::ALValue getBreathConfig();

    // General tools API

    bool areNotificationsEnabled();

    std::vector<std::string> getBodyNames(const std::string& name);

    std::vector<std::string> getSensorNames();

    AL::ALValue getLimits(const std::string& name);

    AL::ALValue getMotionCycleTime();

    AL::ALValue getRobotConfig();

    std::string getSummary();

    float getMass(const std::string& pName);

    std::vector<float> getCOM(const std::string& pName, const int& pSpace, const bool& pUseSensorValues);

    void setMotionConfig(const AL::ALValue& config);

    void setEnableNotifications(bool enable);

    // Motion task API

    AL::ALValue getTaskList();

    bool areResourcesAvailable(const std::vector<std::string>& resourceNames);

    bool killTask(const int& motionTaskID);

    void killTasksUsingResources(const std::vector<std::string>& resourceNames);

    void killMove();

    void killAll();

    typedef boost::shared_ptr<AL::ALMotionProxy> ALMotionProxyPtr;

private:
    ALMotionProxyPtr motionProxy;
};
#endif // EMOTIONAL_MOTION_H
