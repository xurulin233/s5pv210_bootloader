#!/bin/bash
export ENV_OK=y
export TOP_DIR=$PWD
export ECOS_PRODUCT_DIR=$TOP_DIR
export ECOS_KERNEL_DIR=$ECOS_PRODUCT_DIR/kernel/linux-3.0.8
export ECOS_UBOOT_DIR=$ECOS_PRODUCT_DIR/uboot/tiny210v2-uboot
export ARCH="arm"
export CROSS_COMPILE="$ECOS_PRODUCT_DIR/toolschain/4.5.1/bin/arm-none-linux-gnueabi-"
export ECOS_CROSS_COMPILE=$CROSS_COMPILE
export ECOS_IMAGE_DIR=$ECOS_PRODUCT_DIR/images
export ECOS_INSTALL_DIR=$ECOS_PRODUCT_DIR/rootfs.build
export ECOS_UTIL_DIR=$ECOS_PRODUCT_DIR/util
export ECOS_ROOTFS_DIR=$ECOS_PRODUCT_DIR/rootfs
export INSTALL_MOD_PATH=$ECOS_INSTALL_DIR
export ECOS_CROSS_PATH=$ECOS_PRODUCT_DIR/toolschain/4.5.1


export ECOS_OPENSSL_PATH=${ECOS_PRODUCT_DIR}/lib/openssl-1.0.2r
export ECOS_LIBNL_PATH=${ECOS_PRODUCT_DIR}/lib/libnl-3.4.0
export ECOS_COMMON_PATH=${ECOS_PRODUCT_DIR}/lib/common
export ECOS_INIPARSER_PATH=${ECOS_PRODUCT_DIR}/lib/iniparser-4.2.4
export ECOS_FREETYPE_PATH=${ECOS_PRODUCT_DIR}/lib/freetype-2.8.1




export TOOLCHAIN_BIN_DIR="$ECOS_PRODUCT_DIR/toolschain/4.5.1/bin"
