#include "motion.h"

#include <iostream>
#include <alcommon/albroker.h>

EmotionalMotion::EmotionalMotion(boost::shared_ptr<AL::ALBroker> broker)
  : AL::ALModule(broker, MOTION_MODULE_ADAPTOR)
{
  // Describe the module here. This will appear on the webpage
  setModuleDescription("Emotionally modified motion");

  // // Pattern:
  // functionName("name", getName(), "description");
  // addParam("param", "");
  // setReturn("return", "");
  // BIND_METHOD(EmotionalMotion::name);

  functionName("wakeUp", getName(), "The robot wakes up: sets Motor on and, if needed, goes to initial position. For example, H25 or H21 sets the Stiffness on and keeps is current position.");
  BIND_METHOD(EmotionalMotion::wakeUp);

  functionName("rest", getName(), "The robot rests: goes to a relaxed and safe position and sets Motor off. For example, H25 or H21 goes to the Crouch posture and sets the Stiffness off.");
  BIND_METHOD(EmotionalMotion::rest);

  functionName("robotIsWakeUp", getName(), "description");
  addParam("param", "");
  setReturn("bool", "");
  BIND_METHOD(EmotionalMotion::robotIsWakeUp);

  functionName("stiffnessInterpolation", getName(), "Interpolates one or multiple joints to a targeted stiffness or along timed trajectories of stiffness. This is a blocking call.");
  addParam("names", "");
  addParam("stiffnessLists", "");
  addParam("timeLists", "");
  BIND_METHOD(EmotionalMotion::stiffnessInterpolation);

  functionName("setStiffnesses", getName(), "Sets the stiffness of one or more joints. This is a non-blocking call.");
  addParam("names", "");
  addParam("stiffnesses", "");
  BIND_METHOD(EmotionalMotion::setStiffnesses);

  functionName("getStiffnesses", getName(), "Gets stiffness of a joint or group of joints");
  addParam("jointName", "");
  setReturn("std::vector<float>", "");
  BIND_METHOD(EmotionalMotion::getStiffnesses);

  // Joint control API

  functionName("angleInterpolation", getName(), "Interpolates one or multiple joints to a target angle or along timed trajectories. This is a blocking call.");
  addParam("names", "");
  addParam("angleLists", "");
  addParam("angleLists", "");
  addParam("isAbsolute", "");
  BIND_METHOD(EmotionalMotion::angleInterpolation);

  functionName("angleInterpolationWithSpeed", getName(), "Interpolates one or multiple joints to a target angle, using a fraction of max speed. Only one target angle is allowed for each joint. This is a blocking call.");
  addParam("names", "");
  addParam("targetAngles", "");
  addParam("maxSpeedFraction", "");
  BIND_METHOD(EmotionalMotion::angleInterpolationWithSpeed);

  functionName("name", getName(), "Interpolates a sequence of timed angles for several motors using Bezier control points. This is a blocking call.");
  addParam("jointNames", "");
  addParam("times", "");
  addParam("controlPoints", "");
  BIND_METHOD(EmotionalMotion::getName);

  functionName("angleInterpolationBezier", getName(), "Sets angles. This is a non-blocking call.");
  addParam("names", "");
  addParam("angles", "");
  addParam("fractionMaxSpeed", "");
  BIND_METHOD(EmotionalMotion::angleInterpolationBezier);

  functionName("changeAngles", getName(), "Changes Angles. This is a non-blocking call.");
  addParam("names", "");
  addParam("changes", "");
  addParam("fractionMaxSpeed", "");
  BIND_METHOD(EmotionalMotion::changeAngles);

  functionName("getAngles", getName(), "Gets the angles of the joints");
  addParam("names", "");
  addParam("useSensors", "");
  setReturn("std::vector<float>", "");
  BIND_METHOD(EmotionalMotion::getAngles);

  functionName("closeHand", getName(), "Closes the hand, then cuts motor current to conserve energy. This is a blocking call.");
  addParam("handName", "");
  BIND_METHOD(EmotionalMotion::closeHand);

  functionName("openHand", getName(), "Opens the hand, then cuts motor current to conserve energy. This is a blocking call.");
  addParam("handName", "");
  BIND_METHOD(EmotionalMotion::openHand);

  // Locomotion control API

  functionName("move", getName(), "There are two overloads of this function. Makes the robot move at the given velocity, expressed in FRAME_ROBOT. This is a non-blocking call.");
  addParam("x", "The velocity along x axis [m.s-1].");
  addParam("y", "The velocity along y axis [m.s-1].");
  addParam("theta", "The velocity around z axis [rd.s-1].");
  AL::completeAndCheck<
    EmotionalMotion,
    const float&,
    const float&,
    const float&,
    void>
    (&EmotionalMotion::move, getCurrentMethodDescription());
  bindMethodOverload(AL::createFunctor<EmotionalMotion,
                     float,
                     float,
                     float,
                     void>
  (this, &EmotionalMotion::move));

  functionName("move", getName(), "Makes the robot move at the given velocity, expressed in FRAME_ROBOT, with a move configuration. This is a non-blocking call.");
  addParam("x", "The velocity along x axis [m.s-1].");
  addParam("y", "The velocity along y axis [m.s-1].");
  addParam("theta", "The velocity around z axis [rd.s-1].");
  addParam("moveConfig", "");
  AL::completeAndCheck<EmotionalMotion,
                       const float&,
                       const float&,
                       const float&,
                       const AL::ALValue&,
                       void>
    (&EmotionalMotion::move, getCurrentMethodDescription());
  bindMethodOverload(AL::createFunctor<EmotionalMotion,
                     float,
                     float,
                     float,
                     AL::ALValue,
                     void>
  (this, &EmotionalMotion::move));

  functionName("moveToward", getName(), "There are two overloads of this function. Makes the robot move at the given normalized velocity, expressed in FRAME_ROBOT. This is a non-blocking call.");
  addParam("x", "");
  addParam("y", "");
  addParam("theta", "");
  AL::completeAndCheck<EmotionalMotion,
                       const float&,
                       const float&,
                       const float&,
                       void>
    (&EmotionalMotion::moveToward, getCurrentMethodDescription());
  bindMethodOverload(AL::createFunctor<EmotionalMotion,
                     float,
                     float,
                     float,
                     void>
  (this, &EmotionalMotion::moveToward));

  functionName("moveToward", getName(), "There are two overloads of this function. Makes the robot move to the given pose in the ground plane, relative to FRAME_ROBOT. This is a blocking call.");
  addParam("x", "");
  addParam("y", "");
  addParam("theta", "");
  addParam("moveConfig", "");
  AL::completeAndCheck<EmotionalMotion,
                       const float&,
                       const float&,
                       const float&,
                       const AL::ALValue&,
                       void>
    (&EmotionalMotion::moveToward, getCurrentMethodDescription());
  bindMethodOverload(AL::createFunctor<EmotionalMotion,
                     float,
                     float,
                     float,
                     AL::ALValue,
                     void>
  (this, &EmotionalMotion::moveToward));

  functionName("moveTo", getName(), "Makes the robot move to the given pose in the ground plane, relative to FRAME_ROBOT, with custom move configuration. This is a blocking call.");
  addParam("x", "");
  addParam("y", "");
  addParam("theta", "");
  AL::completeAndCheck<EmotionalMotion,
                       const float&,
                       const float&,
                       const float&,
                       void>
    (&EmotionalMotion::moveTo, getCurrentMethodDescription());
  bindMethodOverload(AL::createFunctor<EmotionalMotion,
                     float,
                     float,
                     float,
                     void>
  (this, &EmotionalMotion::moveTo));


  functionName("moveTo", getName(), "Makes the robot move to the given pose in the ground plane, relative to FRAME_ROBOT, with custom move configuration. This is a blocking call.");
  addParam("x", "");
  addParam("y", "");
  addParam("theta", "");
  addParam("moveConfig", "");
  AL::completeAndCheck<EmotionalMotion,
                       const float&,
                       const float&,
                       const float&,
                       const AL::ALValue&,
                       void>
    (&EmotionalMotion::moveTo, getCurrentMethodDescription());
  bindMethodOverload(AL::createFunctor<EmotionalMotion,
                     float,
                     float,
                     float,
                     AL::ALValue,
                     void>
  (this, &EmotionalMotion::moveTo));

  functionName("moveTo", getName(), "Makes the robot move to the given pose in the ground plane, relative to FRAME_ROBOT, while passing through check points. This is a blocking call.");
  addParam("controlPoints", "");
  AL::completeAndCheck<EmotionalMotion,
                       const AL::ALValue&,
                       void>
    (&EmotionalMotion::moveTo, getCurrentMethodDescription());
  bindMethodOverload(AL::createFunctor<EmotionalMotion,
                     AL::ALValue,
                     void>
  (this, &EmotionalMotion::moveTo));

  functionName("moveTo", getName(), "Makes the robot move to the given pose in the ground plane, relative to FRAME_ROBOT, while passing through check points with custom move configuration. This is a blocking call.");
  addParam("controlPoints", "");
  addParam("moveConfig", "");
  AL::completeAndCheck<EmotionalMotion,
                       const AL::ALValue&,
                       const AL::ALValue&,
                       void>
    (&EmotionalMotion::moveTo, getCurrentMethodDescription());
  bindMethodOverload(AL::createFunctor<EmotionalMotion,
                     AL::ALValue,
                     AL::ALValue,
                     void>
  (this, &EmotionalMotion::moveTo));

  functionName("moveTo", getName(), "Makes the robot move to the relative position (x, y, theta) in pTime.");
  addParam("x", "");
  addParam("y", "");
  addParam("theta", "");
  addParam("pTime", "");
  AL::completeAndCheck<EmotionalMotion,
                       const float&,
                       const float&,
                       const float&,
                       const float&,
                       void>
    (&EmotionalMotion::moveTo, getCurrentMethodDescription());
  bindMethodOverload(AL::createFunctor<EmotionalMotion,
                     float,
                     float,
                     float,
                     float,
                     void>
  (this, &EmotionalMotion::moveTo));

  functionName("setFootSteps", getName(), "Makes the robot do foot step planner. This is a non-blocking call.");
  addParam("legName", "");
  addParam("footSteps", "");
  addParam("timeList", "");
  addParam("clearExisting", "");
  BIND_METHOD(EmotionalMotion::setFootSteps);

  functionName("setFootStepsWithSpeed", getName(), "Makes the robot do foot step planner with speed. This is a blocking call.");
  addParam("legName", "");
  addParam("footSteps", "");
  addParam("fractionMaxSpeed", "");
  addParam("clearExisting", "");
  BIND_METHOD(EmotionalMotion::setFootStepsWithSpeed);

  functionName("getFootSteps", getName(), "Get the actual foot steps vector. This is a non-blocking call.");
  setReturn("AL::ALValue", "");
  BIND_METHOD(EmotionalMotion::getFootSteps);

  functionName("moveInit", getName(), "Initializes the move process. Checks the robot pose and takes a right posture. This is blocking called.");
  BIND_METHOD(EmotionalMotion::moveInit);

  functionName("waitUntilWalkIsFinished", getName(), "Waits until the WalkTask is finished: this method can be used to block your script/code execution until the walk task is totally finished.");
  BIND_METHOD(EmotionalMotion::waitUntilWalkIsFinished);

  functionName("waitUntilMoveIsFinished", getName(), "Waits until the MoveTask is finished: this method can be used to block your script/code execution until the move task is totally finished.");
  BIND_METHOD(EmotionalMotion::waitUntilMoveIsFinished);

  functionName("moveIsActive", getName(), "description");
  setReturn("bool", "");
  BIND_METHOD(EmotionalMotion::moveIsActive);

  functionName("stopWalk", getName(), "Stops Walk task at next double support: this method will end the walk task less brutally than killWalk but more quickly than move(0.0, 0.0, 0.0).");
  BIND_METHOD(EmotionalMotion::stopWalk);

  functionName("stopMove", getName(), "Stops Move task at next double support: this method will end the move task less brutally than killMove but more quickly than move(0.0, 0.0, 0.0).");
  BIND_METHOD(EmotionalMotion::stopMove);

  functionName("getMoveConfig", getName(), "Gets the move config (“MaxStepX”, “MaxStepY”, “MaxStepTheta”, “MaxStepFrequency”, “StepHeight”, “TorsoWx”, “TorsoWy”).");
  addParam("config", "");
  setReturn("AL::ALValue", "");
  BIND_METHOD(EmotionalMotion::getMoveConfig);

  functionName("getRobotPosition", getName(), "Gets the World Absolute Robot Position.");
  addParam("useSensors", "");
  setReturn("std::vector<float>", "");
  BIND_METHOD(EmotionalMotion::getRobotPosition);

  functionName("getNextRobotPosition", getName(), "Gets the World Absolute next Robot Position.");
  setReturn("std::vector<float>", "");
  BIND_METHOD(EmotionalMotion::getNextRobotPosition);

  functionName("getRobotVelocity", getName(), "Gets the Absolute Robot Velocity, expressed in FRAME_ROBOT.");
  setReturn("std::vector<float>", "");
  BIND_METHOD(EmotionalMotion::getRobotVelocity);

  functionName("getMoveArmsEnabled", getName(), "Gets if Arms Motions are enabled during the Move Process.");
  addParam("chainName", "");
  setReturn("bool", "");
  BIND_METHOD(EmotionalMotion::getMoveArmsEnabled);

  functionName("setMoveArmsEnabled", getName(), "Sets if Arms Motions are enabled during the Move Process.");
  addParam("leftArmEnable", "");
  addParam("rightArmEnable", "");
  BIND_METHOD(EmotionalMotion::setMoveArmsEnabled);

  // Cartesian control API

  functionName("positionInterpolations", getName(), "There are two overloads of this function. Moves end-effectors to the given positions and orientations over time. This is a blocking call.");
  addParam("effectorNames", "");
  addParam("frames", "");
  addParam("paths", "");
  addParam("axisMasks", "");
  addParam("relativeTimes", "");
  BIND_METHOD(EmotionalMotion::positionInterpolations);

  functionName("setPositions", getName(), "Moves an end-effector to the given position and orientation. This is a non-blocking call.");
  addParam("effectorNames", "");
  addParam("frame", "");
  addParam("position", "");
  addParam("fractionMaxSpeed", "");
  addParam("axisMask", "");
  BIND_METHOD(EmotionalMotion::setPositions);

  functionName("getPosition", getName(), "Gets a Position relative to the FRAME. Axis definition: the x axis is positive toward the robot’s front, the y from right to left and the z is vertical. The angle convention of Position6D is Rot_z(wz).Rot_y(wy).Rot_x(wx).");
  addParam("name", "");
  addParam("frame", "");
  addParam("useSensorValues", "");
  setReturn("std::vector<float>", "");
  BIND_METHOD(EmotionalMotion::getPosition);

  functionName("transformInterpolations", getName(), "There are two overloads of this function. Moves end-effector to the given transforms over time. This is a blocking call.");
  addParam("effectorNames", "");
  addParam("frames", "");
  addParam("paths", "");
  addParam("axisMasks", "");
  addParam("relativeTimes", "");
  BIND_METHOD(EmotionalMotion::transformInterpolations);

  functionName("setTransforms", getName(), "Moves an end-effector to the given position and orientation transform. This is a non-blocking call.");
  addParam("effectorName", "");
  addParam("frame", "");
  addParam("transform", "");
  addParam("fractionMaxSpeed", "");
  addParam("axisMask", "");
  BIND_METHOD(EmotionalMotion::setTransforms);

  functionName("getTransform", getName(), "Gets an Homogeneous Transform relative to the FRAME. Axis definition: the x axis is positive toward the robot’s front, the y from right to left and the z is vertical.");
  addParam("name", "");
  addParam("frame", "");
  addParam("useSensorValues", "");
  setReturn("std::vector<float>", "");
  BIND_METHOD(EmotionalMotion::getTransform);

  // Whole Body control API

  functionName("wbEnable", getName(), "Enables Whole Body Balancer. It’s a Generalized Inverse Kinematics which deals with Cartesian control, balance, redundancy and task priority. The main goal is to generate and stabilized consistent motions without precomputed trajectories and adapt the behavior of the robot to the situation. The generalized inverse kinematic problem takes in account equality constraints (keep foot fix), inequality constraints (joint limits, balance, ...) and quadratic minimization (Cartesian / articular desired trajectories). We solve each step a quadratic programming on the robot.");
  addParam("isEnabled", "");
  BIND_METHOD(EmotionalMotion::wbEnable);

  functionName("wbFootState", getName(), "Sets the state of the foot (or feet): fixed foot, constrained in a plane or free.");
  addParam("stateName", "");
  addParam("supportLeg", "");
  BIND_METHOD(EmotionalMotion::wbFootState);

  functionName("wbEnableBalanceConstraint", getName(), "Enables to keep balance in support polygon.");
  addParam("isEnable", "");
  addParam("supportLeg", "");
  BIND_METHOD(EmotionalMotion::wbEnableBalanceConstraint);

  functionName("wbGoToBalance", getName(), "Advanced Whole Body API: Com go to a desired support polygon. This is a blocking call. Use with caution: make sure the starting pose is consistent with the targeted pose. Starting form Init pose is the safer way to use it.");
  addParam("supportLeg", "");
  addParam("duration", "");
  BIND_METHOD(EmotionalMotion::wbGoToBalance);

  functionName("wbEnableEffectorControl", getName(), "Enables whole body Cartesian control of an effector.");
  addParam("effectorName", "");
  addParam("isEnabled", "");
  BIND_METHOD(EmotionalMotion::wbEnableEffectorControl);

  functionName("wbSetEffectorControl", getName(), "Sets a new target for controlled effector. This is a non-blocking call.");
  addParam("effectorName", "");
  addParam("targetCoordinate", "");
  BIND_METHOD(EmotionalMotion::wbSetEffectorControl);

  functionName("wbEnableEffectorOptimization", getName(), "Enables whole body Cartesian optimization of an effector.");
  addParam("effectorName", "");
  addParam("isEnabled", "");
  BIND_METHOD(EmotionalMotion::wbEnableEffectorOptimization);

  // Self-collision avoidance API

  functionName("setCollisionProtectionEnabled", getName(), "Enable/Disable Anti-collision protection of the arms of the robot. Use ALMotionProxy::isCollision() to know if a chain is in collision and can be inactivated.");
  addParam("ChainName", "");
  addParam("Enable", "");
  setReturn("bool", "");
  BIND_METHOD(EmotionalMotion::setCollisionProtectionEnabled);

  functionName("getCollisionProtectionEnabled", getName(), "Allow to know if the collision protection is activated on the given chain.");
  addParam("ChainName", "");
  setReturn("bool", "");
  BIND_METHOD(EmotionalMotion::getCollisionProtectionEnabled);

  functionName("isCollision", getName(), "Give the collision state of a chain. If a chain has a collision state “none” or “near”, it could be deactivates.");
  addParam("ChainName", "");
  setReturn("std::string", "");
  BIND_METHOD(EmotionalMotion::isCollision);

  // External-collision avoidance API

  functionName("getChainClosestObstaclePosition", getName(), "Gets, for a specified chain, the position, relative to the specified frame, of the closest obstacle.");
  addParam("chainName", "");
  addParam("frame", "");
  setReturn("std::vector<float>", "");
  BIND_METHOD(EmotionalMotion::getChainClosestObstaclePosition);

  functionName("getExternalCollisionProtectionEnabled", getName(), "Checks if the external collision protection is activated on the given name.");
  addParam("name", "");
  setReturn("bool", "");
  BIND_METHOD(EmotionalMotion::getExternalCollisionProtectionEnabled);

  functionName("getOrthogonalSecurityDistance", getName(), "Gets the current orthogonal security distance used to check dangerous obstacles.");
  setReturn("float", "");
  BIND_METHOD(EmotionalMotion::getOrthogonalSecurityDistance);

  functionName("getTangentialSecurityDistance", getName(), "Gets the current tangential security distance used to check dangerous obstacles.");
  setReturn("float", "");
  BIND_METHOD(EmotionalMotion::getTangentialSecurityDistance);

  functionName("setExternalCollisionProtectionEnabled", getName(), "Enable/disable external collision protection of the robot.");
  addParam("name", "");
  addParam("enable", "");
  BIND_METHOD(EmotionalMotion::setExternalCollisionProtectionEnabled);

  functionName("setOrthogonalSecurityDistance", getName(), "Defines the orthogonal security distance.");
  addParam("distance", "");
  BIND_METHOD(EmotionalMotion::setOrthogonalSecurityDistance);

  functionName("setTangentialSecurityDistance", getName(), "Defines the tangential security distance.");
  addParam("distance", "");
  BIND_METHOD(EmotionalMotion::setTangentialSecurityDistance);

  //Fall manager API

  functionName("setFallManagerEnabled", getName(), "Enable/disable the fall manager reflex, but only if allowed by the owner. If not allowed, an exception is thrown.");
  addParam("enable", "");
  BIND_METHOD(EmotionalMotion::setFallManagerEnabled);

  functionName("getFallManagerEnabled", getName(), "Allow to know if the fall manager reflex is activated.");
  setReturn("bool", "");
  BIND_METHOD(EmotionalMotion::getFallManagerEnabled);

  // Smart Stiffness API

  functionName("setSmartStiffnessEnabled", getName(), "Enable or Disable the smart stiffness reflex for all the joints (True by default). The update takes one motion cycle.");
  addParam("enable", "");
  setReturn("bool", "");
  BIND_METHOD(EmotionalMotion::setSmartStiffnessEnabled);

  functionName("getSmartStiffnessEnabled", getName(), "Allow to know if the smart stiffness reflex is activated.");
  BIND_METHOD(EmotionalMotion::getSmartStiffnessEnabled);

  // Diagnosis effect API

  functionName("setDiagnosisEffectEnabled", getName(), "Enable or Disable the diagnosis reflex.");
  addParam("enable", "");
  BIND_METHOD(EmotionalMotion::setDiagnosisEffectEnabled);

  functionName("getDiagnosisEffectEnabled", getName(), "Allow to know if the diagnosis reflex is activated.");
  setReturn("bool", "");
  BIND_METHOD(EmotionalMotion::getDiagnosisEffectEnabled);

  // Push Recovery API

  functionName("setPushRecoveryEnabled", getName(), "Enable/disable the push-recovery reflex of the robot, but only if allowed by the owner. If not allowed, an exception is thrown.");
  addParam("enable", "");
  BIND_METHOD(EmotionalMotion::setPushRecoveryEnabled);

  functionName("getPushRecoveryEnabled", getName(), "Allow to know if the push recovery protection is activated.");
  addParam("void", "");
  setReturn("bool", "");
  BIND_METHOD(EmotionalMotion::getPushRecoveryEnabled);

  // Idle API

  functionName("setIdlePostureEnabled", getName(), "Starts or stops idle posture control on a chain.");
  addParam("pChainName", "");
  addParam("pEnable", "");
  BIND_METHOD(EmotionalMotion::setIdlePostureEnabled);

  functionName("getIdlePostureEnabled", getName(), "Gets the status of idle posture control on a chain.");
  addParam("pChainName", "");
  setReturn("bool", "");
  BIND_METHOD(EmotionalMotion::getIdlePostureEnabled);

  functionName("setBreathEnabled", getName(), "Starts or stops breathing animation on a chain.");
  addParam("pChainName", "");
  addParam("pEnable", "");
  BIND_METHOD(EmotionalMotion::setBreathEnabled);

  functionName("getBreathEnabled", getName(), "Gets the status of breathing animation on a chain.");
  addParam("pChainName", "");
  setReturn("bool", "");
  BIND_METHOD(EmotionalMotion::getBreathEnabled);

  functionName("setBreathConfig", getName(), "Configures the breathing animation.");
  addParam("pConfig", "");
  BIND_METHOD(EmotionalMotion::setBreathConfig);

  functionName("getBreathConfig", getName(), "This function gets the current breathing configuration.");
  setReturn("AL::ALValue", "");
  BIND_METHOD(EmotionalMotion::getBreathConfig);

  // General tools API

  functionName("areNotificationsEnabled", getName(), "Get notifications status. Return true if notifications are active.");
  setReturn("bool", "");
  BIND_METHOD(EmotionalMotion::areNotificationsEnabled);

  functionName("getBodyNames", getName(), "Gets the names of all the joints in the collection.");
  addParam("name", "");
  setReturn("std::vector<std::string>", "");
  BIND_METHOD(EmotionalMotion::getBodyNames);

  functionName("getSensorNames", getName(), "Gets the list of sensors supported on your robot.");
  setReturn("std::vector<std::string>", "");
  BIND_METHOD(EmotionalMotion::getSensorNames);

  functionName("getLimits", getName(), "Get the minAngle (rad), maxAngle (rad), maxVelocity (rad.s-1) and maxTorque (N.m). for a given joint or actuator in the body.");
  addParam("name", "");
  setReturn("AL::ALValue", "");
  BIND_METHOD(EmotionalMotion::getLimits);

  functionName("getMotionCycleTime", getName(), "Get the motion cycle time in milliseconds.");
  setReturn("AL::ALValue", "");
  BIND_METHOD(EmotionalMotion::getMotionCycleTime);

  functionName("getRobotConfig", getName(), "Get the robot configuration.");
  setReturn("AL::ALValue", "");
  BIND_METHOD(EmotionalMotion::getRobotConfig);

  functionName("getSummary", getName(), "Returns a string representation of the Model’s state");
  setReturn("std::string", "");
  BIND_METHOD(EmotionalMotion::getSummary);

  functionName("getMass", getName(), "Gets the mass of a joint, chain, “Body” or “Joints”.");
  addParam("pName", "");
  setReturn("float", "");
  BIND_METHOD(EmotionalMotion::getMass);

  functionName("getCOM", getName(), "Gets the COM of a joint, chain, “Body” or “Joints”.");
  addParam("pName", "");
  addParam("pSpace", "");
  addParam("pUseSensorValues", "");
  setReturn("std::vector<float>", "");
  BIND_METHOD(EmotionalMotion::getCOM);

  functionName("setMotionConfig", getName(), "Internal Use.");
  addParam("config", "");
  BIND_METHOD(EmotionalMotion::setMotionConfig);

  functionName("setEnableNotifications", getName(), "Enable / Disable notifications.");
  addParam("enable", "");
  BIND_METHOD(EmotionalMotion::setEnableNotifications);

  // Motion task API

  functionName("getTaskList", getName(), "Gets an ALValue structure describing the tasks in the Task List");
  setReturn("AL::ALValue", "");
  BIND_METHOD(EmotionalMotion::getTaskList);

  functionName("areResourcesAvailable", getName(), "Returns true if all the desired resources are available. Only motion API’s‘ blocking call takes resources.");
  addParam("resourceNames", "");
  setReturn("bool", "");
  BIND_METHOD(EmotionalMotion::areResourcesAvailable);

  functionName("killTask", getName(), "Kills a motion task.");
  addParam("motionTaskID", "");
  setReturn("bool", "");
  BIND_METHOD(EmotionalMotion::killTask);

  functionName("killTasksUsingResources", getName(), "Kills all tasks that use any of the resources given. Only motion API’s‘ blocking call takes resources and can be killed.");
  addParam("resourceNames", "");
  BIND_METHOD(EmotionalMotion::killTasksUsingResources);

  functionName("killMove", getName(), "Emergency Stop on Move task: this method will end the move task brutally, without attempting to return to a balanced state. If the robot has one foot in the air, he could easily fall.");
  BIND_METHOD(EmotionalMotion::killMove);

  functionName("killAll", getName(), "Kills all tasks.");
  BIND_METHOD(EmotionalMotion::killAll);

  // TODO add error checking for proxy creation
  motionProxy = ALMotionProxyPtr(new AL::ALMotionProxy(broker));
}

