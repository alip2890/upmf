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

#ifndef UPMF_CONFIG_H
#define UPMF_CONFIG_H

#include <config.h>
#include <libxml/xmlIO.h>
#include <stdio.h>
#include <string.h>

#include "common.h"
#include "gl_linked_list.h"
#include "gl_list.h"
#include "types.h"
#include "use.h"

struct UpmfConfig
{
  xcstring_t enabled;
  xstring_t packagedir;
  xstring_t cflags;
  xstring_t cxxflags;
  xstring_t chost;
  xstring_t makeopts;
  xstring_t upmfopts;
  xstring_t stow;
  gl_list_t pkgfiledirs;
  gl_list_t features;
  gl_list_t uses;
};

/* Command line arguments, for argp */
struct arguments
{
  char *args[1];
  int quiet, update, upgrade;
  char *package_name;
};

extern upmf_config_t upmf_config;
extern struct arguments arguments;

int
upmf_config_init ();

void
upmf_config_destroy (void);

#endif /* !UPMF_CONFIG_H */
