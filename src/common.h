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

#ifndef COMMON_H
#define COMMON_H

#include <config.h>
#include <dirent.h>
#include <libxml/xmlIO.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "error.h"
#include "gettext.h"
#include "gl_linked_list.h"
#include "gl_list.h"
#include "types.h"
#include "upmf-config.h"

#define NEXT(s) s = s->next

xstring_t
upmf_get_xstring (xmlDocPtr doc, xmlNodePtr node);

xmlDocPtr
upmf_document_init (ucstring_t filename, ucstring_t tag);

gl_list_t
upmf_list_init_from_doc (xmlDocPtr doc, xmlNodePtr node, ustring_t children);

ustring_t
upmf_str_replace (ucstring_t s, ucstring_t old, ucstring_t new);

#endif /* !COMMON_H */