EmotionalMotion::~EmotionalMotion()
{
}

void
EmotionalMotion::init()
{
}

void
EmotionalMotion::wakeUp()
{
  motionProxy->wakeUp();
}

void
EmotionalMotion::rest()
{
  motionProxy->rest();
}

bool
EmotionalMotion::robotIsWakeUp()
{
  return motionProxy->robotIsWakeUp();
}

void
EmotionalMotion::stiffnessInterpolation(const AL::ALValue& names, const AL::ALValue& stiffnessLists, const AL::ALValue& timeLists)
{
  motionProxy->stiffnessInterpolation(names, stiffnessLists, timeLists);
}

void
EmotionalMotion::setStiffnesses(const AL::ALValue& names, const AL::ALValue& stiffnesses)
{
  motionProxy->setStiffnesses(names, stiffnesses);
}

std::vector<float>
EmotionalMotion::getStiffnesses(const AL::ALValue& jointName)
{
  return motionProxy->getStiffnesses(jointName);
}

// Joint control API

void
EmotionalMotion::angleInterpolation(const AL::ALValue& names, const AL::ALValue& angleLists, const AL::ALValue& timeLists, const bool& isAbsolute)
{
  motionProxy->angleInterpolation(names, angleLists, timeLists, isAbsolute);
}

