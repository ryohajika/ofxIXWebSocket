meta:
	ADDON_NAME = ofxIXWebSocket
	ADDON_DESCRIPTION = OpenFrameworks wrapper of the IXWebSocket library by @machinezone
	ADDON_AUTHOR = Ryo Hajika
	ADDON_TAGS = "websocket" "IXWebSocket" "network"
	ADDON_URL = https://github.com/ryohajika/ofxIXWebSocket.git

common:

	ADDON_INCLUDES += libs/IXWebSocket/ixwebsocket
	ADDON_INCLUDES += libs/IXWebSocket/third_party/cli11
	ADDON_INCLUDES += libs/IXWebSocket/third_party/cpp-linenoise
	ADDON_INCLUDES += libs/IXWebSocket/third_party/msgpack11
	ADDON_INCLUDES += libs/openssl/include

	ADDON_SOURCES += libs/IXWebSocket/ixwebsocket
	ADDON_SOURCES += libs/IXWebSocket/third_party/cpp-linenoise
	ADDON_SOURCES += libs/IXWebSocket/third_party/msgpack11

	ADDON_SOURCES_EXCLUDE += libs/IXWebSocket/%.cpp
	ADDON_SOURCES_EXCLUDE += libs/IXWebSocket/test/%
	ADDON_SOURCES_EXCLUDE += libs/IXWebSocket/ws/%
	ADDON_SOURCES_EXCLUDE += libs/IXWebSocket/third_party/cpp-linenoise/example/%

osx:
	ADDON_LIBS += libs/openssl/lib/osx/crypto.a
	ADDON_LIBS += libs/openssl/lib/osx/ssl.a

	ADDON_SOURCES_EXCLUDE += libs/zlib-1.2.11/%
