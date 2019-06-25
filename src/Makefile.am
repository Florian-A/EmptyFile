-include $(top_srcdir)/git.mk

bin_PROGRAMS = \
	empty-file
user_templates_SOURCES = \
	empty-file.c

AM_CPPFLAGS = \
	-DPROGRAMNAME_LOCALEDIR=\"${PROGRAMNAME_LOCALEDIR}\" \
	-DGETTEXT_PACKAGE=\"${GETTEXT_PACKAGE}\"

CFLAGS = -Wall -Wextra -std=c99 -g
CPPFLAGS = -I.
LDFLAGS =
