// Copyright (c) 2023 Oleg Kalachev <okalachev@gmail.com>
// Repository: https://github.com/okalachev/flix

// Motors output control using MOSFETs
// In case of using ESC, use this version of the code: https://gist.github.com/okalachev/8871d3a94b6b6c0a298f41a4edd34c61.
// Motor: 8520 3.7V

#define MOTOR_0_PIN 12 // rear left
#define MOTOR_1_PIN 13 // rear right
#define MOTOR_2_PIN 14 // front right
#define MOTOR_3_PIN 15 // front left

#define PWM_FREQUENCY 200
#define PWM_RESOLUTION 8

void setupMotors() {
	Serial.println("Setup Motors");

	// configure pins
	ledcAttach(MOTOR_0_PIN, PWM_FREQUENCY, PWM_RESOLUTION);
	ledcAttach(MOTOR_1_PIN, PWM_FREQUENCY, PWM_RESOLUTION);
	ledcAttach(MOTOR_2_PIN, PWM_FREQUENCY, PWM_RESOLUTION);
	ledcAttach(MOTOR_3_PIN, PWM_FREQUENCY, PWM_RESOLUTION);

	sendMotors();
	Serial.println("Motors initialized");
}

uint8_t signalToDutyCycle(float signal) {
	float duty = mapff(signal, 0, 1, 0, (1 << PWM_RESOLUTION) - 1);
	return round(constrain(duty, 0, (1 << PWM_RESOLUTION) - 1));
}

void sendMotors() {
	ledcWrite(MOTOR_0_PIN, signalToDutyCycle(motors[0]));
	ledcWrite(MOTOR_1_PIN, signalToDutyCycle(motors[1]));
	ledcWrite(MOTOR_2_PIN, signalToDutyCycle(motors[2]));
	ledcWrite(MOTOR_3_PIN, signalToDutyCycle(motors[3]));
}
