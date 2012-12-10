/*
 * Obd.cpp
 *
 *  Created on: Dec 4, 2012
 *      Author: agu
 */

#include "Obd.h"

#define OUTPUT_LENGTH 64

Obd::Obd(HardwareSerial & serial) :
		_sp(serial)
{
	_mode = 1;
	_error = false;
	_output = (char *) malloc(sizeof(char) * OUTPUT_LENGTH);
	_input = (char *) malloc(sizeof(char) * 5);

	memset(_input, 0x00, 5);
	//memset(_output, 0x00, 64);
}

Obd::~Obd()
{
	free(_input);
	free(_output);
}

bool Obd::err()
{
	return _error;
}

void Obd::getValue(byte pid)
{
	sprintf(_input, "%02X%02X", _mode, pid);
	_sp.print(_input);
//	_sp.print("AT");
	_sp.print('\r');

	memset(_output, 0x00, OUTPUT_LENGTH);
	_sp.readBytesUntil(0x3e, _output, OUTPUT_LENGTH);

	_error = *(_output + 5) != *_input + 4 && *(_output + 6) != *(_input + 1);

}

char * Obd::getOutput()
{
	return _output;
}

byte Obd::getByte(byte pid)
{
	this->getValue(pid);

	int val;
	sscanf(_output + 11, "%02x", &val);
	return lowByte(val) ;
}

word Obd::getWord(byte pid)
{
	this->getValue(pid);
	word valH, valL;
	sscanf(_output + 11, "%02x", &valH);
	sscanf(_output + 14, "%02x", &valL);
	word val = (valH * 256 + valL);
	return val;
}
