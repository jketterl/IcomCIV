#include "IcomCIV.h"

IcomCIV::IcomCIV() {
}

void IcomCIV::begin(HardwareSerial s, int baudRate) {
	serial = &s;
	serial->begin(baudRate);
}

void IcomCIV::process() {
  while (Serial1.available()) {
    byte read = Serial1.read();
    if (mode == 0) {
      if (read == 254) {
        mode = 1;
        position = 0;
        message[position++] = read;
      }
    } else if (mode == 1) {
      message[position++] = read;
      if (read == 253) {
        this->parseMessage();
        mode = 0;
      }
    }
  }
}

void IcomCIV::parseMessage() {
	// check if the message preamble is OK
  	if (message[0] != 254 || message[1] != 254) return;
  	// only process frequency change messages
 	if (message[4] != 0) return;
 	// check message length
  	if (position != 11) {
  		frequency = -1;
	    return;
  	}
  	// check message end
  	if (message[10] != 253) {
  		frequency = -1;
    	return;
  	}
  
  // decode BCD data
  frequency = 0;
  frequency += ((long) bcd_to_dec(message[5]));
  frequency += ((long) bcd_to_dec(message[6])) * 100;
  frequency += ((long) bcd_to_dec(message[7])) * 10000;
  frequency += ((long) bcd_to_dec(message[8])) * 1000000;
  frequency += ((long) bcd_to_dec(message[9])) * 100000000;
}

long IcomCIV::getFrequency() {
	process();
	return frequency;
}

byte IcomCIV::bcd_to_dec(byte bcd) {
	byte result = 0;
	
	result += ((bcd & 0b11110000) >> 4) * 10;
	result += (bcd & 0b00001111);

	return result;	
}
