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

#include <config.h>
#include <libxml/xmlIO.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>

#include "argp.h"
#include "error.h"
#include "gettext.h"
#include "package.h"
#include "version.h"
#include "types.h"
#include "upmf-config.h"

/* Argp stuff */

const char *argp_program_version = PACKAGE_STRING;
const char *argp_program_bug_address = PACKAGE_BUGREPORT;
static char doc[] = "Upmf -- package manager";
static char args_doc[] = "PACKAGE";

static struct argp_option options[] = {
  { "verbose", 'v', 0, 0, "Produce verbose output (default)" },
  { "quiet", 'q', 0, 0, "Produce less verbose output, including no build output" },
  { "install", 'i', "PACKAGE", 0, "Build and install PACKAGE" },
  { "update", 'u', 0, 0, "Update package files from remote server" },
  { "upgrade", 'g', 0, 0, "Upgrade packages on system" },
  { NULL }
};

static error_t
parse_opt (int key, char *arg, struct argp_state *state)
{
  struct arguments *arguments = state->input;

  switch (key)
    {
    case 'q':
      arguments->quiet = TRUE;
      break;
    case 'v':
      arguments->quiet = FALSE;
      break;
    case 'i':
      arguments->package_name = arg;
      break;
    case 'u':
      arguments->update = TRUE;
      break;
    case 'g':
      arguments->upgrade = TRUE;
      break;
    case ARGP_KEY_ARG:
      if (state->arg_num > 1)
	argp_usage (state);
      arguments->args[state->arg_num] = arg;
      break;
    default:
      return ARGP_ERR_UNKNOWN;
    }

  return 0;
}

static struct argp argp = { options, parse_opt, args_doc, doc };

/* Main program */

void
upmf_exit(void)
{
  upmf_config_destroy ();
}

int
main (int argc, char **argv)
{
  /*
  xmlDocPtr doc;
  xmlNodePtr node;
  UpmfPackage *p; */
  struct arguments arguments;

#ifdef ENABLE_NLS
  setlocale (LC_ALL, "");
  bindtextdomain (PACKAGE, LOCALEDIR);
  textdomain (PACKAGE);
#endif

  atexit (upmf_exit);

  if (!upmf_config_init ())
    {
      error (0, 0, _("Could not load configuration, aborting"));
      exit (1);
    }

  if (strcmp (upmf_config.enabled, "true"))
    {
      error (0, 0, _("Configuration file is not enabled\nPlease set the tag enabled to true"));
      exit (2);
    }

  arguments.quiet = FALSE;
  arguments.update = FALSE;
  arguments.upgrade = FALSE;
  arguments.package_name = "-";
  argp_parse (&argp, argc, argv, 0, 0, &arguments);


  if (arguments.update)
    {
      printf ("Updating files...\n");
    }

  if (arguments.upgrade)
    {
      printf ("Upgrading system...\n");
    }

  if (strcmp (arguments.package_name, "-"))
    {
      gl_list_t plist = UPMF_PACKAGE_LIST_NEW;
      upmf_package_tree_new (arguments.package_name, plist);

      for (int pos = 0; pos < gl_list_size (plist); pos++)
	{
	  upmf_package_t p = UPMF_PACKAGE (gl_list_get_at (plist, pos));
	  printf (_("Pending package: %s/%s\n"), p->section, p->name);
	}

      gl_list_free (plist);
      
      printf (_("Installing %s\n"), arguments.package_name);
    }

  exit (0);
}
