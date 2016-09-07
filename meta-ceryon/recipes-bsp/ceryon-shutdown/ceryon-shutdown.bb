SUMMARY = "Ceryon Shutdown Files"
SECTION = "base"
PRIORITY = "required"
LICENSE = "proprietary"
MAINTAINER = "ceryon"
PACKAGE_ARCH = "${MACHINE_ARCH}"

require conf/license/openpli-gplv2.inc

PV = "1.0"
PR = "1"

S = "${WORKDIR}"

SRC_URI = "file://ceryon-shutdown.sh"

ALLOW_EMPTY_${PN} = "1"

do_install() {
    install -d ${D}/etc/init.d/
    install -m 0755 ${S}/ceryon-shutdown.sh ${D}/etc/init.d/ceryon-shutdown
}

INITSCRIPT_NAME = "ceryon-shutdown"
INITSCRIPT_PARAMS = "start 31 0 ."

inherit update-rc.d
