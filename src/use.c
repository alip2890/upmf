/* Copyright (C) 2012 Aljosha Papsch <papsch.al@googlemail.com>

   This file is part of Upmf.

   Upmf is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   Upmf is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with Upmf.  If not, see <http://www.gnu.org/licenses/>. */

#include <config.h>
#include "use.h"

upmf_use_t
upmf_use_new (xmlDocPtr doc, xmlNodePtr node, upmf_package_t par)
{
  upmf_use_t tempuse = UPMF_USE (malloc (sizeof (struct UpmfUse)));
  tempuse->name = xmlGetProp (node, XSTRING ("name"));
  tempuse->dscr = upmf_get_xstring (doc, node);
  /* Here should be checked whether a use is set or not, for now always true */
  tempuse->isset = TRUE;
  return tempuse;
}

void
upmf_use_destroy (upmf_use_t this)
{
  xmlFree (XSTRING (this->name));
  xmlFree (XSTRING (this->dscr));
  free (this);
}

bool
upmf_use_isset (ustring_t name)
{
  for (int pos = 0; pos < gl_list_size (upmf_config.uses); pos++)
    {
      printf ("comparing %s with %s\n", gl_list_get_at
	      (upmf_config.uses, pos), name);
	      
      if (!xmlStrcmp (gl_list_get_at (upmf_config.uses, pos), XSTRING (name)))
	return TRUE;
    }

  return FALSE;
}

UPMF_DEFINE_LIST_FUN (use, "use")
UPMF_DEFINE_CMP_FUN (use, USE, name)

