void configureAllSensor(){

	SensorType[S1] = sensorEV3_Touch;
	SensorType[S2] = sensorEV3_Ultrasonic;
	SensorType[S3] = sensorEV3_Color;
	wait1Msec(50);
	SensorMode[S3] = modeEV3Color_Color;
	wait1Msec(50);
	SensorType[S4] = sensorEV3_Gyro;
	wait1Msec(50);
	SensorMode[S4] = modeEV3Gyro_Calibration;
	wait1Msec(100);
	SensorMode[S4] = modeEV3Gyro_RateAndAngle;
	wait1Msec(50);
}

	void dispensecoin(){
	nMotorEncoder[motorC] = 0;

	motor[motorC] = 25;

	while(nMotorEncoder[motorC] < 360)
	{}
	motor[motorC] = 0;
}


int rotatetoptable(){

	nMotorEncoder[motorA] = 0;

	motor[motorA] = -10;

	while(SensorValue[S3] == 6 && abs(nMotorEncoder[motorA]) < 180)
	{}
	//int initalmovement = nMotorEncoder[motorA];
	nMotorEncoder[motorA] = 0;
	motor[motorA] = -10;
	while(abs(nMotorEncoder[motorA]) < 10)
	{}
	motor[motorA] = 0;
	// add the inital movement too
	return nMotorEncoder[motorA];
}

void outofcoins(int timer){
	if(SensorValue[S3] == 6){
		motor[motorA] = 10;
		time1[T1] = 0;
		while(time1[T1] < timer)
		{}
		motor[motorA] = 0;
	}
}

int sensecolour(){
	// wait for table to rotate before analysing colour
int x = 0;
if(SensorValue[S3] == 1){
	displayString(3,"Poker Chip is Black!");
	 x = 50;
	}

if(SensorValue[S3] == 2){
	displayString(3,"Poker Chip is Blue!");
	 x = 80;
	}

if(SensorValue[S3] == 5){
	displayString(3,"Poker Chip is Red!");
	 x = 360;
	}
	wait1Msec(50);
if(SensorValue[S3] == 3){
	displayString(3,"Poker Chip is Green!");
	 x = 120;
	}
	return x;
}

int rotatebottomtable(int rotate){

	nMotorEncoder[motorB] = 0;

	motor[motorB] = 25;

	while(nMotorEncoder[motorB] < rotate)
	{}

	motor[motorB] = 0;
	return nMotorEncoder[motorB];
}

task main()
{
	configureAllSensor();
	dispensecoin();
	time1[T2] =0;
	rotatetoptable();
	outofcoins(time1[T2]);
rotatebottomtable(sensecolour());
}
