/*******************************************************************************
  Copyright(c) 2015-2021 Radek Kaczorek  <rkaczorek AT gmail DOT com>

 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Library General Public
 License version 2 as published by the Free Software Foundation.
 .
 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Library General Public License for more details.
 .
 You should have received a copy of the GNU Library General Public License
 along with this library; see the file COPYING.LIB.  If not, write to
 the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 Boston, MA 02110-1301, USA.
*******************************************************************************/

#ifndef ASTROBERRYRELAYS_H
#define ASTROBERRYRELAYS_H

#include <string.h>
#include <iostream>
#include <stdio.h>

#include <defaultdevice.h>

class IndiAstrAlimRelays : public INDI::DefaultDevice
{
public:
	IndiAstrAlimRelays();
	virtual ~IndiAstrAlimRelays();
	virtual const char *getDefaultName();
	virtual bool initProperties();
	virtual bool updateProperties();
	virtual void ISGetProperties(const char *dev);
	virtual bool ISNewNumber (const char *dev, const char *name, double values[], char *names[], int n);
	virtual bool ISNewSwitch (const char *dev, const char *name, ISState *states, char *names[], int n);
	virtual bool ISNewText (const char *dev, const char *name, char *texts[], char *names[], int n);
	virtual bool ISNewBLOB (const char *dev, const char *name, int sizes[], int blobsizes[], char *blobs[], char *formats[], char *names[], int n);
	virtual bool ISSnoopDevice(XMLEle *root);
protected:
	virtual bool saveConfigItems(FILE *fp);
	virtual void TimerHit();
private:
	virtual bool Connect();
	virtual bool Disconnect();
	virtual void udateSwitches();

	INumber BCMpinsN[3];
	INumberVectorProperty BCMpinsNP;
	ISwitch ActiveStateS[2];
	ISwitchVectorProperty ActiveStateSP;
	IText RelayLabelsT[8];
	ITextVectorProperty RelayLabelsTP;

	ISwitch Switch1S[2];
	ISwitchVectorProperty Switch1SP;
	ISwitch Switch2S[2];
	ISwitchVectorProperty Switch2SP;
	ISwitch Switch3S[2];
	ISwitchVectorProperty Switch3SP;
	//ISwitch MasterSwitchS[2];
	//ISwitchVectorProperty MasterSwitchSP;

	//ILight SwitchStatusL[8];
	//ILightVectorProperty SwitchStatusLP;

	int activeState = 0;
	int relayState[8]; // relayState is mission critical to maintain relays status between reconnections. initially set to !activeState
	int pollingTime = 1000;

	const char* gpio_chip_path = "/dev/gpiochip4";
	struct gpiod_chip *chip;
	struct gpiod_line *gpio_relay1;
	struct gpiod_line *gpio_relay2;
	struct gpiod_line *gpio_relay3;
};

#endif
