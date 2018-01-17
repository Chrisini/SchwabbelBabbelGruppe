## GoPro Instant Streaming v1.0
##
## By @Sonof8Bits and @KonradIT
##
## 1. Connect your desktop or laptop to your GoPro via WIFI.
##
## That's all! When done, press CTRL+C to quit this application.
##

import sys
import socket
import urllib.request
import subprocess
from time import sleep
import signal
import json
import re

##gst-launch-1.0 -v udpsrc port=8554 \ caps="application/x-rtp, media=////(string)audio, format=(string)S32LE, \ layout=(string)interleaved, clock-rate=(int)44100, channels=(int)2, payload=(int)0" ! \ rtpL16depay ! playsink

def get_command_msg(id):
	return "_GPHD_:%u:%u:%d:%1lf\n" % (0, 0, 2, 0)

#gst-launch -v udpsrc uri="udp://10.5.5.9:8554" ! mpegtsdemux ! h264parse ! TIViddec2 ! queue ! tidisplaysink2

# gst-launch udpsrc port=8554 ! 'video/mpegts, systemstream=(boolean)true, packetsize=(int)188' ! mpegtsdemux ! 'video/x-h264' ! queue ! ffdec_h264 ! 'video/x-raw-yuv, width=(int)1280, height=(int)720, framerate=(fraction)25/1, format=(fourcc)I420, interlaced=(boolean)false' ! xvimagesink sync=false

def gopro_live():
	UDP_IP = "10.5.5.9"
	UDP_PORT = 8554
	KEEP_ALIVE_PERIOD = 2500
	KEEP_ALIVE_CMD = 2

	MESSAGE = get_command_msg(KEEP_ALIVE_CMD)

	subprocess.Popen("ffplay -loglevel panic -fflags nobuffer -f:v mpegts -probesize 8192 udp://:8554", shell=True)
		
	if sys.version_info.major >= 3:
		MESSAGE = bytes(MESSAGE, "utf-8")
	print("Press ctrl+C to quit this application.\n")
	while True:
		sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
		sock.sendto(MESSAGE, (UDP_IP, UDP_PORT))
		sleep(KEEP_ALIVE_PERIOD/1000)

def quit_gopro(signal, frame):
	sys.exit(0)

if __name__ == '__main__':
	signal.signal(signal.SIGINT, quit_gopro)
	gopro_live()
