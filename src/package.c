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
  pack->section = xmlGetProp (node, XSTRING ("section"));
  pack->uselist = UPMF_USE_LIST_NEW;
  pack->patchlist = UPMF_PATCH_LIST_NEW;
  pack->releaselist = UPMF_RELEASE_LIST_NEW;

  node = node->xmlChildrenNode;
  while (node != NULL)
    {
      if (!xmlStrcmp (node->name, XSTRING ("description")))
	pack->dscr = upmf_get_xstring (doc, node);
      if (!xmlStrcmp (node->name, XSTRING ("license")))
	pack->license = upmf_get_xstring (doc, node);
      if (!xmlStrcmp (node->name, XSTRING ("uses")))
	upmf_use_make_list (doc, node, pack, pack->uselist);
      if (!xmlStrcmp (node->name, XSTRING ("patches")))
	upmf_patch_make_list (doc, node, pack, pack->patchlist);
      if (!xmlStrcmp (node->name, XSTRING ("releases")))
	{
	  upmf_release_make_list (doc, node, pack, pack->releaselist);
	}
      NEXT (node);
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
  xmlFree (XSTRING (this->section));
  xmlFree (XSTRING (this->dscr));
  xmlFree (XSTRING (this->license));
  gl_list_free (this->uselist);
  gl_list_free (this->patchlist);
  gl_list_free (this->releaselist);
  free (this);
}

void
upmf_package_deplist_new (ucstring_t pname, gl_list_t plist)
{
  ustring_t filen = upmf_package_find_file (pname);
  if (filen != NULL)
    {
      /* No need to check for NULL pointer, since upmf_package_new
	 aborts the program in case of error */
      upmf_package_t pack = upmf_package_new (filen);

      /* Check for duplicate */
      for (int mpos = gl_list_size (plist) -1; mpos >= 0; mpos--)
	{
	  ucpointer_t tpack = gl_list_get_at (plist, mpos);
	  if (upmf_package_cmp (UCPOINTER (pack), tpack))
	    {
	      upmf_package_destroy (pack);
	      free (filen);
	      return;
	    }
	}

      gl_list_nx_add_last (plist, UCPOINTER (pack));
      free (filen);

      upmf_release_t newestrel = UPMF_RELEASE (gl_list_get_at
					       (pack->releaselist, 0));
      if (newestrel == NULL)
	return;

      /* Go through the dependency list and add them to the list,
	 do this recursively */
      for (int pos = 0; pos < gl_list_size (newestrel->deplist); pos++)
	{
	  upmf_dep_t dep = UPMF_DEP (gl_list_get_at
				     (newestrel->deplist, pos));
	  
	  if (dep->use == NULL || upmf_use_isset (dep->use))
	    upmf_package_deplist_new (dep->name, plist);
	}
    }
  else
    {
      error (1, 0, _("Error processing package information, aborting"));
    }
}

ustring_t
upmf_package_find_file (ucstring_t pkgname)
{
  size_t listlen, pos;
  ucstring_t pkgfiledir;
  ustring_t pkgname_cpy, pcat, pname, pfilestr = NULL;

  if (!arguments.quiet)
    printf (_("Looking up %s\n"), pkgname);

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

  error (0, 0, _("Package file not found for %s"), pkgname);
  return NULL;
}

bool
upmf_package_cmp (ucpointer_t p1, ucpointer_t p2)
{
  upmf_package_t pp1 = UPMF_PACKAGE (p1);
  upmf_package_t pp2 = UPMF_PACKAGE (p2);
  if (!xmlStrcmp (pp1->name, pp2->name)
      && !xmlStrcmp (pp1->section, pp2->section))
    return TRUE;
  return FALSE;
}
