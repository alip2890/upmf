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
#include "archive.h"

upmf_archive_t
upmf_archive_new (xmlDocPtr doc, xmlNodePtr node, upmf_package_t parent)
{
  if (xmlStrcmp (node->name, XSTRING ("archive"))) return NULL;
  
  upmf_archive_t temparch = UPMF_ARCHIVE (malloc (sizeof
						  (struct UpmfArchive)));

  temparch->name = xmlGetProp (node, XSTRING ("name"));
  temparch->prepare_hook = UPMF_COMMAND_LIST_NEW;
  temparch->configure_hook = UPMF_COMMAND_LIST_NEW;
  temparch->commands = UPMF_COMMAND_LIST_NEW;
  
  xmlNodePtr child = node->xmlChildrenNode;
  while (child != NULL)
    {
      if (!xmlStrcmp (child->name, XSTRING ("hook")))
	{
	  xstring_t buf = NULL;
	  buf = xmlGetProp (child, XSTRING ("type"));
	  if (!xmlStrcmp (buf, XSTRING ("prepare")))
	    upmf_command_make_list (doc, node, parent, temparch->prepare_hook);
	  if (!xmlStrcmp (buf, XSTRING ("configure")))
	    upmf_command_make_list (doc, node, parent,
				    temparch->configure_hook);
	  xmlFree (buf);
	}
      if (!xmlStrcmp (node->name, XSTRING ("commands")))
	upmf_command_make_list (doc, node, parent, temparch->commands);
      
      NEXT (child);
    }

  return temparch;
}

void
upmf_archive_destroy (upmf_archive_t this)
{
  if (this == NULL) return;

  xmlFree (this->name);
  if (this->configure_hook != NULL) gl_list_free (this->configure_hook);
  if (this->prepare_hook != NULL) gl_list_free (this->prepare_hook);
  if (this->commands != NULL) gl_list_free (this->commands);
  free (this);
}

UPMF_DEFINE_LIST_FUN (archive, "archive")
UPMF_DEFINE_CMP_FUN (archive, ARCHIVE, name)
