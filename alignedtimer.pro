   TEMPLATE = subdirs
   CONFIG += ordered


   module_alignedtimer_src.subdir = src
   module_alignedtimer_src.target = module-alignedtimer-src

   module_alignedtimer_tests.subdir = tests
   module_alignedtimer_tests.target = module-alignedtimer-tests
   module_alignedtimer_tests.depends = module_alignedtimer_src
   module_alignedtimer_tests.CONFIG = no_default_install
   !contains(QT_BUILD_PARTS,tests) {
       module_alignedtimer_tests.CONFIG += no_default_target
   }

   SUBDIRS += module_alignedtimer_src \
              module_alignedtimer_tests \
