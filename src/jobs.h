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

#ifndef JOBS_H
#define JOBS_H

#include <config.h>

#include "gettext.h"
#include "gl_list.h"
#include "gl_linked_list.h"
#include "package.h"
#include "types.h"

void
upmf_install_package (ucstring_t pname);

void
upmf_update_files ();

void
upmf_upgrade_system (bool withdeps);

#endif /* !JOBS_H */
