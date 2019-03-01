###################################################################
# Setting Internal Feature Compiler Option
###################################################################

ifdef HW_INIT_ONLY
C_OPTION += -DHW_INIT_ONLY
export HW_INIT_ONLY
endif

###################################################################
# Setting Feature Compiler Option
###################################################################

ifdef CFG_BOOT_DEV
C_OPTION += -DCFG_BOOT_DEV="$(CFG_BOOT_DEV)"
export CFG_BOOT_DEV
endif

ifdef CFG_FPGA_PLATFORM
C_OPTION += -DCFG_FPGA_PLATFORM="$(CFG_FPGA_PLATFORM)"
export CFG_FPGA_PLATFORM
endif

ifdef CFG_EVB_PLATFORM
C_OPTION += -DCFG_EVB_PLATFORM="$(CFG_EVB_PLATFORM)"
export CFG_EVB_PLATFORM
endif

ifdef CFG_BATTERY_DETECT
C_OPTION += -DCFG_BATTERY_DETECT="$(CFG_BATTERY_DETECT)"
export CFG_BATTERY_DETECT
endif

ifdef CFG_HIGH_BATTERY_VOLTAGE_SUPPORT
C_OPTION += -DCFG_HIGH_BATTERY_VOLTAGE_SUPPORT="$(CFG_HIGH_BATTERY_VOLTAGE_SUPPORT)"
export CFG_HIGH_BATTERY_VOLTAGE_SUPPORT
endif

ifdef CFG_UART_TOOL_HANDSHAKE
C_OPTION += -DCFG_UART_TOOL_HANDSHAKE="$(CFG_UART_TOOL_HANDSHAKE)"
export CFG_UART_TOOL_HANDSHAKE
endif

ifdef CFG_USB_TOOL_HANDSHAKE
C_OPTION += -DCFG_USB_TOOL_HANDSHAKE="$(CFG_USB_TOOL_HANDSHAKE)"
export CFG_USB_TOOL_HANDSHAKE
endif

ifdef CFG_USB_DOWNLOAD
C_OPTION += -DCFG_USB_DOWNLOAD="$(CFG_USB_DOWNLOAD)"
export CFG_USB_DOWNLOAD
endif

ifdef CFG_UART_LOG
C_OPTION += -DCFG_UART_LOG="$(CFG_UART_LOG)"
export CFG_UART_LOG
endif

ifdef CFG_UART_META
C_OPTION += -DCFG_UART_META="$(CFG_UART_META)"
export CFG_UART_META
endif

ifdef CFG_LOG_BAUDRATE
C_OPTION += -DCFG_LOG_BAUDRATE="$(CFG_LOG_BAUDRATE)"
export CFG_LOG_BAUDRATE
endif

ifdef CFG_META_BAUDRATE
C_OPTION += -DCFG_META_BAUDRATE="$(CFG_META_BAUDRATE)"
export CFG_META_BAUDRATE
endif

ifdef CFG_EMERGENCY_DL_SUPPORT
C_OPTION += -DCFG_EMERGENCY_DL_SUPPORT="$(CFG_EMERGENCY_DL_SUPPORT)"
export CFG_EMERGENCY_DL_SUPPORT
endif

ifdef CFG_EMERGENCY_DL_TIMEOUT_MS
C_OPTION += -DCFG_EMERGENCY_DL_TIMEOUT_MS="$(CFG_EMERGENCY_DL_TIMEOUT_MS)"
export CFG_EMERGENCY_DL_TIMEOUT_MS
endif

ifdef CFG_MMC_ADDR_TRANS
C_OPTION += -DCFG_MMC_ADDR_TRANS="$(CFG_MMC_ADDR_TRANS)"
export CFG_MMC_ADDR_TRANS
endif

ifdef CFG_USB_UART_SWITCH
C_OPTION += -DCFG_USB_UART_SWITCH="$(CFG_USB_UART_SWITCH)"
export CFG_USB_UART_SWITCH
endif

ifdef CFG_OUTPUT_PL_LOG_TO_UART1
C_OPTION += -DCFG_OUTPUT_PL_LOG_TO_UART1="$(CFG_OUTPUT_PL_LOG_TO_UART1)"
export CFG_OUTPUT_PL_LOG_TO_UART1
endif

ifdef CFG_FUNCTION_TRACER_SUPPORT
C_OPTION += -DCFG_FUNCTION_TRACER_SUPPORT="$(CFG_FUNCTION_TRACER_SUPPORT)"
export CFG_FUNCTION_TRACER_SUPPORT
endif

