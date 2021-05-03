#include "ofxIXWebSocket.h"

ofxIXWebSocket::ofxIXWebSocket(){
#if defined(TARGET_MINGW) || defined(TARGET_WINVS)
	ix::initNetSystem();
#endif
}

ofxIXWebSocket::~ofxIXWebSocket(){
#if defined(TARGET_MINGW) || defined(TARGET_WINVS)
	ix::uninitNetSystem();
#endif
}
