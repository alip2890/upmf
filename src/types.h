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

#ifndef TYPES_H
#define TYPES_H

#include <config.h>
#include <libxml/xmlIO.h>

#ifndef FALSE
#define FALSE 0
#define TRUE !FALSE
#endif /* !FALSE */

/* Cast macros for non-upmf types */

#define XSTRING(s) (xstring_t) s
#define XCSTRING(s) (xcstring_t) s
#define USTRING(s) (ustring_t) s
#define UCSTRING(s) (ucstring_t) s
#define UPOINTER(s) (upointer_t) s
#define UCPOINTER(s) (ucpointer_t) s

/* Cast macros for upmf types */

#define UPMF_USE(s) (upmf_use_t*) s
#define UPMF_PATCH(s) (upmf_patch_t*) s
#define UPMF_DEP(s) (upmf_dep_t*) s
#define UPMF_COMMAND(s) (upmf_command_t*) s
#define UPMF_ARCHIVE(s) (upmf_archive_t*) s
#define UPMF_BUILD(s) (upmf_build_t*) s
#define UPMF_RELEASE(s) (upmf_release_t*) s
#define UPMF_PACKAGE(s) (upmf_package_t*) s
#define UPMF_CONFIG(s) (upmf_config_t*) s

/* Typedefs for non-upmf types */

typedef xmlChar* xstring_t;
typedef const xmlChar* xcstring_t;
typedef void* upointer_t;
typedef const void* ucpointer_t;
typedef char* ustring_t;
typedef const char* ucstring_t;

/* Typedefs for upmf types */

typedef struct UpmfUse upmf_use_t;
typedef struct UpmfPatch upmf_patch_t;
typedef struct UpmfDep upmf_dep_t;
typedef struct UpmfCommand upmf_command_t;
typedef struct UpmfArchive upmf_archive_t;
typedef struct UpmfBuild upmf_build_t;
typedef struct UpmfRelease upmf_release_t;
typedef struct UpmfPackage upmf_package_t;
typedef struct UpmfConfig upmf_config_t;

#endif /* !TYPES_H */
