#pragma once
#ifndef FRAME_H
#define FRAME_H
#include <vector>
#include "mvm_led.h"

/**
 * \brief This struct contains all the data of a frame obtained from a mvm file. 
 * The frame step number, the time stamp and 18 Leds with its corresponding coordinates and luminosities
 */
struct Frame {
	int stepNumber;
	float timeStamp;
	std::vector<MvmLed> leds;
};
#endif
