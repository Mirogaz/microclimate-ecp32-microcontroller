#pragma once

#include <WebServer.h>

#include "src/config/Config.h"
#include "src/domain/Mode.h"

class HandshakeServer {
  public:
	void begin(Config* config, Mode* mode, const char* name);

	void tick();

  private:
	WebServer server;

	Config* cfg;
	Mode* mode;

	const char* deviceName;

	void handleGet();
	void handlePost();
};
