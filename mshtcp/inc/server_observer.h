// --------------------------------------------------------------------------
// This file is part of jnutils, made public 2023, (c) Jeff Nye
//
// jnutils is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// jnutils is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with jnutils; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
// ---------------------------------------------------------------------------
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
