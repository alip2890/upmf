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
#include <libxml/xmlIO.h>

#include "error.h"
#include "gettext.h"
#include "types.h"

xstring_t
upmf_get_xstring (xmlDocPtr doc, xmlNodePtr node);

xmlDocPtr
upmf_document_init (ustring_t filename, ustring_t tag);

#endif /* !COMMON_H */
