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

upmf_use_t*
upmf_use_new (xmlDocPtr doc, xmlNodePtr node)
{
  upmf_use_t *tempuse = (upmf_use_t*) malloc (sizeof (upmf_use_t));
  tempuse->name = xmlGetProp (node, XSTRING ("name"));
  tempuse->dscr = upmf_get_xstring (doc, node);
  /* Here should be checked whether a use is set or not, for now always true */
  tempuse->isset = TRUE;
  return tempuse;
}

void
upmf_use_destroy (upmf_use_t *this)
{
  xmlFree (XSTRING (this->name));
  xmlFree (XSTRING (this->dscr));
  free (this);
}

gl_list_t
upmf_use_make_list (xmlDocPtr doc, xmlNodePtr node, upmf_package_t *pack)
{
  xmlNodePtr usenode = node->xmlChildrenNode;
  gl_list_t uselist = gl_list_nx_create_empty (GL_LINKED_LIST, NULL, NULL,
					       NULL, FALSE);
  while (usenode != NULL)
    {
      if (!xmlStrcmp (usenode->name, XSTRING ("use")))
	{
	  upmf_use_t *tempuse = upmf_use_new (doc, node);
	  gl_list_nx_add_last (uselist, UCPOINTER (tempuse));
	}
      usenode = usenode->next;
    }
  /*xmlFree (usenode);*/
  return uselist;
}