ifdef CFG_HW_WATCHDOG
C_OPTION += -DCFG_HW_WATCHDOG="$(CFG_HW_WATCHDOG)"
export CFG_HW_WATCHDOG
endif

ifdef CFG_BOOT_ARGUMENT
C_OPTION += -DCFG_BOOT_ARGUMENT="$(CFG_BOOT_ARGUMENT)"
export CFG_BOOT_ARGUMEN
endif

ifdef CFG_BOOT_ARGUMENT_BY_ATAG
C_OPTION += -DCFG_BOOT_ARGUMENT_BY_ATAG="$(CFG_BOOT_ARGUMENT_BY_ATAG)"
export CFG_BOOT_ARGUMENT_BY_ATAG
endif

ifdef CFG_RAM_CONSOLE
C_OPTION += -DCFG_RAM_CONSOLE="$(CFG_RAM_CONSOLE)"
export CFG_RAM_CONSOLE
endif

ifdef CFG_MDJTAG_SWITCH
C_OPTION += -DCFG_MDJTAG_SWITCH="$(CFG_MDJTAG_SWITCH)"
export CFG_MDJTAG_SWITCH
endif

ifdef CFG_MDMETA_DETECT
C_OPTION += -DCFG_MDMETA_DETECT="$(CFG_MDMETA_DETECT)"
export CFG_MDMETA_DETECT
endif

ifdef CFG_APWDT_DISABLE
C_OPTION += -DCFG_APWDT_DISABLE="$(CFG_APWDT_DISABLE)"
export CFG_APWDT_DISABLE
endif

ifdef CFG_MDWDT_DISABLE
C_OPTION += -DCFG_MDWDT_DISABLE="$(CFG_MDWDT_DISABLE)"
export CFG_MDWDT_DISABLE
endif

ifdef CFG_SYS_STACK_SZ
C_OPTION += -DCFG_SYS_STACK_SZ="$(CFG_SYS_STACK_SZ)"
export CFG_SYS_STACK_SZ
endif

#load images
ifdef CFG_LOAD_UBOOT
C_OPTION += -DCFG_LOAD_UBOOT="$(CFG_LOAD_UBOOT)"
export CFG_LOAD_UBOOT
endif

ifdef CFG_LOAD_AP_ROM
C_OPTION += -DCFG_LOAD_AP_ROM="$(CFG_LOAD_AP_ROM)"
export CFG_LOAD_AP_ROM
endif

ifdef CFG_LOAD_MD_ROM
C_OPTION += -DCFG_LOAD_MD_ROM="$(CFG_LOAD_MD_ROM)"
export CFG_LOAD_MD_ROM
endif

ifdef CFG_LOAD_MD_RAMDISK
C_OPTION += -DCFG_LOAD_MD_RAMDISK="$(CFG_LOAD_MD_RAMDISK)"
export CFG_LOAD_MD_RAMDISK
endif

ifdef CFG_LOAD_CONN_SYS
C_OPTION += -DCFG_LOAD_CONN_SYS="$(CFG_LOAD_CONN_SYS)"
export CFG_LOAD_CONN_SYS
endif


ifdef CFG_UBOOT_MEMADDR
C_OPTION += -DCFG_UBOOT_MEMADDR="$(CFG_UBOOT_MEMADDR)"
export CFG_UBOOT_MEMADDR
endif

ifdef CFG_AP_ROM_MEMADDR
C_OPTION += -DCFG_AP_ROM_MEMADDR="$(CFG_AP_ROM_MEMADDR)"
export CFG_AP_ROM_MEMADDR
endif

ifdef CFG_MD1_ROM_MEMADDR
C_OPTION += -DCFG_MD1_ROM_MEMADDR="$(CFG_MD1_ROM_MEMADDR)"
export CFG_MD1_ROM_MEMADDR
endif

ifdef CFG_MD1_RAMDISK_MEMADDR
C_OPTION += -DCFG_MD1_RAMDISK_MEMADDR="$(CFG_MD1_RAMDISK_MEMADDR)"
export CFG_MD1_RAMDISK_MEMADDR
endif

ifdef CFG_MD2_ROM_MEMADDR
C_OPTION += -DCFG_MD2_ROM_MEMADDR="$(CFG_MD2_ROM_MEMADDR)"
export CFG_MD2_ROM_MEMADDR
endif

ifdef CFG_MD2_RAMDISK_MEMADDR
C_OPTION += -DCFG_MD2_RAMDISK_MEMADDR="$(CFG_MD2_RAMDISK_MEMADDR)"
export CFG_MD2_RAMDISK_MEMADDR
endif

