dnl $Id$
dnl config.m4 for extension jsonnet

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

PHP_ARG_WITH(jsonnet, for jsonnet support,
dnl Make sure that the comment is aligned:
[  --with-jsonnet             Include jsonnet support])

dnl Otherwise use enable:

dnl PHP_ARG_ENABLE(jsonnet, whether to enable jsonnet support,
dnl Make sure that the comment is aligned:
dnl [  --enable-jsonnet           Enable jsonnet support])

AC_DEFUN([AC_JSONNET_EPOLL],
[
	AC_MSG_CHECKING([for epoll])

	AC_TRY_COMPILE(
	[
		#include <sys/epoll.h>
	], [
		int epollfd;
		struct epoll_event e;

		epollfd = epoll_create(1);
		if (epollfd < 0) {
			return 1;
		}

		e.events = EPOLLIN | EPOLLET;
		e.data.fd = 0;

		if (epoll_ctl(epollfd, EPOLL_CTL_ADD, 0, &e) == -1) {
			return 1;
		}

		e.events = 0;
		if (epoll_wait(epollfd, &e, 1, 1) < 0) {
			return 1;
		}
	], [
		AC_DEFINE([HAVE_EPOLL], 1, [do we have epoll?])
		AC_MSG_RESULT([yes])
	], [
		AC_MSG_RESULT([no])
	])
])

if test "$PHP_JSONNET" != "no"; then
  cd libjsonnet
  make libjsonnet.so
  cd ../

  # --with-jsonnet -> check with-path
  SEARCH_PATH="/usr/local/libjsonnet"
  SEARCH_FOR="libjsonnet.h"
  if test -r $PHP_JSONNET/$SEARCH_FOR; then # path given as parameter
    JSONNET_DIR=$PHP_JSONNET
  else # search default path list
    AC_MSG_CHECKING([for jsonnet files in default path])
    for i in $SEARCH_PATH ; do
      if test -r $i/$SEARCH_FOR; then
        JSONNET_DIR=$i
        AC_MSG_RESULT(found in $i)
      fi
    done
  fi

  if test -z "$JSONNET_DIR"; then
    AC_MSG_RESULT([not found])
    AC_MSG_ERROR([Please reinstall the jsonnet distribution])
  fi

  # --with-jsonnet -> add include path
  PHP_ADD_INCLUDE($JSONNET_DIR)

  # --with-jsonnet -> check for lib and symbol presence

    PHP_ADD_INCLUDE($JSONNET_DIR)
    PHP_EVAL_LIBLINE($JSONNET_DIR, JSONNET_SHARED_LIBADD)
    PHP_ADD_LIBRARY_WITH_PATH(jsonnet, $JSONNET_DIR, JSONNET_SHARED_LIBADD)

    AC_JSONNET_EPOLL()

    PHP_SUBST(JSONNET_SHARED_LIBADD)

    PHP_NEW_EXTENSION(jsonnet, jsonnet.c, $ext_shared)
fi
