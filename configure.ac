# copy-pasted from libreport
# ABRT_PARSE_WITH(PACKAGE)
# -----------------------
# For use in AC_ARG_WITH action-if-found, for packages default ON.
# * Set NO_PACKAGE=YesPlease for --without-PACKAGE
# * Unset NO_PACKAGE for --with-PACKAGE without ARG
AC_DEFUN([ABRT_PARSE_WITH],
    [m4_pushdef([ABRT_UC_PACKAGE], m4_toupper([$1]))dnl
    if test "$withval" = "no"; then
        NO_[]ABRT_UC_PACKAGE=YesPlease
    elif test "$withval" = "yes"; then
        NO_[]ABRT_UC_PACKAGE=
    else
        NO_[]ABRT_UC_PACKAGE=
    fi
    m4_popdef([ABRT_UC_PACKAGE])])

AC_INIT([abrt],
	m4_esyscmd([cat ./abrt-version]),
	[crash-catcher@fedorahosted.org])

AC_CONFIG_MACRO_DIR([m4])
AM_INIT_AUTOMAKE([-Wall foreign tar-ustar])
# Support silent build rules. Disable by either passing --disable-silent-rules
# to ./configure or passing V=1 to make
m4_ifdef([AM_SILENT_RULES], [AM_SILENT_RULES])
# The 'yes' argument is undocumented but it is common knowledge that it works.
AM_SILENT_RULES([yes])


AM_PROG_AR
AC_DISABLE_STATIC
AC_PROG_LIBTOOL
AC_PROG_CC
AM_PROG_CC_C_O
AC_PROG_LN_S

AC_SYS_LARGEFILE
CFLAGS="$CFLAGS -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE \
          -D_FILE_OFFSET_BITS=64 -fno-strict-aliasing -std=gnu99 -Wall -Wwrite-strings"

AC_ARG_ENABLE(debug,
              [AC_HELP_STRING([--enable-debug],
                             [Enable debug information])],
              [CFLAGS="$CFLAGS -DDEBUG -ggdb -g -O0"])

dnl ****** INTERNATIONALIZATION **********************
GETTEXT_PACKAGE=abrt
AC_SUBST(GETTEXT_PACKAGE)
AC_DEFINE_UNQUOTED(GETTEXT_PACKAGE, "$GETTEXT_PACKAGE", [Package name for gettext])

AM_GNU_GETTEXT([external])
AM_GNU_GETTEXT_VERSION([0.17])

IT_PROG_INTLTOOL([0.35.0])

dnl ****** END ****************************************

AM_PATH_PYTHON
if test -z "$PYTHON"; then
    echo "*** Essential program python not found" 1>&2
    exit 1
fi

AC_PATH_PROG([ASCIIDOC], [asciidoc], [no])
[if test "$ASCIIDOC" = "no"]
[then]
    [echo "The asciidoc program was not found in the search path. Please ensure"]
    [echo "that it is installed and its directory is included in the search path."]
    [echo "Then run configure again before attempting to build ABRT."]
    [exit 1]
[fi]

AC_PATH_PROG([XMLTO], [xmlto], [no])
[if test "$XMLTO" = "no"]
[then]
    [echo "The xmlto program was not found in the search path. Please ensure"]
    [echo "that it is installed and its directory is included in the search path."]
    [echo "Then run configure again before attempting to build ABRT."]
    [exit 1]
[fi]

AC_PATH_PROG([PYTHON_CONFIG], [python-config], [no])
[if test "$PYTHON_CONFIG" = "no"]
[then]
    [echo "The python-config program was not found in the search path. Please ensure"]
    [echo "that it is installed and its directory is included in the search path."]
    [echo "Then run configure again before attempting to build ABRT."]
    [exit 1]
[fi]

AC_ARG_WITH(python3,
AS_HELP_STRING([--with-python3],[build Python3 support (default is YES)]),
ABRT_PARSE_WITH([python3]))