ifdef CFG_LOAD_MD3_ROM
C_OPTION += -DCFG_LOAD_MD3_ROM="$(CFG_LOAD_MD3_ROM)"
export CFG_LOAD_MD3_ROM
endif

ifdef CFG_MD3_ROM_MEMADDR
C_OPTION += -DCFG_MD3_ROM_MEMADDR="$(CFG_MD3_ROM_MEMADDR)"
export CFG_MD3_ROM_MEMADDR
endif

ifdef CFG_CONN_SYS_MEMADDR
C_OPTION += -DCFG_CONN_SYS_MEMADDR="$(CFG_CONN_SYS_MEMADDR)"
export CFG_CONN_SYS_MEMADDR
endif

ifdef CFG_BOOTA64_MEMADDR
C_OPTION += -DCFG_BOOTA64_MEMADDR="$(CFG_BOOTA64_MEMADDR)"
export CFG_BOOTA64_MEMADDR
endif

ifdef CFG_DTB_MEMADDR
C_OPTION += -DCFG_DTB_MEMADDR="$(CFG_DTB_MEMADDR)"
export CFG_DTB_MEMADDR
endif

ifdef CFG_IMAGE_AARCH64_MEMADDR
C_OPTION += -DCFG_IMAGE_AARCH64_MEMADDR="$(CFG_IMAGE_AARCH64_MEMADDR)"
export CFG_IMAGE_AARCH64_MEMADDR
endif

ifdef CFG_WORLD_PHONE_SUPPORT
C_OPTION += -DCFG_WORLD_PHONE_SUPPORT="$(CFG_WORLD_PHONE_SUPPORT)"
export CFG_WORLD_PHONE_SUPPORT
endif

ifdef KPD_PMIC_LPRST_TD
C_OPTION += -DKPD_PMIC_LPRST_TD="$(KPD_PMIC_LPRST_TD)"
export KPD_PMIC_LPRST_TD
endif

ifdef ONEKEY_REBOOT_NORMAL_MODE_PL
C_OPTION += -DONEKEY_REBOOT_NORMAL_MODE_PL="$(ONEKEY_REBOOT_NORMAL_MODE_PL)"
export ONEKEY_REBOOT_NORMAL_MODE_PL
endif

ifdef KPD_USE_EXTEND_TYPE
C_OPTION += -DKPD_USE_EXTEND_TYPE="$(KPD_USE_EXTEND_TYPE)"
export KPD_USE_EXTEND_TYPE
endif

ifdef MTK_PMIC_RST_KEY
C_OPTION += -DMTK_PMIC_RST_KEY="$(MTK_PMIC_RST_KEY)"
export MTK_PMIC_RST_KEY
endif

ifdef CFG_FEATURE_ENCODE
C_OPTION += -DCFG_FEATURE_ENCODE="$(CFG_FEATURE_ENCODE)"
export CFG_FEATURE_ENCODE
endif

ifdef CFG_USB_AUTO_DETECT
C_OPTION += -DCFG_USB_AUTO_DETECT="$(CFG_USB_AUTO_DETECT)"
export CFG_USB_AUTO_DETECT
endif

ifdef CFG_USB_AUTO_DETECT_TIMEOUT_MS
C_OPTION += -DCFG_USB_AUTO_DETECT_TIMEOUT_MS="$(CFG_USB_AUTO_DETECT_TIMEOUT_MS)"
export CFG_USB_AUTO_DETECT_TIMEOUT_MS
endif

ifdef CFG_LOAD_SLT_MD_RAMDISK
C_OPTION += -DCFG_LOAD_SLT_MD_RAMDISK="$(CFG_LOAD_SLT_MD_RAMDISK)"
export CFG_LOAD_SLT_MD_RAMDISK
endif

ifdef CFG_LOAD_SLT_MD_DSP
C_OPTION += -DCFG_LOAD_SLT_MD_DSP="$(CFG_LOAD_SLT_MD_DSP)"
export CFG_LOAD_SLT_MD_DSP
endif

ifdef CFG_LOAD_SLT_MD
C_OPTION += -DCFG_LOAD_SLT_MD="$(CFG_LOAD_SLT_MD)"
export CFG_LOAD_SLT_MD
endif

ifdef CFG_LOAD_SLT_AARCH64_KERNEL
C_OPTION += -DCFG_LOAD_SLT_AARCH64_KERNEL="$(CFG_LOAD_SLT_AARCH64_KERNEL)"
export CFG_LOAD_SLT_AARCH64_KERNEL
endif

