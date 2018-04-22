#pragma once
#include <serial\serial.h>
#include <string>

using std::string;


class SerialInterface
{
public:
	SerialInterface();
	~SerialInterface();

	void send(string msg);
	void getValues();
	void printValues();

	int getRedValue() { return redValue; };
	int getGreenValue() { return greenValue; };
	int getBlueValue() { return blueValue; };
	int getYellowValue() { return yellowValue; };

	void close();

private:
	serial::Serial* mySerial;
	bool connect = false;

	int redValue = 0;
	int greenValue = 0;
	int blueValue = 0;
	int yellowValue = 0;

};


