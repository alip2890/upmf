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

#ifndef USE_H
#define USE_H

#include <config.h>

#include "common.h"
#include "gl_list.h"
#include "gl_linked_list.h"
#include "types.h"

#define UPMF_USE_LIST_NEW gl_list_nx_create_empty \
  (GL_LINKED_LIST, UCPOINTER (upmf_use_cmp), NULL, \
   UCPOINTER (upmf_use_destroy), FALSE)

struct UpmfUse
{
  xstring_t name;
  xstring_t dscr;
  int isset;
};

UPMF_DECLARE_TYPE (use)

/* Checks whether a use flag is set */
bool
upmf_use_isset (ustring_t name);

#endif /* !USE_H */