[if test -z "$NO_PYTHON3"]
[then]
    AM_CONDITIONAL(BUILD_PYTHON3, true)
    AC_PATH_PROG([PYTHON3], [python3], [no])
    [if test "$PYTHON3" == "no"]
    [then]
        [echo "The python3 program was not found in the search path. Please ensure"]
        [echo "that it is installed and its directory is included in the search path or"]
        [echo "pass --without-python3 to ./configure."]
        [echo "Then run configure again before attempting to build ABRT."]
        [exit 1]
    [fi]

    AC_PATH_PROG([PYTHON3_CONFIG], [python3-config], [no])
    [if test "$PYTHON3_CONFIG" = "no"]
    [then]
        [echo "The python3-config program was not found in the search path. Please ensure"]
        [echo "that it is installed and its directory is included in the search path or"]
        [echo "pass --without-python3 to ./configure."]
        [echo "Then run configure again before attempting to build ABRT."]
        [exit 1]
    [fi]

    PYTHON3_CFLAGS=`python3-config --cflags 2> /dev/null`
    PYTHON3_LIBS=`python3-config --libs 2> /dev/null`

    AC_SUBST([PYTHON3_PREFIX], ['${prefix}'])
    AC_SUBST([PYTHON3_EXEC_PREFIX], ['${exec_prefix}'])

    PYTHON3_DIR=`$PYTHON3 -c "import distutils.sysconfig; \
        print(distutils.sysconfig.get_python_lib(0,0,prefix='$PYTHON3_PREFIX'))"`
    PYTHON3_EXECDIR=`$PYTHON3 -c "import distutils.sysconfig; \
        print(distutils.sysconfig.get_python_lib(1,0,prefix='$PYTHON3_EXEC_PREFIX'))"`

    AC_SUBST(PYTHON3_CFLAGS)
    AC_SUBST(PYTHON3_LIBS)
    AC_SUBST(python3dir, $PYTHON3_DIR)
    AC_SUBST(py3execdir, $PYTHON3_EXECDIR)
[else]
    AM_CONDITIONAL(BUILD_PYTHON3, false)
[fi]

AC_ARG_WITH(pythondoc,
AS_HELP_STRING([--with-pythondoc],[build Python documentation (default is YES)]),
ABRT_PARSE_WITH([pythondoc]))

[if test -z "$NO_PYTHONDOC"]
[then]
    AM_CONDITIONAL(HAVE_PYTHON_SPHINX, true)
    AC_PATH_PROG([PYTHON_SPHINX], [sphinx-build], [no])
    [if test "$PYTHON_SPHINX" = "no"]
    [then]
        [echo "The sphinx-build program was not found in the search path. Please ensure"]
        [echo "that it is installed and its directory is included in the search path or"]
        [echo "pass --without-pythondoc to ./configure."]
        [echo "Then run configure again before attempting to build ABRT."]
        [exit 1]
    [fi]
[else]
    AM_CONDITIONAL(HAVE_PYTHON_SPHINX, false)
[fi]

AC_ARG_WITH(pythontests,
AS_HELP_STRING([--with-pythontests],[run python tests (default is YES)]),
ABRT_PARSE_WITH([pythontests]))

[if test -z "$NO_PYTHONTESTS"]
[then]
    AM_CONDITIONAL(HAVE_PYTHON_NOSE, true)
    AC_PATH_PROG([PYTHON_NOSE], [nosetests], [no])
    [if test "$PYTHON_NOSE" = "no"]
    [then]
        [echo "The nosetests program was not found in the search path. Please ensure"]
        [echo "that it is installed and its directory is included in the search path or"]
        [echo "pass --without-pythontests to ./configure."]
        [echo "Then run configure again before attempting to build ABRT."]
        [exit 1]
    [fi]
[else]
    AM_CONDITIONAL(HAVE_PYTHON_NOSE, false)
[fi]

PYTHON_CFLAGS=`python-config --cflags 2> /dev/null`
PYTHON_LIBS=`python-config --libs 2> /dev/null`

AC_SUBST(PYTHON_CFLAGS)
AC_SUBST(PYTHON_LIBS)

PKG_CHECK_MODULES([GTK], [gtk+-3.0])
PKG_CHECK_MODULES([GLIB], [glib-2.0 >= 2.43])
PKG_CHECK_MODULES([DBUS], [dbus-1])
PKG_CHECK_MODULES([LIBXML], [libxml-2.0])
PKG_CHECK_MODULES([LIBNOTIFY], [libnotify >= 0.7.0])
PKG_CHECK_MODULES([NSS], [nss])
PKG_CHECK_MODULES([LIBREPORT], [libreport])
PKG_CHECK_MODULES([LIBREPORT_GTK], [libreport-gtk])
PKG_CHECK_MODULES([GIO], [gio-2.0])
PKG_CHECK_MODULES([GIO_UNIX], [gio-unix-2.0])
PKG_CHECK_MODULES([SATYR], [satyr])
PKG_CHECK_MODULES([SYSTEMD], [libsystemd])
PKG_CHECK_MODULES([GSETTINGS_DESKTOP_SCHEMAS], [gsettings-desktop-schemas >= 3.15.1])

