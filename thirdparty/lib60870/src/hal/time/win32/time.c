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

#include <windows.h>

#include "hal_time.h"

uint64_t
Hal_getTimeInMs()
{
	FILETIME ft;
	uint64_t now;
	static const uint64_t DIFF_TO_UNIXTIME = 11644473600000LL;
	GetSystemTimeAsFileTime(&ft);
	now = (LONGLONG)ft.dwLowDateTime + ((LONGLONG)(ft.dwHighDateTime) << 32LL);
	return (now / 10000LL) - DIFF_TO_UNIXTIME;
}
