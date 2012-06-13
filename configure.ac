#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

# Copyright (C) 2012 Aljosha Papsch <papsch.al@googlemail.com>
#
# This file is part of upmf.
#
# upmf is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or (at
# your option) any later version.
#
# upmf is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see `http://www.gnu.org/licenses/'.

AC_PREREQ([2.69])
AC_INIT([upmf], [0.1], [papsch.al@googlemail.com], [upmf], [http://localhost])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_AUX_DIR([config])
AC_CONFIG_HEADERS([config.h])
AC_USE_SYSTEM_EXTENSIONS

AM_INIT_AUTOMAKE
AM_SILENT_RULES([yes])
AM_MAINTAINER_MODE([enable])

AM_GNU_GETTEXT_VERSION([0.18.1])
AM_GNU_GETTEXT([external])

AC_PROG_CC_C99
AM_PROG_CC_C_O
gl_EARLY
gl_INIT

PKG_CHECK_MODULES([DEPS], [
			  libxml-2.0 >= 2.7.0
			  ])

AC_OUTPUT([Makefile lib/Makefile src/Makefile po/Makefile.in])
