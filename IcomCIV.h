#ifndef IcomCIV_h
#define IcomCIV_h

#include "HardwareSerial.h"
#include "Arduino.h"

class IcomCIV {
	private:
		HardwareSerial* serial;
		long frequency = 0;
		byte message[128];
		int position = 0;
		int mode = 0;

		void parseMessage();
		void process();
		byte bcd_to_dec(byte bcd);
	public:
		IcomCIV();
		void begin(HardwareSerial serial, int baudRate);
		long getFrequency();
};

#endif