ifdef CFG_TDD_MD_ROM_MEMADDR
C_OPTION += -DCFG_TDD_MD_ROM_MEMADDR="$(CFG_TDD_MD_ROM_MEMADDR)"
export CFG_TDD_MD_ROM_MEMADDR
endif

ifdef CFG_FDD_MD_ROM_MEMADDR
C_OPTION += -DCFG_FDD_MD_ROM_MEMADDR="$(CFG_FDD_MD_ROM_MEMADDR)"
export CFG_FDD_MD_ROM_MEMADDR
endif

ifdef CFG_2G_MD_ROM_MEMADDR
C_OPTION += -DCFG_2G_MD_ROM_MEMADDR="$(CFG_2G_MD_ROM_MEMADDR)"
export CFG_2G_MD_ROM_MEMADDR
endif

ifdef CFG_TDD_ONLY_ROM_MEMADDR
C_OPTION += -DCFG_TDD_ONLY_ROM_MEMADDR="$(CFG_TDD_ONLY_ROM_MEMADDR)"
export CFG_TDD_ONLY_ROM_MEMADDR
endif

ifdef CFG_LOAD_SLT_MD32
C_OPTION += -DCFG_LOAD_SLT_MD32="$(CFG_LOAD_SLT_MD32)"
export CFG_LOAD_SLT_MD32
endif

ifdef CFG_MD32P_ROM_MEMADDR
C_OPTION += -DCFG_MD32P_ROM_MEMADDR="$(CFG_MD32P_ROM_MEMADDR)"
export CFG_MD32P_ROM_MEMADDR
endif

ifdef CFG_MD32D_ROM_MEMADDR
C_OPTION += -DCFG_MD32D_ROM_MEMADDR="$(CFG_MD32D_ROM_MEMADDR)"
export CFG_MD32D_ROM_MEMADDR
endif
ifdef CFG_LOAD_MD_DSP
C_OPTION += -DCFG_LOAD_MD_DSP="$(CFG_LOAD_MD_DSP)"
export CFG_LOAD_MD_DSP
endif

ifdef CFG_MD_DSP_MEMADDR
C_OPTION += -DCFG_MD_DSP_MEMADDR="$(CFG_MD_DSP_MEMADDR)"
export CFG_MD_DSP_MEMADDR
endif

ifdef CFG_USBIF_COMPLIANCE
C_OPTION += -DCFG_USBIF_COMPLIANCE="$(CFG_USBIF_COMPLIANCE)"
export CFG_USBIF_COMPLIANCE
endif

ifdef SLT_VMIN
C_OPTION += -DSLT_VMIN="$(SLT_VMIN)"
endif

ifdef SLT_VMAX
C_OPTION += -DSLT_VMAX="$(SLT_VMAX)"
endif

ifdef CUSTOM_CONFIG_MAX_DRAM_SIZE
C_OPTION += -DCUSTOM_CONFIG_MAX_DRAM_SIZE="$(CUSTOM_CONFIG_MAX_DRAM_SIZE)"
export CUSTOM_CONFIG_MAX_DRAM_SIZE
endif

ifdef FEATURE_DOWNLOAD_SCREEN
C_OPTION += -DFEATURE_DOWNLOAD_SCREEN="$(FEATURE_DOWNLOAD_SCREEN)"
export FEATURE_DOWNLOAD_SCREEN
endif

ifeq ("$(MTK_SECURITY_SW_SUPPORT)","yes")
	C_OPTION += -DMTK_SECURITY_SW_SUPPORT
endif

ifeq ("$(MTK_EMMC_SUPPORT)","yes")
    C_OPTION += -DMTK_EMMC_SUPPORT
endif

ifeq ("$(MTK_KERNEL_POWER_OFF_CHARGING)","yes")
C_OPTION += -DMTK_KERNEL_POWER_OFF_CHARGING
endif

ifeq ("$(MTK_MT6333_SUPPORT)","yes")
    C_OPTION += -DMTK_MT6333_SUPPORT
endif

ifeq ("$(MTK_MT8193_SUPPORT)","yes")
    C_OPTION += -DMTK_MT8193_SUPPORT
endif

ifeq ("$(MTK_FAN5405_SUPPORT)","yes")
    C_OPTION += -DMTK_FAN5405_SUPPORT
endif

ifeq ("$(CUSTOM_SEC_AUTH_SUPPORT)","yes")
    C_OPTION += -DCUSTOM_SEC_AUTH_SUPPORT
endif

ifeq ("$(MTK_EMMC_SUPPORT_OTP)","yes")
    C_OPTION += -DMTK_EMMC_SUPPORT_OTP
