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

upmf_package_t
upmf_package_new (ucstring_t filen)
{
  xmlDocPtr doc;
  xmlNodePtr node;
  upmf_package_t pack;

  doc = upmf_document_init (filen, "package");
  if (doc == NULL)
    {
      error (1, 0, _("Error processing package file, aborting"));
    }

  node = xmlDocGetRootElement (doc);
  pack = UPMF_PACKAGE (malloc (sizeof (struct UpmfPackage)));  
  pack->name = xmlGetProp (node, XSTRING ("name"));
  node = node->xmlChildrenNode;

  while (node != NULL)
    {
      if (!xmlStrcmp (node->name, XSTRING ("description")))
	pack->dscr = upmf_get_xstring (doc, node);
      if (!xmlStrcmp (node->name, XSTRING ("uri")))
	pack->uri = upmf_get_xstring (doc, node);
      if (!xmlStrcmp (node->name, XSTRING ("license")))
	pack->license = upmf_get_xstring (doc, node);
      if (!xmlStrcmp (node->name, XSTRING ("uses")))
	pack->uselist = upmf_use_make_list (doc, node, pack);
      if (!xmlStrcmp (node->name, XSTRING ("patches")))
	pack->patchlist = upmf_patch_make_list (doc, node, pack);
      if (!xmlStrcmp (node->name, XSTRING ("releases")))
	pack->releaselist = upmf_release_make_list (doc, node, pack);
      node = node->next;
    }
  /* NOTE Placeholders (PS, PV, PN) need to replaced when parsing
     releases, because package version is not determined at this stage. */

  xmlFreeDoc (doc);
  return pack;
}

void
upmf_package_destroy (upmf_package_t this)
{
  xmlFree (XSTRING (this->name));
  xmlFree (XSTRING (this->dscr));
  xmlFree (XSTRING (this->uri));
  xmlFree (XSTRING (this->license));
  gl_list_free (this->uselist);
  gl_list_free (this->patchlist);
  gl_list_free (this->releaselist);
  free (this);
}

gl_list_t
upmf_package_tree_new (ucstring_t pkgname)
{
  ustring_t filen = upmf_package_find_file (pkgname);
  if (filen != NULL)
    {
      upmf_package_t top_pack = upmf_package_new (filen);
      printf ("Package: %s\nDescription: %s\nSource: %s\n\n",
	      top_pack->name, top_pack->dscr, top_pack->uri);

      upmf_package_destroy (top_pack);
      free (filen);
    }
  else
    {
      error (1, 0, _("Error processing package file, aborting"));
    }
  return NULL;
}

ustring_t
upmf_package_find_file (ucstring_t pkgname)
{
  size_t listlen, pos;
  ucstring_t pkgfiledir;
  ustring_t pkgname_cpy, pcat, pname, pfilestr = NULL;

  pkgname_cpy = strdup (pkgname);
  pcat = strtok (pkgname_cpy, "/");
  pname = strtok (NULL, "/");
  if (pname == NULL)
    {
      error (0, 0, _("No section specified"));
      printf (_("Format for package names is `section/name'\n"));
      free (pkgname_cpy);
      return NULL;
    }
  
  listlen = gl_list_size (upmf_config.pkgfiledirs);
  for (pos = 0; pos < listlen; pos++)
    {
      pkgfiledir = UCSTRING (gl_list_get_at (upmf_config.pkgfiledirs, pos));
      size_t pfilesize = strlen (pkgfiledir) + strlen (pkgname) + 6;
      pfilestr = USTRING (realloc (pfilestr, pfilesize));
      snprintf (pfilestr, pfilesize, "%s/%s.xml", pkgfiledir, pkgname);
      struct stat pstat;
      if (stat (pfilestr, &pstat) == ENOENT)
	continue;
      else
	{
	  if (S_ISREG (pstat.st_mode))
	    {
	      free (pkgname_cpy);
	      return pfilestr;
	    }
	}
    }

  free (pfilestr);
  free (pkgname_cpy);

  error (0, 0, _("No package file found"));
  return NULL;
}
