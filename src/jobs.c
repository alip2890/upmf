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

#include "jobs.h"

void
upmf_install_package (ucstring_t pname)
{
  gl_list_t deplist = UPMF_PACKAGE_LIST_NEW;
  upmf_package_deplist_new (pname, deplist);

  for (int pos = 0; pos < gl_list_size (deplist); pos++)
    {
      upmf_package_t p = UPMF_PACKAGE (gl_list_get_at (deplist, pos));
      printf (_("New: %s/%s\n"), p->section, p->name);
    }

  gl_list_free (deplist);
      
  printf (_("Installing %s\n"), pname);
}

void
upmf_update_files ()
{
  printf ("Updating package files...\n");
}

void
upmf_upgrade_system (bool withdeps)
{
  if (withdeps)
    printf ("Upgrading installed dependencies...\n");

  printf ("Upgrading installed packages...\n");
}
