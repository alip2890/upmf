/* Copyright (C) 2012 Aljosha Papsch <papsch.al@googlemail.com>

   This file is part of upmf.

   upmf is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   upmf is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with upmf.  If not, see <http://www.gnu.org/licenses/>. */

#ifndef VERSION_H
#define VERSION_H

#include <config.h>

#include <stdlib.h>
#include <string.h>

#include "gl_list.h"
#include "gl_linked_list.h"
#include "types.h"

gl_list_t
upmf_version_make_list (ucstring_t string);

int
upmf_version_compare (ucstring_t v1, ucstring_t v2);

#endif /* !VERSION_H */
