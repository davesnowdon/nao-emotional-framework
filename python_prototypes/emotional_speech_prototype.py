""" nao emotional framework - prototype speech to represent emotions.

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
emotional_speech = None
memory = None

class emotional_speech_module(ALModule):
    """ A simple module to change speech parameters dependent on emotions.

    """
    def __init__(self, name):
        ALModule.__init__(self, name)

        # Create proxies for the instance.
        self.tts = ALProxy("ALTextToSpeech")
        

        # Run behaviour when a tactile touched.
        global memory
        memory = ALProxy("ALMemory")
        memory.subscribeToEvent("TouchChanged", self.getName(), "emotive_speech")

    def emotive_speech(self, *_args):
        """ Change speech parameters dependent on the emotion.
            Change volume, speed, pitch & insert spaces.
                        
        """

        memory.unsubscribeToEvent("TouchChanged", self.getName())
        
        # Speech parameter lookup table. Format (pitch modifier, volume modifier)
        speech_parameter_lookup_table = [((1.00,1.00),(1.00,1.00),(1.00,1.00),(1.00,1.00),(1.00,1.00),(1.00,1.00),(1.00,1.00),(1.00,1.00),(1.00,1.00),(1.00,1.00),(1.00,1.00)),
                                        ((1.00,1.00),(1.00,1.00),(1.00,1.00),(1.00,1.00),(1.00,1.00),(1.00,1.00),(1.00,1.00),(1.00,1.00),(1.00,1.00),(1.00,1.00),(1.00,1.00)),
                                        ((1.00,0.75),(0.81,0.75),(0.00,0.00),(0.00,0.00),(-0.25,0.00),(0.50,1.00),(0.62,0.50),(0.75,),(0.75,),(0.75,0.75),(1.00,0.75)),
                                        ((1.00,0.50),(0.63,0.50),(-0.20,-0.50),(-1.00,-1.00),(-0.25,-0.50),(0.25,0.50),(0.25,0.50),(0.50,),(0.50,0.50),(0.50,0.50),(0.00,0.50)),
                                        ((1.00,0.25),(0.44,0.25),(0.40,-0.50),(0.30,-0.50),(0.25,-0.50),(0.25,0.00),(0.25,0.00),(0.25,0.25),(0.25,0.25),(0.25,0.25),(0.00,0.25)),
                                        ((1.00,0.00),(0.25,0.00),(0.10,0.00),(0.00,0.00),(0.00,0.00),(0.00,0.00),(0.00,0.00),(0.10,0.00),(0.10,0.00),(0.10,0.00),(0.00,0.00)),
                                        ((0.25,-0.25),(0.06,-0.25),(-0.10,-0.25),(-0.20,0.00),(-0.20,0.00),(-0.10,0.00),(0.00,0.00),(0.00,0.00),(0.00,0.00),(0.00,0.00),(0.00,0.00)),
                                        ((-0.25,-0.50),(-0.13,-0.50),(-0.35,-0.50),(-0.20,-0.25),(-0.10,0.00),(0.00,0.00),(0.00,0.00),(0.00,0.00),(0.00,0.00),(0.00,0.00),(0.00,0.00)),
                                        ((-0.25,-0.75),(-0.31,-0.75),(-0.35,-0.75),(-0.10,-0.50),(-0.10,-0.25),(0.00,0.00),(0.00,0.00),(0.00,0.00),(0.00,0.00),(0.00,0.00),(0.00,0.00)),
                                        ((-0.50,-1.00),(-0.50,-1.00),(-0.40,-1.00),(-0.20,-0.75),(-0.10,-0.50),(0.00,-0.25),(0.00,0.00),(0.00,0.00),(0.00,0.00),(0.00,0.00),(0.00,0.00)),
                                        ((-0.50,-1.00),(-0.50,-1.00),(-0.50,-1.00),(-0.25,-0.75),(0.00,-0.50),(0.00,-0.25),(0.00,0.00),(0.00,0.00),(0.00,0.00),(0.00,0.00),(0.00,0.00))]
        
        # The pitch and volume modifier values need scaled, final value to be determined. e.g. a value of 4 will divide the parameter by 4 to give a +/- of 25% of the default value
        speech_parameter_scaling_value = 4
        
        current_emotion = memory.getData("Emotion/Current")
        valence = current_emotion[0][0]
        arousal = current_emotion[0][1]
        valence_index = (int(valence * 5) + 5)
        arousal_index = 10 - (int(arousal * 5) + 5)
        scaled_pitch_modifier = 1 + (speech_parameter_lookup_table[arousal_index][valence_index][0] / speech_parameter_scaling_value)
        # NAO can only increase pitch! So need to check if a pitch reduction required and negate it. Range 1.0 - 4.0.
        if scaled_pitch_modifier < 1.0:
            scaled_pitch_modifier = 1.0
        # NAO volume (gain) range 0.0 - 1.0.
        scaled_volume_modifier = 0.5 + (speech_parameter_lookup_table[arousal_index][valence_index][1] / speech_parameter_scaling_value)
       
        print speech_parameter_lookup_table[arousal_index][valence_index][0]
        print speech_parameter_lookup_table[arousal_index][valence_index][1]
        print scaled_pitch_modifier
        print scaled_volume_modifier
        
        self.tts.setParameter("pitchShift", scaled_pitch_modifier)
        self.tts.setVolume(scaled_volume_modifier)
        self.tts.say("What is going on, I can't feel my feet!")

        # Reset all values to default.
        self.tts.setParameter("pitchShift", 0)
        self.tts.setVolume(0.5)

        time.sleep(1.0)


        memory.subscribeToEvent("TouchChanged", self.getName(), "emotive_speech")


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

    
    global emotional_speech
    global memory

    emotional_speech = emotional_speech_module("emotional_speech")

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