void
EmotionalMotion::angleInterpolationWithSpeed(const AL::ALValue& names, const AL::ALValue& targetAngles, const float& maxSpeedFraction)
{
  motionProxy->angleInterpolationWithSpeed(names, targetAngles, maxSpeedFraction);
}

void
EmotionalMotion::angleInterpolationBezier(const std::vector<std::string>& jointNames, const AL::ALValue& times, const AL::ALValue& controlPoints)
{
  motionProxy->angleInterpolationBezier(jointNames, times, controlPoints);
}

void
EmotionalMotion::setAngles(const AL::ALValue& names, const AL::ALValue& angles, const float& fractionMaxSpeed)
{
  motionProxy->setAngles(names, angles, fractionMaxSpeed);
}

void
EmotionalMotion::changeAngles(const AL::ALValue& names, const AL::ALValue& changes, const float& fractionMaxSpeed)
{
  motionProxy->changeAngles(names, changes, fractionMaxSpeed);
}

std::vector<float>
EmotionalMotion::getAngles(const AL::ALValue& names, const bool& useSensors)
{
  return motionProxy->getAngles(names, useSensors);
}

void
EmotionalMotion::closeHand(const std::string& handName)
{
  motionProxy->closeHand(handName);
}

void
EmotionalMotion::openHand(const std::string& handName)
{
  motionProxy->openHand(handName);
}

