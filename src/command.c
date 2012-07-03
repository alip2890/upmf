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
#include "command.h"

upmf_command_t
upmf_command_new (xmlDocPtr doc, xmlNodePtr node, upmf_package_t par)
{
  if (xmlStrcmp (node->name, XSTRING ("cmd"))) return NULL;
  
  xstring_t use = xmlGetProp (node, XSTRING ("use"));
  if (use == NULL || (gl_list_search (par->uselist, UCPOINTER (use)) != NULL))
    {
      upmf_command_t cmd = UPMF_COMMAND (malloc (sizeof (struct UpmfCommand)));
      cmd->cmd = upmf_get_xstring (doc, node);
      cmd->die = strtol (xmlGetProp (node, XSTRING ("die")), NULL, 0);
      return cmd;
    }
  
  xmlFree (use);
  return NULL;
}

void
upmf_command_destroy (upmf_command_t this)
{
  if (this == NULL) return;

  xmlFree (this->cmd);
  free (this);
}

gl_list_t
upmf_command_make_list (xmlDocPtr doc, xmlNodePtr node,
				       upmf_package_t par)
{
  xmlNodePtr childnode = node->xmlChildrenNode;
  gl_list_t childlist = UPMF_COMMAND_LIST_NEW;
    while (childnode != NULL)
      {
	if (!xmlStrcmp (childnode->name, XSTRING ("cmd")))
	  {
	    upmf_command_t tempobj = upmf_command_new (doc, node, par);
	      if (tempobj != NULL)
		gl_list_nx_add_last (childlist, UCPOINTER (tempobj));
	  }
	childnode = childnode->next;
      }
    return childlist;
}

UPMF_DEFINE_CMP_FUN (command, COMMAND, cmd)
