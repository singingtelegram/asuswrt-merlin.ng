/*
<:copyright-BRCM:2018:DUAL/GPL:standard

   Copyright (c) 2018 Broadcom 
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

#include <bdmf_system.h>
#include <bdmf_system_common.h>
#include <rdpa_api.h>
#include "tcpspdtest.h"

static bdmf_object_handle bdmf_udpspdtest_obj_h = NULL;

int udpspd_engine_init(void)
{
    int rc = 0;

#ifdef CONFIG_BCM_XRDP
    if (bdmf_udpspdtest_obj_h)
        return -1;

    rc = rdpa_udpspdtest_get(&bdmf_udpspdtest_obj_h);
    if (rc)
    {
        rc = bdmf_new_and_set(rdpa_udpspdtest_drv(), NULL, NULL, &bdmf_udpspdtest_obj_h);
        if (rc)
        {
            tc_err("Failed to create bdmf udpspdtest\n");
            return rc;
        }
    }

#endif    
    return rc;
}

int udpspd_engine_shutdown(void)
{
#ifdef CONFIG_BCM_XRDP
    if (!bdmf_udpspdtest_obj_h)
        return -1;

    bdmf_destroy(bdmf_udpspdtest_obj_h);
    bdmf_udpspdtest_obj_h = NULL;
#endif
    return 0;
}

