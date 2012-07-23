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

#ifndef COMMAND_H
#define COMMAND_H

#include <config.h>
#include <stdlib.h>

#include "gl_list.h"
#include "gl_linked_list.h"
#include "package.h"
#include "types.h"
#include "use.h"

#define UPMF_COMMAND_LIST_NEW gl_list_nx_create_empty \
  (GL_LINKED_LIST, UCPOINTER (upmf_command_cmp), NULL, \
   UCPOINTER (upmf_command_destroy), FALSE)

struct UpmfCommand
{
  long int die;
  xstring_t cmd;
  xstring_t use;
};

UPMF_DECLARE_TYPE (command)

#endif /* !COMMAND_H */
