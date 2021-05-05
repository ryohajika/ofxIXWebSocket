#include "ofxIXWebSocket.h"

ofxIXWebSocket::ofxIXWebSocket(){
    _host = "";
    _sub = "";
    _port = 0;
    _host_final = "";
    _ping_intvl_sec = 20;
    _b_per_msg_deflate = true;
    _b_verbose = true;
	tls_ = nullptr;
    
#if defined(TARGET_MINGW) || defined(TARGET_WINVS)
	ix::initNetSystem();
#endif
}

ofxIXWebSocket::~ofxIXWebSocket(){
	ws_.stop();
	if(tls_ != nullptr){
		delete tls_;
		tls_ = nullptr;
	}
#if defined(TARGET_MINGW) || defined(TARGET_WINVS)
	ix::uninitNetSystem();
#endif
}

void ofxIXWebSocket::init(std::string target_address, std::string sub_address, int target_port){
	if(_b_verbose){
		ofLogNotice() << __PRETTY_FUNCTION__;
	}
	
	if(!target_address.size()){
		ofLogError("ofxIXWebSocket", "you need to specify target address");
		return;
	}else{
		std::size_t _header_pos = target_address.find_first_of("ws://");
		std::size_t _secure_header_pos = target_address.find_first_of("wss://");
		
		if(_header_pos == std::string::npos || _secure_header_pos == std::string::npos){
			ofLogError("ofxIXWebSocket", "you need to specify WebSocket server address");
			return;
		}else{
			_host = target_address;
			_sub = sub_address;
			_port = target_port;
			
			// Secure connection check
			if(_secure_header_pos != std::string::npos){
				if(_b_verbose) ofLogNotice("ofxIXWebSocket", "TLS option enabling");
				ws_.setTLSOptions(*tls_);
			}
			
			if(_sub.size() < 1){
				_host_final = target_address + ':' + std::to_string(_port);
			}else{
				if(_sub[0] != '/'){
					_sub.insert(_sub.begin(), '/');
				}
				_host_final = target_address + ':' + std::to_string(_port) + _sub;
			}
			ofLogNotice() << "Connecting to: " + _host_final;
			
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

void ofxIXWebSocket::wsEventCallback(const ix::WebSocketMessagePtr &msg){
    if(_b_verbose){
        ofLogNotice() << __PRETTY_FUNCTION__;
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
				std::string m = msg->str;
				ofNotifyEvent(onPongEvt, m);
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
				std::string m = msg->str;
				ofNotifyEvent(onMessageEvt, m);
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
        ofLogNotice() << __PRETTY_FUNCTION__;
    }
    this->init(target_address, "", target_port);
}

void ofxIXWebSocket::setup(std::string target_address,
                           std::string sub_address,
                           int target_port){
	if(_b_verbose){
		ofLogNotice() << __PRETTY_FUNCTION__;
	}
	this->init(target_address, sub_address, target_port);
}

void ofxIXWebSocket::setup(std::string target_address,
						   std::string sub_address,
						   std::string cacert_filepath,
						   int target_port){
	if(_b_verbose){
		ofLogNotice() << __PRETTY_FUNCTION__;
	}
	this->setCacertFile(cacert_filepath);
	this->init(target_address, sub_address, target_port);
}

void ofxIXWebSocket::setCacertFile(std::string filepath){
	if(_b_verbose){
		ofLogNotice() << __PRETTY_FUNCTION__;
	}
	
	if(tls_ == nullptr){
		tls_ = new ix::SocketTLSOptions;
	}
	if(ofFilePath::isAbsolute(filepath)){
		tls_->caFile = filepath;
	}else{
		tls_->caFile = ofFilePath::getAbsolutePath(filepath);
	}
	
	if(_b_verbose){
		ofLogNotice() << "CACert: " << (tls_->isValid() ? "OKAY" : "BAD");
	}
	tls_->tls = true;
	
	if(_b_verbose){
		ofLogNotice() << "CACert file: " << tls_->caFile;
	}
}

void ofxIXWebSocket::setVerbose(bool val){
    if(_b_verbose){
        ofLogNotice() << __PRETTY_FUNCTION__;
    }
    _b_verbose = val;
}
inline bool ofxIXWebSocket::getVerbose(){
    if(_b_verbose){
        ofLogNotice() << __PRETTY_FUNCTION__;
    }
    return _b_verbose;
}

void ofxIXWebSocket::connect(){
	ws_.start();
}
void ofxIXWebSocket::disconnect(){
	ws_.stop();
}

void ofxIXWebSocket::sendMessage(std::string msg_str){
	ws_.send(msg_str);
}
void ofxIXWebSocket::sendMessage(char *msg_chars){
	ws_.send(std::string(msg_chars));
}

void ofxIXWebSocket::setIntervalPingSec(unsigned int sec){
	_ping_intvl_sec = sec;
	ws_.setPingInterval(_ping_intvl_sec);
}
inline int ofxIXWebSocket::getIntervalPingSec(){
	return _ping_intvl_sec;
}

void ofxIXWebSocket::setPerMessageDeflate(bool val){
	_b_per_msg_deflate = val;
	_b_per_msg_deflate ? ws_.enablePerMessageDeflate()
					   : ws_.disablePerMessageDeflate();
}
inline bool ofxIXWebSocket::getPerMessageDeflate(){
	return _b_per_msg_deflate;
}
