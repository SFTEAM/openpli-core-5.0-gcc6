require conf/license/openpli-gplv2.inc
PACKAGE_ARCH = "${MACHINE_ARCH}"

inherit gitpkgv

SRCREV = "autorev"
PV = "1.0"
PR = "1"

SRC_URI = "file://ceryon-shutdown.sh "
FILES_${PN} = "/etc/init.d/ceryon-shutdown.sh"

S = "${WORKDIR}/git"

inherit autotools

do_install_append() {
    install -d ${D}/etc/init.d/
    install -m 0755 ${S}{WORKDIR}/ceryon-shutdown.sh ${D}/etc/init.d/ceryon-shutdown
}

INITSCRIPT_NAME = "ceryon-shutdown"
INITSCRIPT_PARAMS = "start 31 0 ."

inherit update-rc.d
