#include <SPI.h>
#include <Ethernet.h>
#include <EEPROM.h>
#include <RobotOpen.h>

/* Parameter Setup */
ROFloatParameter TlmVelocityCmd("Velocity Cmd", 0);   	// A value that can be updated remotely
ROPWM velocityCmd(5);

void setup()
{
  /* Initiate comms */
  RobotOpen.begin(&enabled, &disabled, &timedtasks);
}


/* This is your primary robot loop - all of your code
 * should live here that allows the robot to operate
 */
void enabled() {
  velocityCmd.write(220);
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
  RODashboard.publish("Velocity Cmd", TlmVelocityCmd.get());
  RODashboard.publish("Uptime Seconds", ROStatus.uptimeSeconds());
}


// !!! DO NOT MODIFY !!!
void loop() {
  RobotOpen.syncDS();
}
