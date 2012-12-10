/*
 * RemoteTransmitter.h
 *
 *  Created on: Nov 22, 2012
 *      Author: agu
 */

#ifndef REMOTE_TRANSMITTER_H_
#define REMOTE_TRANSMITTER_H_

#include "Arduino.h"

class RemoteTransmitter
{
public:
	RemoteTransmitter(uint8_t pin, word pulse_length = 230);
	virtual ~RemoteTransmitter();
	void sendData(uint32_t data);

private:
	const uint8_t _pin;
	const word _pulse_length;
	const static byte REPEAT_TIMES = 4;

	void transmit(byte h, byte l);

	void sendBitH();
	void sendBitL();
	void sendBitF();
	void sendBitSync();
	void sendBit(byte bit);
	void sendCodeWord(byte * s);
};

#endif /* REMOTE_TRANSMITTER_H_ */
