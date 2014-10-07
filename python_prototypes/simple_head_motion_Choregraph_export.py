# Choregraphe simplified export in Python.
import argparse
import motion
import almath
from naoqi import ALProxy

def main(robotIP, PORT = 9559):

	motion = ALProxy("ALMotion", robotIP, 9559)

	names = list()
	times = list()
	keys = list()

	names.append("HeadPitch")
	times.append([1, 1.48, 1.96, 2.44])
	keys.append([0.276078, 0.512314, 0.351244, 0.024502])

	names.append("HeadYaw")
	times.append([1, 1.48, 1.96, 2.44])
	keys.append([-0.0107799, -0.0107799, -4.19617e-05, -4.19617e-05])


	
	
	motion.angleInterpolation(names, keys, times, True)

	print "done"


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("--ip", type=str, default="mistcalf.local",
                        help="Robot ip address")
    parser.add_argument("--port", type=int, default=9559,
                        help="Robot port number")

    args = parser.parse_args()
    main(args.ip, args.port)