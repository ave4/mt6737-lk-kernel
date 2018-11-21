LOCAL_DIR := $(GET_LOCAL_DIR)

TARGET := vz6735_35g_a_m0

MODULES += app/mt_boot \
           dev/lcm


MTK_EMMC_SUPPORT = yes
MACH_FPGA_LED_SUPPORT = no
ifeq ($(MACH_FPGA_LED_SUPPORT),yes)
DEFINES += MACH_FPGA_LED_SUPPORT
endif
DEFINES += MTK_NEW_COMBO_EMMC_SUPPORT
MTK_KERNEL_POWER_OFF_CHARGING=yes
MTK_LCM_PHYSICAL_ROTATION = 0
CUSTOM_LK_LCM="hx8392a_dsi_cmd_qhd"
#hx8392a_dsi_cmd_qhd = yes

#FASTBOOT_USE_G_ORIGINAL_PROTOCOL = yes
MTK_SECURITY_SW_SUPPORT = yes
MTK_VERIFIED_BOOT_SUPPORT = yes
MTK_SEC_FASTBOOT_UNLOCK_SUPPORT = yes

DEBUG := 0
BOOT_LOGO=ct_lte_qhd

#DEFINES += WITH_DEBUG_DCC=1
DEFINES += WITH_DEBUG_UART=1
#DEFINES += WITH_DEBUG_FBCON=1
#DEFINES += MACH_FPGA=y
#DEFINES += SB_LK_BRINGUP=y
DEFINES += MTK_GPT_SCHEME_SUPPORT
