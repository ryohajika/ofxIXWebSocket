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
                ofNotifyEvent(onOpenEvt, msg->openInfo.headers);
            }
            break;
        case ix::WebSocketMessageType::Close:
            {
            
            }
            break;
        case ix::WebSocketMessageType::Error:
            {
            
            }
            break;
        case ix::WebSocketMessageType::Ping:
            {
            
            }
            break;
        case ix::WebSocketMessageType::Pong:
            {
            
            }
            break;
        case ix::WebSocketMessageType::Message:
            {
            
            }
            break;
        case ix::WebSocketMessageType::Fragment:
            {
            
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