// Locomotion control API

void
EmotionalMotion::move(const float& x, const float& y, const float& theta)
{
  motionProxy->move(x, y, theta);
}

void
EmotionalMotion::move(const float& x, const float& y, const float& theta, const AL::ALValue& moveConfig)
{
  motionProxy->move(x, y, theta, moveConfig);
}

void
EmotionalMotion::moveToward(const float& x, const float& y, const float& theta)
{
  motionProxy->moveToward(x, y, theta);
}

void
EmotionalMotion::moveToward(const float& x, const float& y, const float& theta, const AL::ALValue& moveConfig)
{
  motionProxy->moveToward(x, y, theta, moveConfig);
}

void
EmotionalMotion::moveTo(const float& x, const float& y, const float& theta)
{
  motionProxy->moveTo(x, y, theta);
}

void
EmotionalMotion::moveTo(const float& x, const float& y, const float& theta, const AL::ALValue& moveConfig)
{
  motionProxy->moveTo(x, y, theta, moveConfig);
}

void
EmotionalMotion::moveTo(const AL::ALValue& controlPoints)
{
  motionProxy->moveTo(controlPoints);
}

void
EmotionalMotion::moveTo(const AL::ALValue& controlPoints, const AL::ALValue& moveConfig)
{
  motionProxy->moveTo(controlPoints, moveConfig);
}

