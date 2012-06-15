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
#include "package.h"

upmf_package_t*
upmf_package_new (ucstring_t filen)
{
  xmlDocPtr doc;
  xmlNodePtr node;
  upmf_package_t *pack;

  doc = upmf_document_init (filen, "package");
  if (doc == NULL)
    {
      error (0, 0, _("Error processing package file, aborting"));
      exit (1);
    }

  node = xmlDocGetRootElement (doc);
  pack = UPMF_PACKAGE (malloc (sizeof (upmf_package_t)));  
  pack->name = xmlGetProp (node, XSTRING ("name"));
  node = node->xmlChildrenNode;

  while (node != NULL)
    {
      if (!xmlStrcmp (node->name, XSTRING ("description")))
	  pack->dscr = upmf_get_xstring (doc, node);
      if (!xmlStrcmp (node->name, XSTRING ("uri")))
	  pack->uri = upmf_get_xstring (doc, node);
      if (!xmlStrcmp (node->name, XSTRING ("uses")))
	  pack->uselist = upmf_use_make_list (doc, node, pack);
      node = node->next;
    }
  /* TODO Replace placeholders here. PV, PS, PN */
  return pack;
}

void
upmf_package_destroy (upmf_package_t *this)
{
  xmlFree (XSTRING (this->name));
  xmlFree (XSTRING (this->dscr));
  xmlFree (XSTRING (this->uri));
  free (this);
}

gl_list_t
upmf_package_tree_new (ucstring_t pkgname)
{
  upmf_find_pkgfile (pkgname);

  /*  free (filen);*/
}
