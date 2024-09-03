/*
<:copyright-BRCM:2020:DUAL/GPL:standard

   Copyright (c) 2020 Broadcom 
   All Rights Reserved

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License, version 2, as published by
the Free Software Foundation (the "GPL").

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.


A copy of the GPL is available at http://www.broadcom.com/licenses/GPLv2.php, or by
writing to the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
Boston, MA 02111-1307, USA.

:>
*/

#ifndef _TCPSPDTEST_VERSION_
#define _TCPSPDTEST_VERSION_

#include <generated/compile.h>


#define TCPSPDTEST_VERSION_MAJOR "$Change: 480908 $"  /* CL */
#define TCPSPDTEST_VERSION_EXT   ""  /* Extra version, empty by default, can be changed to any string for extra purpose(i.e. debug) */
#define TCPSPDTEST_VERSION_TIME  UTS_VERSION  /* use same one as Linux kernel */
#define TCPSPDTEST_VERSION_MINOR TCPSPDTEST_VERSION_EXT" "TCPSPDTEST_VERSION_TIME

#endif /* _TCPSPDTEST_VERSION_ */
