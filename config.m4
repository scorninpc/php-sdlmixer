dnl $Id$
dnl config.m4 for extension sdlmixer

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(sdlmixer, for sdlmixer support,
dnl Make sure that the comment is aligned:
dnl [  --with-sdlmixer             Include sdlmixer support])

dnl Otherwise use enable:

PHP_ARG_ENABLE(sdlmixer, whether to enable sdlmixer support,
dnl Make sure that the comment is aligned:
[  --enable-sdlmixer           Enable sdlmixer support])

if test "$PHP_SDLMIXER" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-sdlmixer -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/sdlmixer.h"  # you most likely want to change this
  dnl if test -r $PHP_SDLMIXER/$SEARCH_FOR; then # path given as parameter
  dnl   SDLMIXER_DIR=$PHP_SDLMIXER
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for sdlmixer files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       SDLMIXER_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$SDLMIXER_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the sdlmixer distribution])
  dnl fi

  dnl # --with-sdlmixer -> add include path
  dnl PHP_ADD_INCLUDE($SDLMIXER_DIR/include)

  dnl # --with-sdlmixer -> check for lib and symbol presence
  dnl LIBNAME=sdlmixer # you may want to change this
  dnl LIBSYMBOL=sdlmixer # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $SDLMIXER_DIR/lib, SDLMIXER_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_SDLMIXERLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong sdlmixer lib version or lib not found])
  dnl ],[
  dnl   -L$SDLMIXER_DIR/lib -lm
  dnl ])
  dnl
  dnl PHP_SUBST(SDLMIXER_SHARED_LIBADD)

  PHP_NEW_EXTENSION(sdlmixer, sdlmixer.c, $ext_shared)
fi
