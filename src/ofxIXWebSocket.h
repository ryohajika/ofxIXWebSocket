// originally IXWebSocket (https://github.com/machinezone/IXWebSocket)
// OF addon created by Ryo Hajika (https://github.com/ryohajika/ofxIXWebSocket)

#pragma once

#include "ofMain.h"

#include "IXNetSystem.h"
#include "IXWebSocket.h"

class ofxIXWebSocket {
private:
	std::string _host;
	int _port;
	int _ping_intvl_sec;
	
public:
	ofxIXWebSocket();
	~ofxIXWebSocket();
	
	void setup(std::string target_address,
			   int target_port);
	void connect();
	void disconnect();
	void sendMessage(std::string msg_str);
	void sendMessage(char* msg_chars);
	
	void setIntervalPingSec(unsigned sec);
	int getIntervalPingSec();
	void setPerMessageDeflate(bool val);
	bool getPerMessageDeflate();
};
