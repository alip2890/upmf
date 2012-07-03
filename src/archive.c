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
  temparch->name = xmlGetProp (node, XSTRING ("auto"));
  xmlNodePtr child = node->xmlChildrenNode;
  while (child != NULL)
    {
      if (!xmlStrcmp (node->name, XSTRING ("hook")))
	{
	  if (!xmlStrcmp (xmlGetProp (child, "type"), XSTRING ("prepare")))
	    temparch->prepare_hook = upmf_command_make_list (doc, child,
							     parent);
	  if (!xmlStrcmp (xmlGetProp (child, "type"), XSTRING ("configure")))
	    temparch->configure_hook = upmf_command_make_list (doc, child,
							       parent);
	}
      if (!xmlStrcmp (node->name, XSTRING ("commands")))
	temparch->commands = upmf_command_make_list (doc, child, parent);
      
      NEXT (child);
    }
}

void
upmf_archive_destroy (upmf_archive_t this)
{
  if (this == NULL) return;

  xmlFree (this->name);
  if (this->prepare_hook != NULL) gl_list_free (this->prepare_hook);
  if (this->configure_hook != NULL) gl_list_free (this->configure_hook);
  if (this->commands != NULL) gl_list_free (this->commands);
}

UPMF_DEFINE_LIST_FUN (archive, ARCHIVE, "build", "archive")
UPMF_DEFINE_CMP_FUN (archive, ARCHIVE, name)
