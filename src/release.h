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

#ifndef RELEASE_H
#define RELEASE_H

#include <config.h>

#include "gl_list.h"
#include "gl_linked_list.h"
#include "types.h"

struct UpmfRelease
{
  xcstring_t version;
  xcstring_t revision;
  xcstring_t branch;
  gl_list_t patchlist;
  gl_list_t deplist;
  upmf_build_t *build;
};

#endif /* !RELEASE_H */
