// Copyright (c) 2024 Oleg Kalachev <okalachev@gmail.com>
// Repository: https://github.com/okalachev/flix

// Fail-safe for RC loss

#define RC_LOSS_TIMEOUT 0.2
#define DESCEND_TIME 3.0 // time to descend from full throttle to zero

extern double controlsTime;
extern int rollChannel, pitchChannel, throttleChannel, yawChannel;

void failsafe() {
	if (t - controlsTime > RC_LOSS_TIMEOUT) {
		descend();
	}
}

void descend() {
	// Smooth descend on RC lost
	mode = STAB;
	controls[rollChannel] = 0;
	controls[pitchChannel] = 0;
	controls[throttleChannel] = 0;
	controls[throttleChannel] -= dt / DESCEND_TIME;
	if (controls[throttleChannel] < 0) controls[throttleChannel] = 0;
}
