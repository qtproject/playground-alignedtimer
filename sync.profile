%modules = ( # path to module name map
    "QtAlignedTimer" => "$basedir/src/alignedtimer",
);
%moduleheaders = ( # restrict the module headers to those found in relative path
);
%classnames = (
    "qtalignedtimerversion.h" => "QtAlignedTimerVersion",
);
%mastercontent = (
    "alignedtimer" => "#include <QtAlignedTimer/QtAlignedTimer>\n",
);
%modulepris = (
    "QtAlignedTimer" => "$basedir/modules/qt_alignedtimer.pri",
);
# Module dependencies.
# Every module that is required to build this module should have one entry.
# Each of the module version specifiers can take one of the following values:
#   - A specific Git revision.
#   - any git symbolic ref resolvable from the module's repository (e.g. "refs/heads/master" to track master branch)
#
%dependencies = (
    "qtbase" => "refs/heads/master",
);

