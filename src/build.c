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
#include "build.h"

upmf_build_t
upmf_build_new (xmlDocPtr doc, xmlNodePtr node, upmf_package_t parent)
{
  if (xmlStrcmp (node->name, XSTRING ("build"))) return NULL;
  
  upmf_build_t tempbuild = UPMF_BUILD (malloc (sizeof (struct UpmfBuild)));
  tempbuild->type = xmlGetProp (node, XSTRING ("type"));
  tempbuild->archivelist = UPMF_ARCHIVE_LIST_NEW;
  upmf_archive_make_list (doc, node, parent, tempbuild->archivelist);
  return tempbuild;
}

void
upmf_build_destroy (upmf_build_t this)
{
  if (this == NULL) return;

  xmlFree (this->type);
  gl_list_free (this->archivelist);
  free (this);
}

UPMF_DEFINE_LIST_FUN (build, "build")
/* I know, type is not suitable for comparing builds,
   but there is not other string available */
UPMF_DEFINE_CMP_FUN (build, BUILD, type)
