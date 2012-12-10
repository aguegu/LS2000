#include "KnightReceiver.h"
#include "TM1812.h"

#define LENGTH 16
#define INDEX_MAX 15

TM1812 tm(13);
byte color[LENGTH] =
{ 0x00 };

void animationSwift(byte clr);
void animationMove(byte clr);
byte code = 0;

void setup()
{
	cbi(TIMSK0, TOIE0);

	////////////////////////////
	pinMode(A0, OUTPUT);
	pinMode(A1, OUTPUT);

	pinMode(A2, INPUT);
	pinMode(A3, INPUT);
	pinMode(A4, INPUT);
	pinMode(A5, INPUT);

	digitalWrite(A0, LOW);
	digitalWrite(A1, HIGH);

	Serial.begin(9600);

	memset(color, 0x00, LENGTH);
	tm.sendData(color, LENGTH);
}

void loop()
{
	static byte cache = 0x00;
	static byte last_code = 0x00;

	byte val = 0x00;
	val += digitalRead(A2) ? 1 : 0;
	val += digitalRead(A3) ? 2 : 0;
	val += digitalRead(A4) ? 4 : 0;
	val += digitalRead(A5) ? 8 : 0;

	if (val != cache)
	{
		Serial.write(val);
		cache = val;
		//if (cache)
		code = cache;
		//last_code = code ? code : last_code;
	}

	switch (code)
	{
	case 8:
		animationSwift(0x04);
		last_code = code;
		break;
	case 4:
//		memset(color, 0x01, LENGTH);
//		tm.sendData(color, LENGTH);
		animationMove(0x02);
		last_code = code;
		break;
	case 2:
		animationMove(0x01);
		last_code = code;
//		memset(color, 0x02, LENGTH);
//		tm.sendData(color, LENGTH);
		break;
	case 1:
		animationMove(0x04);
		last_code = code;
		break;
	case 0:
		code = last_code;
		break;
	case 15:
		memset(color, 0x00, LENGTH);
		tm.sendData(color, LENGTH);
		last_code = 0;
		break;
	default:
		digitalWrite(A1, LOW);
		delay(20);
		digitalWrite(A1, HIGH);

		memset(color, 0x00, LENGTH);
		tm.sendData(color, LENGTH);

		last_code = 0;
		//TM1812::delayLong(0x100000);
		break;

	}
}

void animationSwift(byte clr)
{
	byte i = 0;
	memset(color, 0x00, LENGTH);
	color[0] = clr;
	color[1] = clr;

	//swifting
	for (; i < INDEX_MAX - 1; i++)
	{
		tm.sendData(color, LENGTH);
		TM1812::delayLong(0x10000);
		byte tmp = color[INDEX_MAX];
		memmove(color + 1, color, INDEX_MAX);
		color[0] = tmp;
	}

	for (; i; i--)
	{
		tm.sendData(color, LENGTH);
		TM1812::delayLong(0x10000);
		byte tmp = color[0];
		memcpy(color, color + 1, INDEX_MAX);
		color[INDEX_MAX] = tmp;
	}
}

void animationMove(byte clr)
{

	memset(color, 0x00, LENGTH);

	byte half = LENGTH >> 1;

	color[half] = clr;
	color[half - 1] = clr;

	for (byte i = 0; i < half - 1; i++)
	{
		tm.sendData(color, LENGTH);
		TM1812::delayLong(0x20000);

		for (byte j = 0; j < half - 1; j++)
		{
			color[INDEX_MAX - j] = color[INDEX_MAX - j - 1];
			color[j] = color[j + 1];
		}
		color[half] = 0;
		color[half - 1] = 0;
	}

	for (byte i = 1; i < half; i++)
	{
		tm.sendData(color, LENGTH);
		TM1812::delayLong(0x20000);

		for (byte j = 0; j < half - 1; j++)
		{
			color[half + j] = color[half + j + 1];
			color[half - 1 - j] = color[half - 2 - j];
		}
		color[0] = 0;
		color[INDEX_MAX] = 0;
	}

}

void setColor()
{

}
