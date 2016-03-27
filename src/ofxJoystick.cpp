#include "ofxJoystick.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <iostream>
#include <string>
#include <sstream>
#include "unistd.h"

ofxJoystick::ofxJoystick() {
  openPath("/dev/input/js0");
}

ofxJoystick::ofxJoystick(int joystickNumber)
{
  std::stringstream sstm;
  sstm << "/dev/input/js" << joystickNumber;
  openPath(sstm.str());
}

ofxJoystick::ofxJoystick(std::string devicePath)
{
  openPath(devicePath);
}

void ofxJoystick::setup(std::string devicePath)
{
  openPath(devicePath);
  startThread(true);
}

void ofxJoystick::exit()
{
  stopThread();
}

int ofxJoystick::getButtonNum()
{
  return buttonNum;
}

int ofxJoystick::getButtonValue()
{
  return buttonValue;
}

int ofxJoystick::getAxisNum()
{
  return axisNum;
}

int ofxJoystick::getAxisValue()
{
  return axisValue;
}

void ofxJoystick::threadedFunction() 
{
   while(isThreadRunning()) {
      ofxJoystickEvent event;
      if (sample(&event)) {
         if (event.isButton()) {
	       buttonNum = event.number;
	       buttonValue = event.value;
         }
         else if (event.isAxis()) {
	       axisNum = event.number;
	       axisValue = event.value;
         }
      }
      usleep(1000);
   }
}

void ofxJoystick::openPath(std::string devicePath)
{
  _fd = open(devicePath.c_str(), O_RDONLY | O_NONBLOCK);
}

bool ofxJoystick::sample(ofxJoystickEvent* event)
{
  int bytes = read(_fd, event, sizeof(*event)); 

  if (bytes == -1)
    return false;
  // NOTE if this condition is not met, we're probably out of sync and this
  // Joystick instance is likely unusable
  return bytes == sizeof(*event);
}

bool ofxJoystick::isFound()
{
  return _fd >= 0;
}

ofxJoystick::~ofxJoystick()
{
  close(_fd);
};
