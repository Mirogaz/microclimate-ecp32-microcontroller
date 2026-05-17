#pragma once

#include <WebServer.h>

#include "Config.h"
#include "ModeEnum.h"

class HandshakeServer {
  public:
	void begin(Config* config, Mode* mode, const char* name);

	void tick();

  private:
	WebServer server = WebServer(80);

	Config* cfg;
	Mode* mode;

	const char* deviceName;

	void handleGet();
	void handlePost();
};