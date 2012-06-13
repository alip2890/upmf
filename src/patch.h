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

#ifndef PATCH_H
#define PATCH_H

#include <config.h>

#include "gl_list.h"
#include "gl_linked_list.h"
#include "types.h"

struct UpmfPatch
{
  xcstring_t name;
  xcstring_t filen;
  xcstring_t recom;
  gl_list_t uselist;
};

#endif /* !PATCH_H */
