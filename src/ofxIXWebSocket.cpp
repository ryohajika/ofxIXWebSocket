#include "ofxIXWebSocket.h"

ofxIXWebSocket::ofxIXWebSocket(){
    _host = "";
    _sub = "";
    _port = 0;
    _host_final = "";
    _ping_intvl_sec = 20;
    _b_per_msg_deflate = true;
    _b_verbose = true;
    
#if defined(TARGET_MINGW) || defined(TARGET_WINVS)
	ix::initNetSystem();
#endif
}

ofxIXWebSocket::~ofxIXWebSocket(){
#if defined(TARGET_MINGW) || defined(TARGET_WINVS)
	ix::uninitNetSystem();
#endif
}

void ofxIXWebSocket::wsEventCallback(const ix::WebSocketMessagePtr &msg){
    if(_b_verbose){
        ofLogNotice() << __PRETTY_FUNCTION__ << std::endl;
    }
    
    switch (msg->type) {
        case ix::WebSocketMessageType::Open:
            {
				ofLogNotice("ofxIXWebSocket", "connected!");
				
				if(_b_verbose){
					OFX_WS_BEGIN_MESSAGE
					{
						for(auto it : msg->openInfo.headers){
							std::cout << it.first << ": " << it.second << std::endl;
						}
					}
					OFX_WS_END_MESSAGE
				}
                ofNotifyEvent(onOpenEvt, msg->openInfo.headers);
            }
            break;
        case ix::WebSocketMessageType::Close:
            {
				ofLogNotice("ofxIXWebSocket", "disconnected!");
				
				if(_b_verbose){
					OFX_WS_BEGIN_MESSAGE
					{
						std::cout << msg->closeInfo.reason
							<< "@" << msg->closeInfo.code << std::endl;
					}
					OFX_WS_END_MESSAGE
				}
				std::pair<uint16_t, std::string> _pair(msg->closeInfo.code,
													   msg->closeInfo.reason);
				ofNotifyEvent(onCloseEvt, _pair);
            }
            break;
        case ix::WebSocketMessageType::Error:
            {
				ofLogNotice("ofxIXWebSocket", "error");
				
				if(_b_verbose){
					OFX_WS_BEGIN_MESSAGE
					{
						std::cout << "Error: " << msg->errorInfo.reason << std::endl;
						std::cout << "retries count: " << msg->errorInfo.retries << std::endl;
						std::cout << "Wait time (MS): " << msg->errorInfo.wait_time << std::endl;
						std::cout << "HTTP Status: " << msg->errorInfo.http_status << std::endl;
					}
					OFX_WS_END_MESSAGE
				}
				ofNotifyEvent(onErrorEvt, msg->errorInfo);
            }
            break;
        case ix::WebSocketMessageType::Ping:
        case ix::WebSocketMessageType::Pong:
            {
				ofLogNotice("ofxIXWebSocket", "ping/pong");
				
				if(_b_verbose){
					OFX_WS_BEGIN_MESSAGE
					{
						std::cout << "Pong data: " << msg->str << std::endl;
					}
					OFX_WS_END_MESSAGE
				}
				ofNotifyEvent(onPongEvt, msg->str);
            }
            break;
        case ix::WebSocketMessageType::Message:
            {
				if(_b_verbose){
					OFX_WS_BEGIN_MESSAGE
					{
						std::cout << "Received: " << msg->str << std::endl;
					}
					OFX_WS_END_MESSAGE
				}
				ofNotifyEvent(onMessageEvt, msg->str);
            }
            break;
        case ix::WebSocketMessageType::Fragment:
            {
				if(_b_verbose){
					OFX_WS_BEGIN_MESSAGE
					{
						std::cout << "FRGMT received: " << msg->str << std::endl;
					}
					OFX_WS_END_MESSAGE
				}
            }
            break;
    }
}

void ofxIXWebSocket::setup(std::string target_address,
                           int target_port){
    if(_b_verbose){
        ofLogNotice() << __PRETTY_FUNCTION__ << std::endl;
    }
    this->setup(target_address, "", target_port);
}

void ofxIXWebSocket::setup(std::string target_address,
                           std::string sub_address,
                           int target_port){
    if(_b_verbose){
        ofLogNotice() << __PRETTY_FUNCTION__ << std::endl;
    }
    
    if(!target_address.size()){
        ofLogError("ofxIXWebSocket", "you need to specify target address");
        return;
    }else{
        if((target_address.find("ws://") == std::string::npos)
            || (target_address.find("wss://") == std::string::npos)){
            ofLogError("ofxIXWebSocket", "you need to specify WebSocket server address");
            return;
        }else{
            _host = target_address;
            _sub = sub_address;
            _port = target_port;
            
            if(_sub.size() < 1){
                _host_final = target_address + ':' + std::to_string(_port);
            }else{
                if(_sub[0] != '/'){
                    _sub.insert(_sub.begin(), '/');
                }
                _host_final = target_address + ':' + std::to_string(_port) + _sub;
            }
            ofLogNotice() << "Connecting to: " + _host_final << std::endl;
            
            ws_.setUrl(_host_final);
            ws_.setPingInterval(_ping_intvl_sec);
            _b_per_msg_deflate ? ws_.enablePerMessageDeflate()
                               : ws_.disablePerMessageDeflate();
            ws_.setOnMessageCallback(std::bind(&ofxIXWebSocket::wsEventCallback,
                                               this,
                                               std::placeholders::_1));
        }
    }
}

void ofxIXWebSocket::setVerbose(bool val){
    if(_b_verbose){
        ofLogNotice() << __PRETTY_FUNCTION__ << std::endl;
    }
    _b_verbose = val;
}
inline bool ofxIXWebSocket::getVerbose(){
    if(_b_verbose){
        ofLogNotice() << __PRETTY_FUNCTION__ << std::endl;
    }
    return _b_verbose;
}

void ofxIXWebSocket::connect(){
	
}
void ofxIXWebSocket::disconnect(){
	
}

void ofxIXWebSocket::sendMessage(std::string msg_str){
	
}
void ofxIXWebSocket::sendMessage(char *msg_chars){
	
}

void ofxIXWebSocket::setIntervalPingSec(unsigned int sec){
	
}
inline int ofxIXWebSocket::getIntervalPingSec(){
	
}

void ofxIXWebSocket::setPerMessageDeflate(bool val){
	
}
inline bool ofxIXWebSocket::getPerMessageDeflate(){
	
}
