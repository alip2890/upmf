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
upmf_document_init (ustring_t filename, ustring_t tag)
{
  xmlDocPtr doc;
  xmlNodePtr node;

  doc = xmlParseFile ((char *)filename);
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
