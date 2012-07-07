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

#define UPMF_USE(s) (upmf_use_t) s
#define UPMF_PATCH(s) (upmf_patch_t) s
#define UPMF_DEP(s) (upmf_dep_t) s
#define UPMF_COMMAND(s) (upmf_command_t) s
#define UPMF_ARCHIVE(s) (upmf_archive_t) s
#define UPMF_BUILD(s) (upmf_build_t) s
#define UPMF_RELEASE(s) (upmf_release_t) s
#define UPMF_PACKAGE(s) (upmf_package_t) s
#define UPMF_CONFIG(s) (upmf_config_t) s

/* Typedefs for non-upmf types */

typedef xmlChar* xstring_t;
typedef const xmlChar* xcstring_t;
typedef void* upointer_t;
typedef const void* ucpointer_t;
typedef char* ustring_t;
typedef const char* ucstring_t;

/* Typedefs for upmf types */

typedef struct UpmfUse* upmf_use_t;
typedef struct UpmfPatch* upmf_patch_t;
typedef struct UpmfDep* upmf_dep_t;
typedef struct UpmfCommand* upmf_command_t;
typedef struct UpmfArchive* upmf_archive_t;
typedef struct UpmfBuild* upmf_build_t;
typedef struct UpmfRelease* upmf_release_t;
typedef struct UpmfPackage* upmf_package_t;
/* Caution: Here is the star missing: */
typedef struct UpmfConfig upmf_config_t;

/* Type declaration macro, s is the type name */
#define UPMF_DECLARE_TYPE(s)						\
  upmf_##s##_t upmf_##s##_new (xmlDocPtr doc, xmlNodePtr node,		\
			       upmf_package_t parent);			\
  void upmf_##s##_destroy (upmf_##s##_t this);				\
  void upmf_##s##_make_list (xmlDocPtr doc, xmlNodePtr node,	\
				  upmf_package_t parent, gl_list_t list); \
  bool upmf_##s##_cmp (ucpointer_t elt1, ucpointer_t elt2);

/* Defines the list creation function
   TYPENAME is the lowercase typename,
   CHILDTAG is the name of the tags to make a list from */
#define UPMF_DEFINE_LIST_FUN(typename, childtag)	\
  void upmf_##typename##_make_list (xmlDocPtr doc, xmlNodePtr node,	\
				    upmf_package_t par,	gl_list_t list)	\
  {									\
    xmlNodePtr childnode = node->xmlChildrenNode;			\
      while (childnode != NULL)						\
	{								\
	  if (!xmlStrcmp (childnode->name, XSTRING (childtag)))		\
	    {								\
	      upmf_##typename##_t tempobj = upmf_##typename##_new	\
		(doc, childnode, par);					\
		if (tempobj != NULL)					\
		  gl_list_nx_add_last (list, UCPOINTER (tempobj));	\
	    }								\
	  childnode = childnode->next;					\
	}								\
  }

#define UPMF_DEFINE_CMP_FUN(type, typeup, compmember)			\
  bool upmf_##type##_cmp (ucpointer_t elt1, ucpointer_t elt2)		\
  {									\
    upmf_##type##_t temp = UPMF_##typeup (elt2);			\
    return !strcmp (USTRING (elt1), USTRING (temp->compmember));	\
  }

#endif /* !TYPES_H */
