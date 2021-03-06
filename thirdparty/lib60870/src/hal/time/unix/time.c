/*
 *  Copyright 2016 MZ Automation GmbH
 *
 *  This file is part of lib60870-C
 *
 *  lib60870-C is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  lib60870-C is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with lib60870-C.  If not, see <http://www.gnu.org/licenses/>.
 *
 *  See COPYING file for the complete license text.
 */

#include <time.h>
#include <stdint.h>

#include "hal_time.h"

#ifdef CONFIG_SYSTEM_HAS_CLOCK_GETTIME
uint64_t
Hal_getTimeInMs()
{
	struct timespec tp;
	clock_gettime(CLOCK_REALTIME, &tp);
	return ((uint64_t) tp.tv_sec) * 1000LL + (tp.tv_nsec / 1000000);
}
#else

#include <sys/time.h>

uint64_t
Hal_getTimeInMs()
{
	struct timeval now;
	gettimeofday(&now, NULL);
	return ((uint64_t) now.tv_sec * 1000LL) + (now.tv_usec / 1000);
}

#endif

