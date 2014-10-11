""" nao emotional framework - prototype LED eye colours to represent emotions.

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
LED_eyes = None
memory = None

class LED_eyes_module(ALModule):
    """ A simple module to change the eye LEDs colour to represent emotions.

    """
    def __init__(self, name):
        ALModule.__init__(self, name)

        # Create proxies for the instance.
        self.tts = ALProxy("ALTextToSpeech")
        self.leds = ALProxy("ALLeds")

        # Run behaviour when a tactile touched.
        global memory
        memory = ALProxy("ALMemory")
        memory.subscribeToEvent("TouchChanged", self.getName(), "emotive_eyes")

    def emotive_eyes(self, *_args):
        """ Change eye colour to express emotion.
            Uses VA mapping based on a RYB (artists) colour wheel.
                        
        """

        memory.unsubscribeToEvent("TouchChanged", self.getName())
        
        eye_colour_lookup_table = [[(0xF82C35),(0xF82C35),(0xD55528),(0xD55528),(0xFF622B),(0xFF622B),(0xFFB047),(0xFFB047),(0xFFB047),(0xFFB047),(0xFFB047)],
                                [(0xF82C35),(0xF82C35),(0xD5542A),(0xD5542A),(0xE96A37),(0xFF8232),(0xFF8232),(0xFEB340),(0xFEB340),(0xFEB340),(0xFFFF00)],
                                [(0xF62D35),(0xF62D35),(0xF62D35),(0xE96A37),(0xE96A37),(0xFF984D),(0xFF8232),(0xFDC147),(0xFFB144),(0xFFFF00),(0xFFFF00)],
                                [(0xF72C32),(0xF72C32),(0xFF4048),(0xFE5761),(0xED8659),(0xFEB278),(0xFECE6A),(0xFECE6A),(0xFEE566),(0xFFFF00),(0xFFFF00)],
                                [(0xF6255C),(0xF6255C),(0xF9386F),(0xFD585E),(0xF78C84),(0xFFB379),(0xFEDEA1),(0xFEE67C),(0xFFE564),(0xFFFF00),(0xFFFF00)],
                                [(0xF6255C),(0xF93871),(0xF93871),(0xFE9EB9),(0xFE9EB9),(0xFFFFFF),(0xD0E7B3),(0xA5D277),(0x85B957),(0x6EAB34),(0x6EAB34)],
                                [(0xA82C72),(0xA82C72),(0xC03381),(0xDB5CA1),(0xE8A1C3),(0xD1E5F0),(0xCFDADE),(0x73B8B3),(0x87B958),(0x6EAB34),(0x6EAB34)],
                                [(0xA82C72),(0xA82C72),(0xC03381),(0x9C3F74),(0xB36893),(0xD1E4F2),(0x91C3E6),(0x91C3E6),(0x219A95),(0x00948E),(0x6BAC34)],
                                [(0xA82C72),(0xA82C72),(0x86305D),(0x86305D),(0x94C8D6),(0x93C8D8),(0x92C2E6),(0x3196CE),(0x009591),(0x009591),(0x009591)],
                                [(0xA62D72),(0x692850),(0x692850),(0x692850),(0x2D9DB1),(0x2C9FB2),(0x2F96CE),(0x0085BE),(0x00968D),(0x00968D),(0x00968D)],
                                [(0x692850),(0x692850),(0x692850),(0x692850),(0x037F9B),(0x037F9B),(0x0085BE),(0x0085BE),(0x0085BE),(0x0085BE),(0x0085BE)]
                                ]
        
        current_emotion = memory.getData("Emotion/Current")
        valence = current_emotion[0][0]
        arousal = current_emotion[0][1]
        
        valence_index = (int(valence * 5) + 5)
        arousal_index = 10 - (int(arousal * 5) + 5)
        hex_eye_colour = eye_colour_lookup_table[arousal_index][valence_index]
        eye_duration = 2.0
               
        self.leds.fadeRGB("FaceLeds", hex_eye_colour, eye_duration)
        time.sleep(5.0)
        self.leds.reset("FaceLeds")

        memory.subscribeToEvent("TouchChanged", self.getName(), "emotive_eyes")


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

    
    global LED_eyes
    global memory

    LED_eyes = LED_eyes_module("LED_eyes")

    # set some ALMemory values
    valence = 1.0
    arousal = 0.75
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