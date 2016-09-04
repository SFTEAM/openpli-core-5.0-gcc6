# We know about rtc
include conf/machine/include/build-extras.inc

PREFERRED_VERSION_linux-broadmedia = "4.1.24"
PREFERRED_VERSION_linux-libc-headers = "4.1"

BRAND_OEM = "broadmedia"

MACHINE_NAME = "\
${@bb.utils.contains('MACHINEBUILD', 'mbtwinplus', 'Premium Twin Plus' , '', d)}\
${@bb.utils.contains('MACHINEBUILD', 'sf3038', 'SF3038' , '', d)}\
${@bb.utils.contains('MACHINEBUILD', 'sf128', 'SF128' , '', d)}\
${@bb.utils.contains('MACHINEBUILD', 'sf138', 'SF138' , '', d)}\
"

MACHINE_BRAND = "\
${@bb.utils.contains('MACHINEBUILD', 'mbtwinplus', 'Miraclebox' , '', d)}\
${@bb.utils.contains('MACHINEBUILD', 'sf3038', 'Octagon' , '', d)}\
${@bb.utils.contains('MACHINEBUILD', 'sf128', 'Octagon' , '', d)}\
${@bb.utils.contains('MACHINEBUILD', 'sf138', 'Octagon' , '', d)}\
"

IMAGEDIR ?= "\
${@bb.utils.contains('MACHINEBUILD', 'mbtwinplus', 'miraclebox/twinplus' , '', d)}\
${@bb.utils.contains('MACHINEBUILD', 'sf3038', 'sf3038' , '', d)}\
${@bb.utils.contains('MACHINEBUILD', 'sf128', 'sf128' , '', d)}\
${@bb.utils.contains('MACHINEBUILD', 'sf138', 'sf138' , '', d)}\
"

MACHINE_DRIVER = "\
${@bb.utils.contains('MACHINEBUILD', 'mbtwinplus', 'twinplus' , '', d)}\
${@bb.utils.contains('MACHINEBUILD', 'sf3038', 'sf3038' , '', d)}\
${@bb.utils.contains('MACHINEBUILD', 'sf128', 'g100' , '', d)}\
${@bb.utils.contains('MACHINEBUILD', 'sf138', 'g100' , '', d)}\
"

MTD_KERNEL = "mtd1"
MTD_ROOTFS = "mtd2"
KERNEL_FILE = "kernel.bin"
ROOTFS_FILE = "rootfs.bin"

MACHINE_ESSENTIAL_EXTRA_RDEPENDS = "\
    broadmedia-dvb-modules-sf3038 \
    "

DVBPROVIDER = "kernel"
DVBSKYPROVIDER = "kernel"

MACHINE_ESSENTIAL_EXTRA_RRECOMMENDS = "\
    kernel-module-cdfs \
    "

MACHINE_EXTRA_RRECOMMENDS = " \
    ${@bb.utils.contains("GST_VERSION", "1.0", "gstreamer1.0-plugin-dvbmediasink", "", d)} \
    "

include conf/machine/include/autoload-filesystems.inc

DVBMEDIASINK_CONFIG = "--with-wma --with-wmv --with-pcm --with-dts --with-eac3 \
    ${@bb.utils.contains('MACHINE', 'g100', ' --with-h265' , '', d)} \
"

TARGET_ARCH = "mipsel"
DEFAULTTUNE = "mips32el"

PREFERRED_PROVIDER_virtual/kernel = "linux-broadmedia"

PREFERRED_PROVIDER_virtual/blindscan-dvbs = "broadmedia-blindscan-utils"
PREFERRED_PROVIDER_virtual/blindscan-dvbc = "broadmedia-blindscan-utils"

KERNEL_IMAGETYPE = "vmlinux"
KERNEL_OUTPUT = "${KERNEL_IMAGETYPE}"
KERNEL_CONSOLE = "ttyS0,115200n8"

IMAGE_FSTYPES ?= "ubi"

UBI_VOLNAME = "rootfs"
MKUBIFS_ARGS = "-m 2048 -e 126976 -c 8192"
UBINIZE_ARGS = "-m 2048 -p 128KiB"

IMAGE_CMD_ubi_prepend = " \
    rm -rf ${IMAGE_ROOTFS}/boot/*; \
    rm -rf ${IMAGE_ROOTFS}/tmp/*; \
    "

IMAGE_CMD_ubi_append = "\
    mkdir -p ${DEPLOY_DIR_IMAGE}/${IMAGEDIR}; \
    cp ${DEPLOY_DIR_IMAGE}/octagon/splash.bin ${DEPLOY_DIR_IMAGE}/${IMAGEDIR}/splash.bin; \
    mv ${DEPLOY_DIR_IMAGE}/${IMAGE_NAME}.rootfs.ubi ${DEPLOY_DIR_IMAGE}/${IMAGEDIR}/${ROOTFS_FILE}; \
    gzip -9c ${DEPLOY_DIR_IMAGE}/vmlinux-${MACHINE}.bin > ${DEPLOY_DIR_IMAGE}/${IMAGEDIR}/${KERNEL_FILE}; \
    echo ${DISTRO_NAME}-${DISTRO_VERSION}-${DATE} > ${DEPLOY_DIR_IMAGE}/${IMAGEDIR}/imageversion; \
    echo "rename this file to 'force' to force an update without confirmation" > ${DEPLOY_DIR_IMAGE}/${IMAGEDIR}/noforce; \
    cd ${DEPLOY_DIR_IMAGE}; \
    zip ${IMAGE_NAME}_usb.zip ${IMAGEDIR}/*; \
    rm -Rf ${IMAGEDIR}; \
    "

MACHINE_FEATURES += "alsa osdposition 3dtv switchoff hdmicec bootsplash omb dvb-c ci textlcd videoenhancement blindscan-dvbc skins1080 externalwifi kernelwifi wlan"

BOOTLOGO_FILENAME = "splash.bin"

require conf/machine/include/tune-mips32.inc

# add support for extra feeds
PACKAGE_ARCHS += " ${MACHINEBUILD}"
