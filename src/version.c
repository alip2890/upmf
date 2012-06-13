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

#include <config.h>

#include "version.h"

/* Creates a list with the tokens of the version string. */
gl_list_t
upmf_version_make_list (ucstring_t string)
{
  ustring_t copy, token;
  copy = strdup (string);
  token = strtok (copy, ".-_");
  ucpointer_t toinsert = UCPOINTER (strdup (token));
  gl_list_t templist = gl_list_nx_create (GL_LINKED_LIST, NULL, NULL, NULL, 0,
					  1, &toinsert);

  while ((token = strtok (NULL, ".-_")) != NULL)
    {
      ucpointer_t voidtoken = UCPOINTER (strdup (token));
      gl_list_nx_add_last (templist, voidtoken);
    }

  free (token);
  free (copy);
  return templist;
}

int
upmf_version_compare (ucstring_t str1, ucstring_t str2)
{
  gl_list_t v1, v2;
  size_t listlength1, listlength2;
  /* Determines the relation of the two version strings:
     <0 : Version 2 is lower
     =0 : Both versions are equal
     >0 : Version 2 is greater */
  int status = 0;
  v1 = upmf_version_make_list (str1);
  v2 = upmf_version_make_list (str2);
  listlength1 = gl_list_size (v1);
  listlength2 = gl_list_size (v2);

  for (int pos = 0; pos < listlength2; pos++)
    {
      /* If version 2 is longer than version but rest is equal */
      if (pos > listlength1)
	{
	  status = -1;
	  break;
	}

      long int curnum = strtol (UCSTRING (gl_list_get_at (v2, pos)), NULL, 0);
      long int oldnum = strtol (UCSTRING (gl_list_get_at (v1, pos)), NULL, 0);

      if (curnum > oldnum)
	{
	  status = 1;
	  break;
	}

      if (curnum < oldnum)
	{
	  status = -1;
	  break;
	}

    }

  gl_list_free (v1);
  gl_list_free (v2);

  return status;
}
