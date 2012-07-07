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
#include "patch.h"

upmf_patch_t
upmf_patch_new (xmlDocPtr doc, xmlNodePtr node, upmf_package_t par)
{
  upmf_patch_t temppatch = UPMF_PATCH (malloc (sizeof (struct UpmfPatch)));

  temppatch->name = xmlGetProp (node, XSTRING ("name"));
  temppatch->filen = xmlGetProp (node, XSTRING ("filen"));
  temppatch->recom = xmlGetProp (node, XSTRING ("recommended"));
  temppatch->uselist = UPMF_USE_LIST_NEW;
  
  /*  usebuffer = xmlGetProp (node, XSTRING ("use"));
  while ((use_token = strtok (usebuffer, " ")) != NULL)
    {
      gl_list_nx_add_last (uselist, UCPOINTER (strdup (use_token)));

      if (usebuffer != NULL) xmlFree (usebuffer);
      }*/

  return temppatch;
}

void
upmf_patch_destroy (upmf_patch_t this)
{
  xmlFree (this->name);
  xmlFree (this->filen);
  xmlFree (this->recom);
  gl_list_free (this->uselist);
  free (this);
}

UPMF_DEFINE_LIST_FUN (patch, "patch")
UPMF_DEFINE_CMP_FUN (patch, PATCH, name)

