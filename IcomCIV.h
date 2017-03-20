#ifndef IcomCIV_h
#define IcomCIV_h

// 19200 should work with "AUTO" setting
#define ICOM_BAUDRATE 19200

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
		byte bcd_to_dec(byte bcd);
	public:
		IcomCIV(HardwareSerial serial);
		void begin();
		void process();
		long getFrequency();
};

#endif