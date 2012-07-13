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

bin_PROGRAMS = upmf
upmf_SOURCES = \
	archive.c archive.h \
	build.c build.h \
	command.c command.h \
	common.h common.c \
	dependency.c dependency.h \
	gettext.h \
	jobs.c jobs.h \
	patch.c patch.h \
	package.c package.h \
	release.c release.h \
	types.h \
	upmf-config.c upmf-config.h \
	use.c use.h \
	version.h version.c \
	upmf.c
LDADD = $(LIBINTL) $(DEPS_LIBS) ${top_builddir}/lib/libgnu.a
AM_CPPFLAGS = -DSYSCONFDIR=\"$(sysconfdir)\" -DLOCALEDIR=\"$(localedir)\" $(DEPS_CFLAGS) -I${top_builddir}/lib -I${top_srcdir}/lib