PKG_PROG_PKG_CONFIG
AC_ARG_WITH([systemdsystemunitdir],
        AS_HELP_STRING([--with-systemdsystemunitdir=DIR], [Directory for systemd service files]),
        [], [with_systemdsystemunitdir=$($PKG_CONFIG --variable=systemdsystemunitdir systemd)])
AC_SUBST([systemdsystemunitdir], [$with_systemdsystemunitdir])
AM_CONDITIONAL(HAVE_SYSTEMD, [test -n "$with_systemdsystemunitdir"])

AC_ARG_WITH([dbusinterfacedir],
        AS_HELP_STRING([--with-dbusinterfacedir=DIR], [Directory for dbus interface files]),
        [], [with_dbusinterfacedir=${datadir}/dbus-1/interfaces])
AC_SUBST([dbusinterfacedir], [$with_dbusinterfacedir])

AC_ARG_WITH(largedatatmpdir,
            [AS_HELP_STRING([--with-largedatatmpdir=DIR],
                           [Directory where potentially large data are created (default: /var/tmp)])],
            [], [with_largedatatmpdir="/var/tmp"])
AC_SUBST([LARGE_DATA_TMP_DIR], [$with_largedatatmpdir])

AC_CHECK_HEADER([sys/inotify.h], [],
   [AC_MSG_ERROR([sys/inotify.h is needed to build abrt])])

AC_CHECK_HEADERS([locale.h])

CONF_DIR='${sysconfdir}/${PACKAGE_NAME}'
DEFAULT_CONF_DIR='${datadir}/${PACKAGE_NAME}/conf.d'
VAR_RUN='${localstatedir}/run'
VAR_STATE='${localstatedir}/lib/${PACKAGE_NAME}'
PLUGINS_CONF_DIR='${sysconfdir}/${PACKAGE_NAME}/plugins'
DEFAULT_PLUGINS_CONF_DIR='${datadir}/${PACKAGE_NAME}/conf.d/plugins'
EVENTS_DIR='${datadir}/libreport/events'
EVENTS_CONF_DIR='${sysconfdir}/libreport/events.d'
JOURNAL_CATALOG_DIR='$(prefix)/lib/systemd/catalog'
ENABLE_SOCKET_OR_DBUS='-DENABLE_DBUS=1'
DEFAULT_DUMP_LOCATION_MODE=0751
DEFAULT_DUMP_DIR_MODE=$($PKG_CONFIG --variable=dd_mode libreport)
LIBREPORT_PLUGINS_CONF_DIR=$($PKG_CONFIG --variable=plugins_conf_dir libreport)
PROBLEMS_CONFIG_INTERFACES_DIR=${dbusinterfacedir}

AC_ARG_WITH([defaultdumplocation],
            AS_HELP_STRING([--with-defaultdumplocation=DIR],
                           [Default dump location ('LOCALSTATEDIR/spool/abrt')]),
            [], [with_defaultdumplocation=${localstatedir}/spool/abrt])
AC_SUBST([DEFAULT_DUMP_LOCATION], [$with_defaultdumplocation])

AC_ARG_WITH([defaultpackagemanager],
            AS_HELP_STRING([--with-defaultpackagemanager=dnf],
                           [Default package manager. 'dnf' or 'yum' ('dnf')]),
            [], [with_defaultpackagemanager=dnf])
AC_SUBST([DEFAULT_PACKAGE_MANAGER], [$with_defaultpackagemanager])


AC_ARG_WITH(augeaslenslibdir,
                    [AS_HELP_STRING([--with-augeaslenslibdir=DIR],
                                                   [Directory for librepor lens (default: /usr/share/augeas/lenses)])],
                                [], [with_augeaslenslibdir="/usr/share/augeas/lenses"])