void
EmotionalMotion::moveTo(const float& x, const float& y, const float& theta, const float& pTime)
{
  motionProxy->moveTo(x, y, theta, pTime);
}

void
EmotionalMotion::setFootSteps(const std::vector<std::string>& legName, const AL::ALValue& footSteps, const std::vector<float>& timeList, const bool& clearExisting)
{
  motionProxy->setFootSteps(legName, footSteps, timeList, clearExisting);
}

void
EmotionalMotion::setFootStepsWithSpeed(const std::vector<std::string>& legName, const AL::ALValue& footSteps, const std::vector<float>& fractionMaxSpeed, const bool& clearExisting)
{
  motionProxy->setFootStepsWithSpeed(legName, footSteps, fractionMaxSpeed, clearExisting);
}

AL::ALValue
EmotionalMotion::getFootSteps()
{
  return motionProxy->getFootSteps();
}

void
EmotionalMotion::moveInit()
{
  motionProxy->moveInit();
}

void
EmotionalMotion::waitUntilWalkIsFinished()
{
  motionProxy->waitUntilWalkIsFinished();
}

void
EmotionalMotion::waitUntilMoveIsFinished()
{
  motionProxy->waitUntilMoveIsFinished();
}


bool
EmotionalMotion::moveIsActive()
{
  return motionProxy->moveIsActive();
}

