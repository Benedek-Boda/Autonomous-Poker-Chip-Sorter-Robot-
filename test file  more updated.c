
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
	SensorMode[S4] = modeEV3Gyro_Rate;
	wait1Msec(50);
}

void dispensecoin(){
	nMotorEncoder[motorC] = 0;

	motor[motorC] = 20;

	while(nMotorEncoder[motorC] < 360)
	{}
	motor[motorC] = 0;
}

int rotatetoptable(){

	nMotorEncoder[motorA] = 0;

	motor[motorA] = -10;
	time1[T1] = 0;
	while(SensorValue[S3] == 6 && abs(nMotorEncoder[motorA]) < 180)
	{}

	int initalmovement = nMotorEncoder[motorA];
	nMotorEncoder[motorA] = 0;
	motor[motorA] = -10;
	while(abs(nMotorEncoder[motorA]) < 10)
	{}
	motor[motorA] = 0;
	return initalmovement + nMotorEncoder[motorA];
}

void outofcoins(int timer){
	if(SensorValue[S3] == 6){
		motor[motorA] = 10;
		time1[T1] = 0;
		while(time1[T1] < timer)
		{}
		wait1Msec(2000);
		motor[motorA] = 0;
		stopAllTasks();
	}
}

int sensecolour(){
	int x = 0;
	if(SensorValue[S3] == 1){
	displayString(3,"Poker Chip is Black!");
	wait1Msec(2000);
	 x = 100;
	}

if(SensorValue[S3] == 2){
	displayString(3,"Poker Chip is Blue!");
	wait1Msec(2000);
	 x = 160;
	}

if(SensorValue[S3] == 5){
	displayString(3,"Poker Chip is Red!");
	wait1Msec(2000);
	 x = 220;
	}
	wait1Msec(50);
if(SensorValue[S3] == 3){
		displayString(3,"Poker Chip is Green!");
		wait1Msec(2000);
	 	x = 280;
	}
	return x;
}

int rotatebottomtable(int rotate){

	nMotorEncoder[motorB] = 0;

	motor[motorB] = -20;

	while(abs(nMotorEncoder[motorB]) < rotate)
	{}

	motor[motorB] = 0;
	return nMotorEncoder[motorB];
}

int rotatetoptillfall(){

	nMotorEncoder[motorA] = 0;
	motor[motorA] = -10;
	while(SensorValue[S4] < 10 && abs(nMotorEncoder[motorA]) < 1440)
	{}
	motor[motorA] = 0;
	return nMotorEncoder[motorA];
}

void resettoptable(int totalrotate){
	nMotorEncoder[motorA] = 0;
	motor[motorA] = 10;
	while(abs(nMotorEncoder[motorA]) < abs(totalrotate))
	{}
	motor[motorA] = 0;
}

void resetbottomtable(int totalrotate){
	nMotorEncoder[motorB] = 0;
	motor[motorB] = 20;
	while(abs(nMotorEncoder[motorB]) < abs(totalrotate))
	{}
	motor[motorB] = 0;
}

task main()
{

	configureAllSensor();
	while(1==1){
	int totalrotationtop = 0;
	int totalrotationbottom = 0;
	while(!getButtonPress(buttonEnter))
		{}
	while(getButtonPress(buttonEnter))
		{}
	dispensecoin();
	time1[T2] =0;
	totalrotationtop += rotatetoptable();

	outofcoins(time1[T2]);

	totalrotationbottom += rotatebottomtable(sensecolour());
	totalrotationtop += rotatetoptillfall();
	wait1Msec(2000);
	resettoptable(totalrotationtop);
	resetbottomtable(totalrotationbottom);
	}
}
