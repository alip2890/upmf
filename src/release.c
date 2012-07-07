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
#include "release.h"

upmf_release_t
upmf_release_new (xmlDocPtr doc, xmlNodePtr node, upmf_package_t parent)
{
  if (xmlStrcmp (node->name, "release"))
    {
      return NULL;
    }

  xstring_t patchbuffer = NULL;
  ustring_t patch_token = NULL;
  upmf_release_t temp = UPMF_RELEASE (malloc (sizeof (struct UpmfRelease)));
  temp->version = xmlGetProp (node, XSTRING ("version"));
  temp->revision = xmlGetProp (node, XSTRING ("revision"));
  temp->branch = xmlGetProp (node, XSTRING ("branch"));
  temp->patchlist = UPMF_PATCH_LIST_NEW;
  temp->deplist = UPMF_DEP_LIST_NEW;

  patchbuffer = xmlGetProp (node, XSTRING("patches"));
  /*while ((patch_token = strtok (patchbuffer, " ")) != NULL)
    {
      gl_list_node_t curpatch = gl_list_search (parent->patchlist,
						 UCPOINTER (patch_token));
      if (curpatch != NULL)
	gl_list_nx_add_last (temp->patchlist,
			  gl_list_node_value (parent->patchlist, curpatch));

      if (patchbuffer != NULL) xmlFree (patchbuffer);
      }*/

  xmlNodePtr child = node->xmlChildrenNode;
  while (child != NULL)
    {
      if (!xmlStrcmp (child->name, "uri"))
	{
	  xstring_t uribuffer = upmf_get_xstring (doc, child);	  
	  size_t pstring_len = strlen (temp->version) +
	    strlen (parent->name) + 2;
	  ustring_t pstring = USTRING (malloc (pstring_len));
	  
	  snprintf (pstring, pstring_len, "%s-%s", parent->name,
		    temp->version);
	  temp->uri = upmf_str_replace (uribuffer, "{PS}", pstring);

	  free (pstring);
	  xmlFree (uribuffer);
	}
      if (!xmlStrcmp (child->name, "deps"))
	upmf_dep_make_list (doc, child, parent, temp->deplist);
      if (!xmlStrcmp (child->name, "build"))
	temp->build = upmf_build_new (doc, child, parent);

      NEXT (child);
    }

  free (patchbuffer);

  return temp;
}

void
upmf_release_destroy (upmf_release_t this)
{
  if (this == NULL) return;

  xmlFree (this->version);
  xmlFree (this->revision);
  xmlFree (this->branch);
  xmlFree (this->uri);
  gl_list_free (this->patchlist);
  gl_list_free (this->deplist);
  upmf_build_destroy (this->build);
  free (this);
}

UPMF_DEFINE_LIST_FUN (release, "release")
UPMF_DEFINE_CMP_FUN (release, RELEASE, version)

