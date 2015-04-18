#include <SPI.h>
#include <Ethernet.h>
#include <EEPROM.h>
#include <RobotOpen.h>

// Tuning Constants
#define SENSOR1_CHAN 1
#define PWM_CHAN 1
#define MAX_VEL 5000

// Dashboard Parameters
ROIntParameter VelocityCmd("Velocity Cmd", 0);   	// A value that can be updated remotely

// Sensor Input
ROEncoder positionSensor(SENSOR1_CHAN);

//Velocity Control PWM Output
ROPWM velocityPwm(PWM_CHAN);


void setup()
{
  /* Initiate comms */
  RobotOpen.begin(&enabled, &disabled, &timedtasks);
}


/* This is your primary robot loop - all of your code
 * should live here that allows the robot to operate
 */
void enabled() {
  int velPwm = map(VelocityCmd.get(), 0, MAX_VEL, 0, 255);
  velocityPwm.write(velPwm);
  String velocityDebugMsg = "Velocity and PWM: ";
  velocityDebugMsg += velPwm;
  RODashboard.debug(velocityDebugMsg);
}


/* This is called while the robot is disabled
 * All outputs are automatically disabled (PWM, Solenoid, Digital Outs)
 */
void disabled() {
  // safety code
}


/* This loop ALWAYS runs - only place code here that can run during a disabled state
 * This is also a good spot to put driver station publish code
 */
void timedtasks() {
  // encoders can also be reset to zero by calling encoderName.reset();
  RODashboard.publish("Position", positionSensor.read());
  RODashboard.publish("Active PWM Channel", PWM_CHAN);
  RODashboard.publish("Velocity Cmd", VelocityCmd.get());
  RODashboard.publish("Uptime Seconds", ROStatus.uptimeSeconds());
}


// !!! DO NOT MODIFY !!!
void loop() {
  RobotOpen.syncDS();
}
