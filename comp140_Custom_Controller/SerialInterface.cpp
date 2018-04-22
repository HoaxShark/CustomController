#include "stdafx.h"
#include "SerialInterface.h"
#include <iostream>

using std::cout;
using std::vector;
using std::exception;
using std::stoi;
using std::string;

SerialInterface::SerialInterface()
{
	vector <serial::PortInfo> devicesFound = serial::list_ports(); // checks all serial ports

	vector <serial::PortInfo>::iterator iter = devicesFound.begin(); // 

	while (iter != devicesFound.end()) {
		serial::PortInfo device = *iter++; // gets current device
		string port = device.port.c_str();

		try {
			mySerial = new serial::Serial(port, 115200, serial::Timeout::simpleTimeout(250));

			if (mySerial->isOpen()) {
				cout << "Connection Succes: " << port << "\n";
				connect = true;
				break;
			}
		}
		catch (exception &e){

		}
	}
}


SerialInterface::~SerialInterface()
{
}

void SerialInterface::send(string msg)
{
	if (connect) {
		mySerial->write(msg); // sends string to serial
	}
}

void SerialInterface::getValues()
{
	if (connect) {
		mySerial->write("H"); // sends string to get potentiometer readings back

		string result = mySerial->readline();

		if (result.length() >= 15) {
			string sub1 = result.substr(0, 4);
			redValue = std::stoi(sub1);
			string sub2 = result.substr(4, 4);
			greenValue = std::stoi(sub2);
			string sub3 = result.substr(8, 4);
			blueValue = std::stoi(sub3);
			string sub4 = result.substr(12, 4);
			yellowValue = std::stoi(sub4);
		}
	}
}

void SerialInterface::printValues()
{
	std::cout << "Red - " << redValue << "Green - " <<  greenValue << "Blue - " <<  blueValue << "Yellow - " << yellowValue << std::endl;
}

void SerialInterface::close()
{
	//mySerial->flush();
	//mySerial->close();
}
