/*
 * $Id$
 *
 * Copyright (C) 2001-2003 FhG Fokus
 *
 * This file is part of Kamailio, a free SIP server.
 *
 * Kamailio is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version
 *
 * Kamailio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License 
 * along with this program; if not, write to the Free Software 
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * History:
 * ========
 *
 * 2006-11-28 Added a new function to the usrloc_api, to retrieve the number
 *            of registered users.  (Jeffrey Magder - SOMA Networks)
 */

/*! \file
 *  \brief USRLOC - module API exports interfaces
 *  \ingroup usrloc
 *
 * - Module \ref usrloc
 */

#include "usrloc.h"
#include "dlist.h"
#include "urecord.h"
#include "ucontact.h"
#include "udomain.h"
#include "../../sr_module.h"
#include "ul_mod.h"

/*! nat branch flag */
extern unsigned int nat_bflag;
/*! flag to protect against wrong initialization */
extern unsigned int init_flag;


/*!
 * \brief usrloc module API export bind function
 * \param api usrloc API
 * \return 0 on success, -1 on failure
 */
int bind_usrloc(usrloc_api_t* api)
{
	if (!api) {
		LM_ERR("invalid parameter value\n");
		return -1;
	}
	if (init_flag==0) {
		LM_ERR("configuration error - trying to bind to usrloc module"
				" before being initialized\n");
		return -1;
	}

	api->register_udomain   = register_udomain;
	api->get_udomain        = get_udomain;
	api->get_all_ucontacts  = get_all_ucontacts;
	api->get_all_ucontacts_opt = get_all_ucontacts_opt;
	api->insert_urecord     = insert_urecord;
	api->delete_urecord     = delete_urecord;
	api->get_urecord        = get_urecord;
	api->lock_udomain       = lock_udomain;
	api->unlock_udomain     = unlock_udomain;
	api->release_urecord    = release_urecord;
	api->insert_ucontact    = insert_ucontact;
	api->delete_ucontact    = delete_ucontact;
	api->get_ucontact       = get_ucontact;
	api->update_ucontact    = update_ucontact;
	api->register_ulcb      = register_ulcb;
	api->get_aorhash        = ul_get_aorhash;

	api->get_urecord_by_ruid      = get_urecord_by_ruid;
	api->get_ucontact_by_instance = get_ucontact_by_instance;

	api->use_domain = use_domain;
	api->db_mode    = db_mode;
	api->nat_flag   = nat_bflag;

	return 0;
}