/*
 * RemoteController.cpp
 *
 *  Created on: Nov 22, 2012
 *      Author: agu
 */

#include "RemoteTransmitter.h"

RemoteTransmitter::RemoteTransmitter(uint8_t pin, word pulse_length) :
		_pin(pin), _pulse_length(pulse_length)
{
	pinMode(_pin, OUTPUT);
}

RemoteTransmitter::~RemoteTransmitter()
{

}

void RemoteTransmitter::transmit(byte high, byte low)
{
	digitalWrite(_pin, HIGH);
	delayMicroseconds(_pulse_length * high);
	digitalWrite(_pin, LOW);
	delayMicroseconds(_pulse_length * low);
}

void RemoteTransmitter::sendBitL()
{
	transmit(1, 3);
	transmit(1, 3);
}

void RemoteTransmitter::sendBitH()
{
	transmit(3, 1);
	transmit(3, 1);
}

void RemoteTransmitter::sendBitF()
{
	transmit(1, 3);
	transmit(3, 1);
}

void RemoteTransmitter::sendBitSync()
{
	transmit(1, 31);
}

void RemoteTransmitter::sendBit(byte bit)
{
	switch (bit)
	{
	case 0:
		sendBitL();
		break;
	case 1:
		sendBitF();
		break;
	case 2:
		sendBitH();
		break;
	}
}

void RemoteTransmitter::sendCodeWord(byte * s)
{
	for (byte i = 12; i;)
	{
		sendBit(s[--i]);
	}
	sendBitSync();
}

void RemoteTransmitter::sendData(uint32_t data)
{
	byte s[12];

	for (byte i = 0; i < 12; i++)
	{
		s[i] = data % 3;
		data /= 3;
	}

	byte times = REPEAT_TIMES;
	while (times--)
		sendCodeWord(s);
}