endif

ifeq ("$(MTK_COMBO_NAND_SUPPORT)","yes")
    C_OPTION += -DMTK_COMBO_NAND_SUPPORT
endif

ifeq ("$(MTK_DISABLE_POWER_ON_OFF_VOLTAGE_LIMITATION)","yes")
    C_OPTION += -DMTK_DISABLE_POWER_ON_OFF_VOLTAGE_LIMITATION
endif

ifeq ("$(MTK_BQ24160_SUPPORT)","yes")
    C_OPTION += -DMTK_BQ24160_SUPPORT
endif

ifeq ("$(MTK_SEC_VIDEO_PATH_SUPPORT)","yes")
    C_OPTION += -DMTK_SEC_VIDEO_PATH_SUPPORT
endif

ifdef CFG_ATF_SUPPORT
C_OPTION += -DCFG_ATF_SUPPORT="$(CFG_ATF_SUPPORT)"
export CFG_ATF_SUPPORT
endif

ifdef CFG_ATF_LOG_SUPPORT
C_OPTION += -DCFG_ATF_LOG_SUPPORT="$(CFG_ATF_LOG_SUPPORT)"
export CFG_ATF_LOG_SUPPORT
endif

ifdef CFG_TEE_SUPPORT
C_OPTION += -DCFG_TEE_SUPPORT="$(CFG_TEE_SUPPORT)"
export CFG_TEE_SUPPORT
endif

ifdef CFG_TRUSTONIC_TEE_SUPPORT
C_OPTION += -DCFG_TRUSTONIC_TEE_SUPPORT="$(CFG_TRUSTONIC_TEE_SUPPORT)"
export CFG_TRUSTONIC_TEE_SUPPORT
endif

ifdef CFG_TEE_SECURE_MEM_PROTECTED
C_OPTION += -DCFG_TEE_SECURE_MEM_PROTECTED="$(CFG_TEE_SECURE_MEM_PROTECTED)"
export CFG_TEE_SECURE_MEM_PROTECTED
endif

ifdef CFG_TEE_TRUSTED_APP_HEAP_SIZE
C_OPTION += -DCFG_TEE_TRUSTED_APP_HEAP_SIZE="$(CFG_TEE_TRUSTED_APP_HEAP_SIZE)"
export CFG_TEE_TRUSTED_APP_HEAP_SIZE
endif

ifdef CFG_ATF_ROM_MEMADDR
C_OPTION += -DCFG_ATF_ROM_MEMADDR="$(CFG_ATF_ROM_MEMADDR)"
export CFG_ATF_ROM_MEMADDR
endif

ifdef CFG_BOOTIMG_HEADER_MEMADDR
C_OPTION += -DCFG_BOOTIMG_HEADER_MEMADDR="$(CFG_BOOTIMG_HEADER_MEMADDR)"
export CFG_BOOTIMG_HEADER_MEMADDR
endif

ifdef CFG_NON_SECURE_SRAM_ADDR
C_OPTION += -DCFG_NON_SECURE_SRAM_ADDR="$(CFG_NON_SECURE_SRAM_ADDR)"
export CFG_NON_SECURE_SRAM_ADDR
endif

ifdef CFG_NON_SECURE_SRAM_SIZE
C_OPTION += -DCFG_NON_SECURE_SRAM_SIZE="$(CFG_NON_SECURE_SRAM_SIZE)"
export CFG_NON_SECURE_SRAM_SIZE
endif

ifdef LCM_WIDTH
C_OPTION += -DLCM_WIDTH="$(LCM_WIDTH)"
export LCM_WIDTH
endif

ifdef LCM_HEIGHT
C_OPTION += -DLCM_HEIGHT="$(LCM_HEIGHT)"
export LCM_HEIGHT
endif

ifdef CFG_BYPASS_EMI
C_OPTION += -DCFG_BYPASS_EMI="$(CFG_BYPASS_EMI)"
export CFG_BYPASS_EMI
endif

ifdef CFG_ENABLE_GPIO_CHK_POINT_WITH_UART_META
C_OPTION += -DCFG_ENABLE_GPIO_CHK_POINT_WITH_UART_META="$(CFG_ENABLE_GPIO_CHK_POINT_WITH_UART_META)"
export CFG_ENABLE_GPIO_CHK_POINT_WITH_UART_META
endif

ifdef MACH_TYPE
C_OPTION += -DMACH_TYPE_$(shell echo $(MACH_TYPE) | tr '[a-z]' '[A-Z]')
export MACH_TYPE
endif