void
EmotionalMotion::stopWalk()
{
  motionProxy->stopWalk();
}

void
EmotionalMotion::stopMove()
{
  motionProxy->stopMove();
}

AL::ALValue
EmotionalMotion::getMoveConfig(const std::string& config)
{
  return motionProxy->getMoveConfig(config);
}

std::vector<float>
EmotionalMotion::getRobotPosition(const bool& useSensors)
{
  return motionProxy->getRobotPosition(useSensors);
}

std::vector<float>
EmotionalMotion::getNextRobotPosition()
{
  return motionProxy->getNextRobotPosition();
}

std::vector<float>
EmotionalMotion::getRobotVelocity()
{
  return motionProxy->getRobotVelocity();
}

bool
EmotionalMotion::getMoveArmsEnabled(const std::string& chainName)
{
  return motionProxy->getMoveArmsEnabled(chainName);
}

void
EmotionalMotion::setMoveArmsEnabled(const bool& leftArmEnable, const bool& rightArmEnable)
{
  motionProxy->setMoveArmsEnabled(leftArmEnable, rightArmEnable);
}

// Cartesian control API

void
EmotionalMotion::positionInterpolations(const AL::ALValue& effectorNames, const AL::ALValue& frames, const AL::ALValue& paths, const AL::ALValue& axisMasks, const AL::ALValue& relativeTimes)
{
  motionProxy->positionInterpolations(effectorNames, frames, paths, axisMasks, relativeTimes);
}

