/**
 *    Copyright (C) 2015 splone UG
 *
 *    This program is free software: you can redistribute it and/or  modify
 *    it under the terms of the GNU Affero General Public License, version 3,
 *    as published by the Free Software Foundation.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU Affero General Public License for more details.
 *
 *    You should have received a copy of the GNU Affero General Public License
 *    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <sodium.h>

#include "sb-common.h"
#include "rpc/sb-rpc.h"

#define ENV_VAR_LISTEN_ADDRESS    "SPLONEBOX_LISTEN_ADDRESS"

int8_t verbose_level;

int main(int argc, char **argv)
{
  optparser(argc, argv);

  /* initialize libsodium */
  if (sodium_init() == -1) {
    LOG_ERROR("Failed to initialize sodium.");
  }

  /* initialize event queue */
  if (event_initialize() == -1) {
    LOG_ERROR("Failed to initialize event queue.");
  }

  /* initialize connections */
  if (connection_init() == -1) {
    LOG_ERROR("Failed to initialise connections.");
  }

  /* initialize server */
  string env = cstring_to_string(getenv(ENV_VAR_LISTEN_ADDRESS));

  if (!env.str) {
    LOG_ERROR(
      "Environment Variable 'SPLONEBOX_LISTEN_ADDRESS' is not set, abort.");
  }

  if (server_init() == -1) {
    LOG_ERROR("Failed to initialise server.");
  }

  if (server_start(env) == -1) {
    LOG_ERROR("Failed to start server.");
  }

  uv_run(uv_default_loop(), UV_RUN_DEFAULT);

  return (0);
}