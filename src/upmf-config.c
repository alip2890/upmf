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

#include "upmf-config.h"

upmf_config_t upmf_config;

int
upmf_config_init ()
{
  xmlDocPtr configdoc;
  xmlNodePtr node;
  char *filename = "upmf-settings.xml";
  size_t length = strlen (filename) + strlen (SYSCONFDIR) + 2;
  ustring_t filestring = USTRING (malloc (length));
  snprintf (filestring, length, "%s/%s", SYSCONFDIR, filename);

  configdoc = upmf_document_init (filestring, "settings");
  if (configdoc == NULL)
    {
      free (filestring);
      return FALSE;
    }

  node = xmlDocGetRootElement (configdoc);
  node = node->xmlChildrenNode;
  while (node != NULL)
    {
      if (!xmlStrcmp (node->name, XCSTRING ("enabled")))
	upmf_config.enabled = upmf_get_xstring (configdoc, node);
      if (!xmlStrcmp (node->name, XCSTRING ("packagefiles")))
	{	  
	  upmf_config.pkgfiledirs = upmf_list_init_from_doc (configdoc,
							     node, "dir");
	}

      if (!xmlStrcmp (node->name, XCSTRING ("packagedir")))
	upmf_config.packagedir = upmf_get_xstring (configdoc, node);

      if (!xmlStrcmp (node->name, XCSTRING ("cflags")))
	upmf_config.cflags = upmf_get_xstring (configdoc, node);

      if (!xmlStrcmp (node->name, XCSTRING ("cxxflags")))
	upmf_config.cxxflags = upmf_get_xstring (configdoc, node);

      if (!xmlStrcmp (node->name, XCSTRING ("chost")))
	upmf_config.chost = upmf_get_xstring (configdoc, node);

      if (!xmlStrcmp (node->name, XCSTRING ("makeopts")))
	upmf_config.makeopts = upmf_get_xstring (configdoc, node);

      if (!xmlStrcmp (node->name, XCSTRING ("upmfopts")))
	upmf_config.upmfopts = upmf_get_xstring (configdoc, node);

      if (!xmlStrcmp (node->name, XCSTRING ("stow")))
	upmf_config.stow = upmf_get_xstring (configdoc, node);

      if (!xmlStrcmp (node->name, XCSTRING ("features")))
	upmf_config.features = upmf_list_init_from_doc (configdoc, node,
							"feature");

      if (!xmlStrcmp (node->name, XCSTRING ("uses")))
	upmf_config.uses = upmf_list_init_from_doc (configdoc, node, "use");

      NEXT (node);
    }
  xmlFree (node);
  xmlFreeDoc (configdoc);
  free (filestring);
}

void
upmf_config_destroy (void)
{
  xmlFree (XSTRING (upmf_config.enabled));
  xmlFree (upmf_config.packagedir);
  xmlFree (upmf_config.cflags);
  xmlFree (upmf_config.cxxflags);
  xmlFree (upmf_config.chost);
  xmlFree (upmf_config.makeopts);
  xmlFree (upmf_config.upmfopts);
  xmlFree (upmf_config.stow);
  if (upmf_config.pkgfiledirs != NULL) gl_list_free (upmf_config.pkgfiledirs);
  if (upmf_config.features != NULL) gl_list_free (upmf_config.features);
  if (upmf_config.uses != NULL) gl_list_free (upmf_config.uses);
}
