// --------------------------------------------------------------------
// Jeff Nye (c) 2023, see jnutils/LICENSE and jnutils/README.md
// --------------------------------------------------------------------
#pragma once

#include "client.h"
#include <string>

typedef void (incoming_packet_func)(const Client & client, const char * msg,
                                    size_t size);

typedef incoming_packet_func* incoming_packet_func_t;
typedef void (disconnected_func)(const Client & client);
typedef disconnected_func* disconnected_func_t;

struct server_observer_t {

	std::string wantedIp;
	incoming_packet_func_t incoming_packet_func;
	disconnected_func_t disconnected_func;

	server_observer_t() {
		wantedIp = "";
		incoming_packet_func = NULL;
		disconnected_func = NULL;
	}
};
