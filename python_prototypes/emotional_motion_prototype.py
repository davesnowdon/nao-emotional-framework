""" nao emotional framework - prototype NAO motions to represent emotions.

"""

import sys
import time

import numpy as np

from naoqi import ALProxy
from naoqi import ALBroker
from naoqi import ALModule

from optparse import OptionParser

NAO_IP = "mistcalf.local"

# Global variable to store module instances
emotion_motion = None
memory = None

class motion_module(ALModule):
    """ A simple module to change the head position and stance to represent emotions.

    """
    def __init__(self, name):
        ALModule.__init__(self, name)

        # Create proxies for the instance.
        self.motion = ALProxy("ALMotion")
        
        # Run behaviour when a tactile touched.
        global memory
        memory = ALProxy("ALMemory")
        memory.subscribeToEvent("TouchChanged", self.getName(), "emotive_motion")

    def emotive_motion(self, *_args):
        """ Changes head position based on arousal and stance based on valence.
                        
        """

        memory.unsubscribeToEvent("TouchChanged", self.getName())
        
        motion_names = list()
        motion_times = list()
        motion_keys = list()

        current_emotion = memory.getData("Emotion/Current")
        valence = current_emotion[0][0]
        arousal = current_emotion[0][1]

        # Head pitch - directly proportional to arousal.
        # Head pitch has a range of approx +0.5 to -0.5 radians so divide normalised arousal value by 2.
        head_pitch = arousal / 2

        motion_names.append("HeadPitch")
        motion_times.append([1, 2, 3])
        motion_keys.append([0.0, head_pitch, 0.0])

        # Stance (torso position + arms) - directly proportional to valence
        # Shoulders have a pitch of +2 to -2 radians.
        # Used in absolute mode, central pitch value is 1.4radians.
        shoulder_pitch = 1.4 - valence * 0.5

        motion_names.append("LShoulderPitch")
        motion_times.append([1, 2, 3])
        motion_keys.append([1.45726, shoulder_pitch, 1.45726])

        motion_names.append("RShoulderPitch")
        motion_times.append([1, 2, 3])
        motion_keys.append([1.4, shoulder_pitch, 1.4])

        # Ankles have a pitch of approx +0.9 to -1.1radians.
        # Used in absolute mode, central pitch value is 0.08radians.
        ankle_pitch = 0.08 - valence * 0.05

        motion_names.append("LAnklePitch")
        motion_times.append([1, 2, 3])
        motion_keys.append([0.08, ankle_pitch, 0.08])

        motion_names.append("RAnklePitch")
        motion_times.append([1, 2, 3])
        motion_keys.append([0.08, ankle_pitch, 0.08])

        # Might be better to use the reactive methods -  ALMotionProxy::setAngles().        
        self.motion.angleInterpolation(motion_names, motion_keys, motion_times, True)
        print "done"

        memory.subscribeToEvent("TouchChanged", self.getName(), "emotive_motion")


def main():
    """ Main entry point

    """
    parser = OptionParser()
    parser.add_option("--pip",
        help="Parent broker port. The IP address or your robot",
        dest="pip")
    parser.add_option("--pport",
        help="Parent broker port. The port NAOqi is listening to",
        dest="pport",
        type="int")
    parser.set_defaults(
        pip=NAO_IP,
        pport=9559)

    (opts, args_) = parser.parse_args()
    pip   = opts.pip
    pport = opts.pport

    myBroker = ALBroker("myBroker",
       "0.0.0.0",   
       0,           
       pip,         
       pport)       

    
    global emotion_motion
    global memory

    emotion_motion = motion_module("emotion_motion")

    # set some ALMemory values
    valence = 1.0
    arousal = 1.0
    current_emotion = [(valence, arousal), ("valence_mood", "arousal_mood"), ("personality"), ("param1", "param2")]
    memory.insertData("Emotion/Current", current_emotion)


    try:
        while True:
            time.sleep(1)
    except KeyboardInterrupt:
        print
        print "Interrupted by user, shutting down"
        myBroker.shutdown()
        sys.exit(0)



if __name__ == "__main__":
    main()