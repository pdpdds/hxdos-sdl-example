# Makefile.am for the SDL truetype font loading library and viewer

lib_LTLIBRARIES = libSDL_ttf.la

libSDL_ttfincludedir = $(includedir)/SDL
libSDL_ttfinclude_HEADERS =	\
	SDL_ttf.h

libSDL_ttf_la_SOURCES =		\
	SDL_ttf.c

EXTRA_DIST =			\
	CHANGES			\
	autogen.sh

libSDL_ttf_la_LDFLAGS = 		\
        -release $(LT_RELEASE)	\
	-version-info $(LT_CURRENT):$(LT_REVISION):$(LT_AGE)
libSDL_ttf_la_LIBADD = 

bin_PROGRAMS = showfont

showfont_LDADD = libSDL_ttf.la

# Rule to build tar-gzipped distribution package
$(PACKAGE)-$(VERSION).tar.gz: dist

# Rule to build RPM distribution package
rpm: $(PACKAGE)-$(VERSION).tar.gz
	cp $(PACKAGE)-$(VERSION).tar.gz /usr/src/redhat/SOURCES
	rpm -ba $(PACKAGE).spec

