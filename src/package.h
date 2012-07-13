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

#ifndef PACKAGE_H
#define PACKAGE_H

#include <config.h>
#include <errno.h>
#include <sys/stat.h>

#include "common.h"
#include "gl_list.h"
#include "gl_linked_list.h"
#include "patch.h"
#include "release.h"
#include "types.h"
#include "upmf-config.h"
#include "use.h"

#define UPMF_PACKAGE_LIST_NEW gl_list_nx_create_empty \
  (GL_LINKED_LIST, UCPOINTER (upmf_package_cmp), NULL,	\
   UCPOINTER (upmf_package_destroy), FALSE)

struct UpmfPackage
{
  xstring_t name;
  xstring_t section;
  xstring_t dscr;
  xstring_t license;
  gl_list_t uselist;
  gl_list_t patchlist;
  gl_list_t releaselist;
};

/* upmf_package_t is too special, so no standard declaration
   UPMF_DECLARE_TYPE (package)*/

upmf_package_t
upmf_package_new (ucstring_t filen);

void
upmf_package_destroy (upmf_package_t this);

void
upmf_package_deplist_new (ucstring_t pkgname, gl_list_t plist);

ustring_t
upmf_package_find_file (ucstring_t pkgname);

bool
upmf_package_cmp (ucpointer_t p1, ucpointer_t p2);

#endif /* !PACKAGE_H */
