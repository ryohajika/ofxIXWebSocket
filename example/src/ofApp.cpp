#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ws.setCacertFile("cacert.pem");
	ws.setVerbose(false);
	ws.setup("wss://echo.websocket.org", 443);
	ws.connect();
	ofAddListener(ws.onMessageEvt, this, &ofApp::wsReceiveCallback);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

}

//--------------------------------------------------------------
void ofApp::exit(){
	ws.disconnect();
	ofRemoveListener(ws.onMessageEvt, this, &ofApp::wsReceiveCallback);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	if(key == 's'){
		ws.sendMessage("hello world");
	}
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::wsReceiveCallback(std::string &msg){
	std::cout << "WebSocket[RECEIVED]: " << msg << std::endl;
}
