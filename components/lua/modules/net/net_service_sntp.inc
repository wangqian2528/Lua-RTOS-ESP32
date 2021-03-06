/*
 * Copyright (C) 2015 - 2018, IBEROXARXA SERVICIOS INTEGRALES, S.L.
 * Copyright (C) 2015 - 2018, Jaume Olivé Petrus (jolive@whitecatboard.org)
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the <organization> nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *     * The WHITECAT logotype cannot be changed, you can remove it, but you
 *       cannot change it in any way. The WHITECAT logotype is:
 *
 *          /\       /\
 *         /  \_____/  \
 *        /_____________\
 *        W H I T E C A T
 *
 *     * Redistributions in binary form must retain all copyright notices printed
 *       to any local or remote output device. This include any reference to
 *       Lua RTOS, whitecatboard.org, Lua, and other copyright notices that may
 *       appear in the future.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Lua RTOS, Lua SNTP net module
 *
 */

#include "net.h"

#include "lwip/err.h"
#include "lwip/apps/sntp.h"

#include <drivers/net.h>

static u8_t _sntp_running = 0;

static int lsntp_start(lua_State* L) {
	const char* ntp_server = luaL_optstring(L, 1, "pool.ntp.org");

	sntp_setoperatingmode (SNTP_OPMODE_POLL);
	sntp_setservername(0, (char*)ntp_server);
	sntp_init();

	_sntp_running = 1;
	return 0;
}

static int lsntp_stop(lua_State* L) {
	sntp_stop();
	_sntp_running = 0;
	return 0;
}

static int lsntp_running( lua_State* L ) {
	lua_pushboolean(L, _sntp_running);
	return 1;
}

static const LUA_REG_TYPE sntp_map[] = {
	{ LSTRKEY("start"  ), LFUNCVAL( lsntp_start   ) },
	{ LSTRKEY("stop"   ), LFUNCVAL( lsntp_stop    ) },
	{ LSTRKEY("running"), LFUNCVAL( lsntp_running ) },
	{ LNILKEY,LNILVAL }
};

