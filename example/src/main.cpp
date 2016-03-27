#include "ofMain.h"
#include "ofxJoystick.h"

class PSJoystick : public ofBaseApp{
	public:
	ofxJoystick joy;
	int numButton;
	int valueButton;
	int numAxis;
	int valueAxis;
	ofBoxPrimitive box;
	int x,y;

	void setup(){
		joy.setup("/dev/input/js0");
		if (!joy.isFound()) 
		    ofLog()<<"open Failed!";
		else
		    ofLog()<<"open Start!";
		box.set(100);
	}

	void update(){
		numButton   = joy.getButtonNum();
		valueButton = joy.getButtonValue();
		numAxis     = joy.getAxisNum();
		valueAxis   = joy.getAxisValue();
		switch(numButton){
			case 7: //left
				x--;
			break;
			case 5: //right
				x++;
			break;
			case 4: //up
				y--;
			break;
			case 6: //down
				y++;
			break;
		}
		numButton = 0;
		box.setPosition(ofVec3f(x,y,0));
		print();
	}

	void exit(){
		joy.exit();
	}

	void draw(){
		ofEnableDepthTest();
		ofSetColor(255,0,0);
		box.draw();
		ofSetColor(0,0,0);
		box.drawWireframe();
		ofDisableDepthTest();
	}
	
	void print(){
		ofLog()<<"Button:";
		ofLog()<<numButton;
		ofLog()<<valueButton;
		ofLog()<<"Axis:";
		ofLog()<<numAxis;
		ofLog()<<valueAxis;
		ofLog()<<"******************";
	}
};

int main(){
    ofSetupOpenGL(630,360, OF_WINDOW);
    ofRunApp(new PSJoystick()); 
}