AC_ARG_WITH([support-url],
        AS_HELP_STRING([--with-support-url=URL],
                [Specify the support URL to show in catalog entries]),
        [SUPPORT_URL="$withval"],
        [SUPPORT_URL=https://bugzilla.redhat.com/])

AC_SUBST(SUPPORT_URL)

AC_SUBST([AUGEAS_LENS_LIB_DIR], [$with_augeaslenslibdir])

AC_PATH_PROG(AUGPARSE, augparse, no)
[if test "$ARGPARSE" = "no"]
[then]
    [echo "The argparse program was not found in the search path. Please ensure"]
    [echo "that it is installed and its directory is included in the search path."]
    [echo "Then run configure again before attempting to build ABRT."]
    [exit 1]
[fi]

AC_ARG_ENABLE(doxygen-docs,
    AS_HELP_STRING([--enable-doxygen-docs],
	[build DOXYGEN documentation (requires Doxygen)]),
    [enable_doxygen_docs=$enableval],
    [enable_doxygen_docs=no]
)

AC_PATH_PROG([FINDMNT], [findmnt], [/usr/bin/findmnt], [$PATH:/usr/sbin:/sbin])
AC_PATH_PROG([GDB], [gdb], [/usr/bin/gdb], [/usr/libexec$PATH_SEPARATOR$PATH])

# Doxygen Documentation

AC_PATH_PROG(DOXYGEN, doxygen, no)

AC_MSG_CHECKING([whether to build Doxygen documentation])

if test "$DOXYGEN" = "no" ; then
    have_doxygen=no
else
    have_doxygen=yes
fi

if test "$enable_doxygen_docs" = "yes" ; then
    if test "$have_doxygen" = "no"; then
        AC_MSG_ERROR([Building Doxygen docs explicitly required, but Doxygen not found])
    fi
    AC_MSG_RESULT(yes)
else
    AC_MSG_RESULT(no)
fi

AM_CONDITIONAL(DBUS_DOXYGEN_DOCS_ENABLED, test "$enable_doxygen_docs" = "yes")


# Autoreporting advertisement

AC_ARG_ENABLE(suggest-autoreporting,
    AS_HELP_STRING([--enable-suggest-autoreporting],
    [print messages encouraging users to enable autoreporting]),
    [enable_suggest_autoreporting=$enableval],
    [enable_suggest_autoreporting=no]
)

AM_CONDITIONAL(SUGGEST_AUTOREPORTING, test "$enable_suggest_autoreporting" = "yes")

# Authenticated autoreporting

AC_ARG_ENABLE(authenticated-autoreporting,
    AS_HELP_STRING([--enable-authenticated-autoreporting],
    [enable authenticated autoreporting]),
    [enable_authenticated_autoreporting=$enableval],
    [enable_authenticated_autoreporting=no]
)

AM_CONDITIONAL(AUTHENTICATED_AUTOREPORTING, test "$enable_authenticated_autoreporting" = "yes")

# Make satyr use GDB or elfutils/libunwind for unwinding?

AC_ARG_ENABLE([native-unwinder],
    AS_HELP_STRING([--enable-native-unwinder],
        [use native unwinder (libunwind or elfutils) instead of GDB (default is no)]),
    [], [enable_native_unwinder=no])

[if test "$enable_native_unwinder" = "yes"]
[then]
    AC_DEFINE([ENABLE_NATIVE_UNWINDER], [1], [Use elfutils/libunwind for unwinding instead of GDB.])
[fi]

AC_ARG_ENABLE([addon-vmcore],
    AS_HELP_STRING([--enable-addon-vmcore],
        [allow to disable vmcore addon (for architectures without kexec/kdump) (default is yes)]),
    [], [enable_addon_vmcore=yes])

[if test "$enable_addon_vmcore" = "yes"]
[then]
    AC_DEFINE([ENABLE_ADDON_VMCORE], [1], [Disable vmcore addon (for architectures without kexec/kdump).])
	AM_CONDITIONAL(BUILD_ADDON_VMCORE, true)
[else]
	AM_CONDITIONAL(BUILD_ADDON_VMCORE, false)
[fi]

# Perform stack unwind on live/dying process in the core handler?

AC_ARG_ENABLE([dump-time-unwind],
    AS_HELP_STRING([--enable-dump-time-unwind],
        [create core stack trace while the crashed process is still in memory (default is no)]),
    [], [enable_dump_time_unwind=no])

[if test "$enable_native_unwinder" = "yes" -a "$enable_dump_time_unwind" = "yes"]
[then]
    AC_DEFINE([ENABLE_DUMP_TIME_UNWIND], [1], [Create core stacktrace while the process is still in memory.])
[fi]

AC_SUBST(CONF_DIR)
AC_SUBST(DEFAULT_CONF_DIR)
AC_SUBST(VAR_RUN)
AC_SUBST(VAR_STATE)
AC_SUBST(PLUGINS_CONF_DIR)
AC_SUBST(DEFAULT_PLUGINS_CONF_DIR)
AC_SUBST(EVENTS_CONF_DIR)
AC_SUBST(JOURNAL_CATALOG_DIR)
AC_SUBST(EVENTS_DIR)
AC_SUBST(DEFAULT_DUMP_LOCATION)
AC_SUBST(DEFAULT_DUMP_LOCATION_MODE)
AC_SUBST(DEFAULT_DUMP_DIR_MODE)
AC_SUBST(LIBREPORT_PLUGINS_CONF_DIR)
AC_SUBST(PROBLEMS_CONFIG_INTERFACES_DIR)

AC_ARG_WITH(bodhi,
AS_HELP_STRING([--with-bodhi],[use Bodhi plugin (default is YES)]),
ABRT_PARSE_WITH([bodhi]))

PKG_CHECK_MODULES([JSON_C], [json], [
    JSON_C_PACKAGE=json
], [
    PKG_CHECK_MODULES([JSON_C], [json-c], [
        JSON_C_PACKAGE=json-c
    ])
])


if test -z "$NO_BODHI"
then
PKG_CHECK_MODULES([LIBREPORT_WEB], [libreport-web])
AM_CONDITIONAL(BUILD_BODHI, true)
else
AM_CONDITIONAL(BUILD_BODHI, false)
fi dnl end NO_BODHI

AC_ARG_WITH(atomic,
AS_HELP_STRING([--with-atomic],[add Atomic support (default is YES)]),
ABRT_PARSE_WITH([atomic]))

if test -z "$NO_ATOMIC"
then
AM_CONDITIONAL(BUILD_ATOMIC, true)
else
AM_CONDITIONAL(BUILD_ATOMIC, false)
fi dnl end NO_BODHI

AC_ARG_WITH(selinux,
AS_HELP_STRING([--with-selinux],[build selinux support (default is YES)]),
ABRT_PARSE_WITH([selinux]))

[if test -z "$NO_SELINUX"]
[then]
    PKG_CHECK_MODULES([LIBSELINUX], [libselinux])
    AM_CONDITIONAL(HAVE_SELINUX, true)
[else]
    AM_CONDITIONAL(HAVE_SELINUX, false)
[fi]

AC_ARG_WITH(rpm,
AS_HELP_STRING([--with-rpm],[build rpm support (default is YES)]),
ABRT_PARSE_WITH([rpm]))

[if test -z "$NO_RPM"]
[then]
    PKG_CHECK_MODULES([RPM], [rpm])
    AC_DEFINE(HAVE_LIBRPM, [], [Have rpm support.])
[fi]

AC_ARG_WITH(polkit,
AS_HELP_STRING([--with-polkit],[build polkit support (default is YES)]),
ABRT_PARSE_WITH([polkit]))

[if test -z "$NO_POLKIT"]
[then]
    PKG_CHECK_MODULES([POLKIT], [polkit-gobject-1])
    PKG_CHECK_MODULES([POLKIT_AGENT], [polkit-agent-1])
    AC_DEFINE(HAVE_POLKIT, [], [Have polkit support.])
[fi]

# Initialize the test suite.
AC_CONFIG_TESTDIR(tests)
AC_CONFIG_FILES([tests/Makefile tests/atlocal])
AM_MISSING_PROG([AUTOM4TE], [autom4te])
# Needed by tests/atlocal.in.
# CFLAGS may contain '-Werror=format-security'
AC_SUBST([O0CFLAGS], [`echo $CFLAGS   | sed 's/-O[[0-9]] *//' | sed 's/-Werror\(=[[^ ]]*\)\?//g'`])

AC_CONFIG_HEADERS([config.h])

AC_CHECK_PROGS([VALGRIND], [valgrind])

AC_CONFIG_FILES([
	Makefile
	abrt.pc
	abrt.spec
	apidoc/Makefile
	apidoc/Doxyfile
	apidoc/html/Makefile
	doc/Makefile
	doc/problems-service/Makefile
	doc/dbus-configuration/Makefile
	src/include/Makefile
	src/lib/Makefile
	src/plugins/Makefile
	src/Makefile
	src/daemon/Makefile
	src/daemon/abrt-handle-upload
	src/hooks/Makefile
	src/applet/Makefile
	src/cli/Makefile
	src/cli-ng/Makefile
	src/cli-ng/abrtcli/Makefile
	src/cli-ng/tests/Makefile
	src/cli-ng/tests/clitests/Makefile
	src/configuration-gui/Makefile
	src/configuration-gui/abrt_gui.pc
	src/dbus/Makefile
	src/plugins/abrt-action-install-debuginfo
	src/plugins/abrt-action-analyze-vmcore
	src/plugins/abrt-action-analyze-vulnerability
	src/plugins/abrt-action-check-oops-for-hw-error
	src/plugins/abrt-action-check-oops-for-alt-component
	src/python-problem/Makefile
	src/python-problem/doc/Makefile
	src/python-problem/tests/Makefile
	src/python-problem/problem/Makefile
	src/python-problem/examples/Makefile
	po/Makefile.in
	icons/Makefile
])

AC_OUTPUT
