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
#include "common.h"

xstring_t
upmf_get_xstring (xmlDocPtr doc, xmlNodePtr node)
{
  return xmlNodeListGetString (doc, node->xmlChildrenNode, 1);
}

xmlDocPtr
upmf_document_init (ucstring_t filename, ucstring_t tag)
{
  xmlDocPtr doc;
  xmlNodePtr node;

  doc = xmlParseFile (filename);
  if (doc == NULL)
    {
      error (0, 0, _("Document not parsed successfully"));
      return NULL;
    }

  node = xmlDocGetRootElement (doc);
  if (node == NULL)
    {
      error (0, 0, _("Document is empty"));
      xmlFreeDoc (doc);
      return NULL;
    }

  if (xmlStrcmp (node->name, XSTRING (tag)))
    {
      error (0, 0, _("Root element is wrong; is not '%s'"), tag);
      xmlFreeDoc (doc);
      return NULL;
    }

  return doc; 
}

gl_list_t
upmf_list_init_from_doc (xmlDocPtr doc, xmlNodePtr node, ustring_t children)
{
  gl_list_t list = gl_list_nx_create_empty (GL_LINKED_LIST, NULL, NULL,
					    UCPOINTER (xmlFree), FALSE);
  xmlNodePtr cnode = node->xmlChildrenNode;

  while (cnode != NULL)
    {
      if (!xmlStrcmp (cnode->name, children))
	{
	  gl_list_nx_add_last (list, UCPOINTER (upmf_get_xstring (doc, cnode)));
	}

      cnode = cnode->next;
    }

  xmlFree (cnode);
  return list;
}


ustring_t
upmf_str_replace(ucstring_t s, ucstring_t old, ucstring_t new)
{
  ustring_t ret;
  int i, count = 0;
  size_t newlen = strlen (new);
  size_t oldlen = strlen (old);

  for (i = 0; s[i] != '\0'; i++)
    {
      if (strncmp (&s[i], old, oldlen) == 0)
	{
	  count++;
	  i += oldlen - 1;
	}
    }

  ret = malloc (i + 1 + count * (newlen - oldlen));
  if (ret == NULL)
    return NULL;

  i = 0;
  while (*s)
    {
      if (strstr(s, old) == s)
	{
	  strcpy(&ret[i], new);
	  i += newlen;
	  s += oldlen;
	}
      else
	ret[i++] = *s++;
    }
  ret[i] = '\0';

  return ret;
}
