meta:
	ADDON_NAME = ofxIXWebSocket
	ADDON_DESCRIPTION = OpenFrameworks wrapper of the IXWebSocket library by @machinezone
	ADDON_AUTHOR = Ryo Hajika
	ADDON_TAGS = "websocket" "IXWebSocket" "network"
	ADDON_URL = https://github.com/ryohajika/ofxIXWebSocket.git

common:

	ADDON_INCLUDES += libs/IXWebSocket/IXBench.h
	ADDON_INCLUDES += libs/IXWebSocket/IXCancellationRequest.h
	ADDON_INCLUDES += libs/IXWebSocket/IXConnectionState.h
	ADDON_INCLUDES += libs/IXWebSocket/IXDNSLookup.h
	ADDON_INCLUDES += libs/IXWebSocket/IXExponentialBackoff.h
	ADDON_INCLUDES += libs/IXWebSocket/IXGetFreePort.h
	ADDON_INCLUDES += libs/IXWebSocket/IXGzipCodec.h
	ADDON_INCLUDES += libs/IXWebSocket/IXHttp.h
	ADDON_INCLUDES += libs/IXWebSocket/IXHttpClient.h
	ADDON_INCLUDES += libs/IXWebSocket/IXHttpServer.h
	ADDON_INCLUDES += libs/IXWebSocket/IXNetSystem.h
	ADDON_INCLUDES += libs/IXWebSocket/IXProgressCallback.h
	ADDON_INCLUDES += libs/IXWebSocket/IXSelectInterrupt.h
	ADDON_INCLUDES += libs/IXWebSocket/IXSelectInterruptFactory.h
	ADDON_INCLUDES += libs/IXWebSocket/IXSelectInterruptPipe.h
	ADDON_INCLUDES += libs/IXWebSocket/IXSetThreadName.h
	ADDON_INCLUDES += libs/IXWebSocket/IXSocket.h
	ADDON_INCLUDES += libs/IXWebSocket/IXSocketConnect.h
	ADDON_INCLUDES += libs/IXWebSocket/IXSocketFactory.h
	ADDON_INCLUDES += libs/IXWebSocket/IXSocketServer.h
	ADDON_INCLUDES += libs/IXWebSocket/IXSocketTLSOptions.h
	ADDON_INCLUDES += libs/IXWebSocket/IXStrCaseCompare.h
	ADDON_INCLUDES += libs/IXWebSocket/IXUdpSocket.h
	ADDON_INCLUDES += libs/IXWebSocket/IXUniquePtr.h
	ADDON_INCLUDES += libs/IXWebSocket/IXUrlParser.h
	ADDON_INCLUDES += libs/IXWebSocket/IXUserAgent.h
	ADDON_INCLUDES += libs/IXWebSocket/IXUtf8Validator.h
	ADDON_INCLUDES += libs/IXWebSocket/IXUuid.h
	ADDON_INCLUDES += libs/IXWebSocket/IXWebSocket.h
	ADDON_INCLUDES += libs/IXWebSocket/IXWebSocketCloseConstants.h
	ADDON_INCLUDES += libs/IXWebSocket/IXWebSocketCloseInfo.h
	ADDON_INCLUDES += libs/IXWebSocket/IXWebSocketErrorInfo.h
	ADDON_INCLUDES += libs/IXWebSocket/IXWebSocketHandshake.h
	ADDON_INCLUDES += libs/IXWebSocket/IXWebSocketHandshakeKeyGen.h
	ADDON_INCLUDES += libs/IXWebSocket/IXWebSocketHttpHeaders.h
	ADDON_INCLUDES += libs/IXWebSocket/IXWebSocketInitResult.h
	ADDON_INCLUDES += libs/IXWebSocket/IXWebSocketMessage.h
	ADDON_INCLUDES += libs/IXWebSocket/IXWebSocketMessageType.h
	ADDON_INCLUDES += libs/IXWebSocket/IXWebSocketOpenInfo.h
	ADDON_INCLUDES += libs/IXWebSocket/IXWebSocketPerMessageDeflate.h
	ADDON_INCLUDES += libs/IXWebSocket/IXWebSocketPerMessageDeflateCodec.h
	ADDON_INCLUDES += libs/IXWebSocket/IXWebSocketPerMessageDeflateOptions.h
	ADDON_INCLUDES += libs/IXWebSocket/IXWebSocketProxyServer.h
	ADDON_INCLUDES += libs/IXWebSocket/IXWebSocketSendInfo.h
	ADDON_INCLUDES += libs/IXWebSocket/IXWebSocketServer.h
	ADDON_INCLUDES += libs/IXWebSocket/IXWebSocketTransport.h
	ADDON_INCLUDES += libs/IXWebSocket/IXWebSocketVersion.h

osx:
	ADDON_INCLUDES += libs/IXWebSocket/IXSocketAppleSSL.h
	ADDON_LIBS += libs/IXWebSocket/lib/osx/libixwebsocket.a
	ADDON_FRAMEWORKS += Security
	ADDON_FRAMEWORKS += Foundation

	ADDON_SOURCES_EXCLUDE += libs/zlib-1.2.11/%
