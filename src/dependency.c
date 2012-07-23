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
#include "dependency.h"

upmf_dep_t
upmf_dep_new (xmlDocPtr doc, xmlNodePtr node, upmf_package_t parent)
{
  if (xmlStrcmp (node->name, XSTRING ("dep"))) return NULL;
  
  upmf_dep_t tempdep = UPMF_DEP (malloc (sizeof (struct UpmfDep)));
  tempdep->name = xmlGetProp (node, XSTRING ("name"));
  tempdep->version = xmlGetProp (node, XSTRING ("version"));
  tempdep->use = xmlGetProp (node, XSTRING ("use"));

  return tempdep;
}

void
upmf_dep_destroy (upmf_dep_t this)
{
  if (this == NULL) return;
  
  xmlFree (this->name);
  xmlFree (this->version);
  xmlFree (this->use);
  free (this);
}

UPMF_DEFINE_LIST_FUN (dep, "dep")
UPMF_DEFINE_CMP_FUN (dep, DEP, name)

