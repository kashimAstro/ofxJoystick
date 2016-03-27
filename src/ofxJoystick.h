#include "ofMain.h"

#define JS_EVENT_BUTTON 0x01 // button pressed/released
#define JS_EVENT_AXIS   0x02 // joystick moved
#define JS_EVENT_INIT   0x80 // initial state of device

class ofxJoystickEvent {
	public:
  	static const short MIN_AXES_VALUE = -32768;
	static const short MAX_AXES_VALUE = 32767;
  	unsigned int time;
  	short value;
  	unsigned char type;
    	unsigned char number;

	bool isButton() {
	    return (type & JS_EVENT_BUTTON) != 0;
	}

	bool isAxis() {
	    return (type & JS_EVENT_AXIS) != 0;
	}

	bool isInitialState() {
	    return (type & JS_EVENT_INIT) != 0;
	}
};

class ofxJoystick : public ofThread {
	public:

	void openPath(std::string devicePath);
	int _fd;
	  
	int buttonNum;
	int buttonValue;
	int axisNum;
	int axisValue;
	~ofxJoystick();
	ofxJoystick();
	ofxJoystick(int joystickNumber);
	ofxJoystick(std::string devicePath);
	void setup(std::string devicePath); 
	bool isFound();
	bool sample(ofxJoystickEvent* event);
	void threadedFunction();
	void exit();

	int getButtonNum();
	int getButtonValue();
	int getAxisNum();
	int getAxisValue();
};
