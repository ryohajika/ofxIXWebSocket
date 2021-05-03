// originally IXWebSocket (https://github.com/machinezone/IXWebSocket)
// OF addon created by Ryo Hajika (https://github.com/ryohajika/ofxIXWebSocket)

#pragma once

#include "ofMain.h"

#include "IXNetSystem.h"
#include "IXWebSocket.h"

class ofxIXWebSocket {
private:
    void wsEventCallback(const ix::WebSocketMessagePtr & msg);
    ix::WebSocket ws_;
	std::string _host;
    std::string _sub;
	int _port;
    std::string _host_final;
	int _ping_intvl_sec;
    bool _b_per_msg_deflate;
    bool _b_verbose;
	
public:
	ofxIXWebSocket();
	~ofxIXWebSocket();
	
	void setup(std::string target_address,
			   int target_port);
    void setup(std::string target_address,
               std::string sub_address,
               int target_port);
    void setVerbose(bool val);
    bool getVerbose();
	void connect();
	void disconnect();
	void sendMessage(std::string msg_str);
	void sendMessage(char* msg_chars);
	
	void setIntervalPingSec(unsigned sec);
	int getIntervalPingSec();
	void setPerMessageDeflate(bool val);
	bool getPerMessageDeflate();
 
    ofEvent<ix::WebSocketHttpHeaders> onOpenEvt;
};