void
EmotionalMotion::setPositions(const AL::ALValue& effectorNames, const AL::ALValue& frame, const AL::ALValue& position, const float& fractionMaxSpeed, const AL::ALValue& axisMask)
{
  motionProxy->setPositions(effectorNames, frame, position, fractionMaxSpeed, axisMask);
}

std::vector<float>
EmotionalMotion::getPosition(const std::string& name, const int& frame, const bool& useSensorValues)
{
  return motionProxy->getPosition(name, frame, useSensorValues);
}

void
EmotionalMotion::transformInterpolations(const AL::ALValue& effectorNames, const AL::ALValue& frames, const AL::ALValue& paths, const AL::ALValue& axisMasks, const AL::ALValue& relativeTimes)
{
  motionProxy->transformInterpolations(effectorNames, frames, paths, axisMasks, relativeTimes);
}

void
EmotionalMotion::setTransforms(const std::string& effectorName, const int& frame, const std::vector<float>& transform, const float& fractionMaxSpeed, const int& axisMask)
{
  motionProxy->setTransforms(effectorName, frame, transform, fractionMaxSpeed, axisMask);
}

std::vector<float>
EmotionalMotion::getTransform(const std::string& name, const int& frame, const bool& useSensorValues)
{
  return motionProxy->getTransform(name, frame, useSensorValues);
}

// Whole Body control API

void
EmotionalMotion::wbEnable(const bool& isEnabled)
{
  motionProxy->wbEnable(isEnabled);
}

void
EmotionalMotion::wbFootState(const std::string& stateName, const std::string& supportLeg)
{
  motionProxy->wbFootState(stateName, supportLeg);
}

void
EmotionalMotion::wbEnableBalanceConstraint(const bool& isEnable, const std::string& supportLeg)
{
  motionProxy->wbEnableBalanceConstraint(isEnable, supportLeg);
}

void
EmotionalMotion::wbGoToBalance(const std::string& supportLeg, const float& duration)
{
  motionProxy->wbGoToBalance(supportLeg, duration);
}

void
EmotionalMotion::wbEnableEffectorControl(const std::string& effectorName, const bool& isEnabled)
{
  motionProxy->wbEnableEffectorControl(effectorName, isEnabled);
}

void
EmotionalMotion::wbSetEffectorControl(const std::string& effectorName, const AL::ALValue& targetCoordinate)
{
  motionProxy->wbSetEffectorControl(effectorName, targetCoordinate);
}

void
EmotionalMotion::wbEnableEffectorOptimization(const std::string& effectorName, const bool& isEnabled)
{
  motionProxy->wbEnableEffectorOptimization(effectorName, isEnabled);
}

// Self-collision avoidance API

bool
EmotionalMotion::setCollisionProtectionEnabled(const std::string& chainName, const bool& enable)
{
  return motionProxy->setCollisionProtectionEnabled(chainName, enable);
}

bool
EmotionalMotion::getCollisionProtectionEnabled(const std::string& chainName)
{
  return motionProxy->getCollisionProtectionEnabled(chainName);
}

std::string
EmotionalMotion::isCollision(const std::string& chainName)
{
  return motionProxy->isCollision(chainName);
}

// External-collision avoidance API

std::vector<float>
EmotionalMotion::getChainClosestObstaclePosition(const std::string& chainName, const int& frame)
{
  // TODO Issue #13 Resolve missing functions in ALMotionProxy
  return std::vector<float>();
  //return motionProxy->getChainClosestObstaclePosition(chainName, frame);
}

bool
EmotionalMotion::getExternalCollisionProtectionEnabled(const std::string& name)
{
  // TODO Issue #13 Resolve missing functions in ALMotionProxy
  return false;
  //return motionProxy->getExternalCollisionProtectionEnabled(name);
}

float
EmotionalMotion::getOrthogonalSecurityDistance()
{
  // TODO Issue #13 Resolve missing functions in ALMotionProxy
  return 0.0f;
  //return motionProxy->getOrthogonalSecurityDistance();
}

float
EmotionalMotion::getTangentialSecurityDistance()
{
  // TODO Issue #13 Resolve missing functions in ALMotionProxy
  return 0.0f;
  //return motionProxy->getTangentialSecurityDistance();
}

