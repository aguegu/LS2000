/*
 * Obd.h
 *
 *  Created on: Dec 4, 2012
 *      Author: agu
 */

#ifndef OBD_H_
#define OBD_H_

#include "Arduino.h"

class Obd
{
public:
	Obd(HardwareSerial & serial);
	virtual ~Obd();
	char * getOutput();
	void getValue(byte pid);
	byte getByte(byte pid);
	word getWord(byte pid);
	bool err();

private:
	HardwareSerial & _sp;
	byte _mode;
	bool _error;
	char * _output;
	char * _input;
};

#endif /* OBD_H_ */
