""" nao emotional framework - prototype LED eye colours to represent emotions.

"""

import sys
import time

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

	def convertRGBToHex(self, list):
	    if len(list) == 3:
	        colour = 256 * 256 * list[0] + 256 * list[1] + list[2]
	    else:
	        raise ValueError("Not a valid RGB list")
	    return colour

	def emotive_eyes(self, *_args):

		RGB = [0, 255, 0]
		hex_colour = self.convertRGBToHex(RGB)
		durationList = [1.0]

		memory.unsubscribeToEvent("TouchChanged", self.getName())

		self.leds.fadeRGB("FaceLeds", hex_colour, 1.0)
		self.tts.say("Hello, world!")
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
    LED_eyes = LED_eyes_module("LED_eyes")

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