void
EmotionalMotion::setExternalCollisionProtectionEnabled(const std::string& name, const bool& enable)
{
  // TODO Issue #13 Resolve missing functions in ALMotionProxy
  //motionProxy->setExternalCollisionProtectionEnabled(name, enable);
}

void
EmotionalMotion::setOrthogonalSecurityDistance(const float& distance)
{
  // TODO Issue #13 Resolve missing functions in ALMotionProxy
  //motionProxy->setOrthogonalSecurityDistance(distance);
}

void
EmotionalMotion::setTangentialSecurityDistance(const float& distance)
{
  // TODO Issue #13 Resolve missing functions in ALMotionProxy
  //motionProxy->setTangentialSecurityDistance(distance);
}

//Fall manager API

void
EmotionalMotion::setFallManagerEnabled(const bool& enable)
{
  motionProxy->setFallManagerEnabled(enable);
}

bool
EmotionalMotion::getFallManagerEnabled()
{
  return motionProxy->getFallManagerEnabled();
}

// Smart Stiffness API

void
EmotionalMotion::setSmartStiffnessEnabled(const bool& enable)
{
  motionProxy->setSmartStiffnessEnabled(enable);
}

bool
EmotionalMotion::getSmartStiffnessEnabled()
{
  return motionProxy->getSmartStiffnessEnabled();
}

// Diagnosis effect API

void
EmotionalMotion::setDiagnosisEffectEnabled(const bool& enable)
{
  motionProxy->setDiagnosisEffectEnabled(enable);
}

bool
EmotionalMotion::getDiagnosisEffectEnabled()
{
  return motionProxy->getDiagnosisEffectEnabled();
}

// Push Recovery API

void
EmotionalMotion::setPushRecoveryEnabled(const bool& enable)
{
  // TODO Issue #13 Resolve missing functions in ALMotionProxy
  //motionProxy->setPushRecoveryEnabled(enable);
}

bool
EmotionalMotion::getPushRecoveryEnabled(void)
{
  // TODO Issue #13 Resolve missing functions in ALMotionProxy
  return false;
  //return motionProxy->getPushRecoveryEnabled();
}

// Idle API

void
EmotionalMotion::setIdlePostureEnabled(const std::string& pChainName, const bool& pEnable)
{
  // TODO Issue #13 Resolve missing functions in ALMotionProxy
  //motionProxy->setIdlePostureEnabled(pChainName, pEnable);
}

bool
EmotionalMotion::getIdlePostureEnabled(const std::string& pChainName)
{
  // TODO Issue #13 Resolve missing functions in ALMotionProxy
  return false;
  //return motionProxy->getIdlePostureEnabled(pChainName);
}

void
EmotionalMotion::setBreathEnabled(const std::string& pChainName, const bool& pEnable)
{
  motionProxy->setBreathEnabled(pChainName, pEnable);
}

bool
EmotionalMotion::getBreathEnabled(const std::string& pChainName)
{
  return motionProxy->getBreathEnabled(pChainName);
}

void
EmotionalMotion::setBreathConfig(const AL::ALValue& pConfig)
{
  motionProxy->setBreathConfig(pConfig);
}

AL::ALValue
EmotionalMotion::getBreathConfig()
{
  return motionProxy->getBreathConfig();
}

// General tools API

bool
EmotionalMotion::areNotificationsEnabled()
{
  // TODO Issue #13 Resolve missing functions in ALMotionProxy
  return false;
  //motionProxy->areNotificationsEnabled();
}

std::vector<std::string>
EmotionalMotion::getBodyNames(const std::string& name)
{
  return motionProxy->getBodyNames(name);
}

std::vector<std::string>
EmotionalMotion::getSensorNames()
{
  return motionProxy->getSensorNames();
}

AL::ALValue
EmotionalMotion::getLimits(const std::string& name)
{
  return motionProxy->getLimits(name);
}

AL::ALValue
EmotionalMotion::getMotionCycleTime()
{
  return motionProxy->getMotionCycleTime();
}

AL::ALValue
EmotionalMotion::getRobotConfig()
{
  return motionProxy->getRobotConfig();
}

std::string
EmotionalMotion::getSummary()
{
  return motionProxy->getSummary();
}

float
EmotionalMotion::getMass(const std::string& pName)
{
  return motionProxy->getMass(pName);
}

std::vector<float>
EmotionalMotion::getCOM(const std::string& pName, const int& pSpace, const bool& pUseSensorValues)
{
  return motionProxy->getCOM(pName, pSpace, pUseSensorValues);
}

void
EmotionalMotion::setMotionConfig(const AL::ALValue& config)
{
  motionProxy->setMotionConfig(config);
}

void
EmotionalMotion::setEnableNotifications(bool enable)
{
  // TODO Issue #13 Resolve missing functions in ALMotionProxy
  //motionProxy->setEnableNotifications(enable);
}

// Motion task API

AL::ALValue
EmotionalMotion::getTaskList()
{
  return motionProxy->getTaskList();
}

bool
EmotionalMotion::areResourcesAvailable(const std::vector<std::string>& resourceNames)
{
  return motionProxy->areResourcesAvailable(resourceNames);
}

bool
EmotionalMotion::killTask(const int& motionTaskID)
{
  return motionProxy->killTask(motionTaskID);
}

void
EmotionalMotion::killTasksUsingResources(const std::vector<std::string>& resourceNames)
{
  motionProxy->killTasksUsingResources(resourceNames);
}

void
EmotionalMotion::killMove()
{
  motionProxy->killMove();
}

void
EmotionalMotion::killAll()
{
  motionProxy->killAll();
}
