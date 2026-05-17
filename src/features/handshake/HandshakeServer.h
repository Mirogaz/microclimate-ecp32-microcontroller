#pragma once

#include <WebServer.h>

#include "src/config/Config.h"
#include "src/domain/Mode.h"

class HandshakeServer {
  public:
	HandshakeServer();

	void begin(Config* config, Mode* mode, const char* deviceId);

	void tick();

  private:
	WebServer server;

	Config* cfg;
	Mode* mode;
	const char* deviceId;

	void handleGet();
	void handlePost();
};
