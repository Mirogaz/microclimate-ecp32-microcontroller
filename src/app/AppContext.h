#pragma once

#include <GyverPortal.h>
#include <Preferences.h>

#include "src/config/Config.h"
#include "src/domain/Mode.h"
#include "src/features/handshake/HandshakeServer.h"

extern Preferences g_prefs;
extern Config g_config;
extern Mode g_mode;
extern GyverPortal g_portal;
extern HandshakeServer g_handshake;
