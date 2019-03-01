# Copyright Statement:
#
# This software/firmware and related documentation ("MediaTek Software") are
# protected under relevant copyright laws. The information contained herein
# is confidential and proprietary to MediaTek Inc. and/or its licensors.
# Without the prior written permission of MediaTek inc. and/or its licensors,
# any reproduction, modification, use or disclosure of MediaTek Software,
# and information contained herein, in whole or in part, shall be strictly prohibited.

# MediaTek Inc. (C) 2010. All rights reserved.
#
# BY OPENING THIS FILE, RECEIVER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
# THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE")
# RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO RECEIVER ON
# AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES,
# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
# NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
# SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
# SUPPLIED WITH THE MEDIATEK SOFTWARE, AND RECEIVER AGREES TO LOOK ONLY TO SUCH
# THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. RECEIVER EXPRESSLY ACKNOWLEDGES
# THAT IT IS RECEIVER'S SOLE RESPONSIBILITY TO OBTAIN FROM ANY THIRD PARTY ALL PROPER LICENSES
# CONTAINED IN MEDIATEK SOFTWARE. MEDIATEK SHALL ALSO NOT BE RESPONSIBLE FOR ANY MEDIATEK
# SOFTWARE RELEASES MADE TO RECEIVER'S SPECIFICATION OR TO CONFORM TO A PARTICULAR
# STANDARD OR OPEN FORUM. RECEIVER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND
# CUMULATIVE LIABILITY WITH RESPECT TO THE MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE,
# AT MEDIATEK'S OPTION, TO REVISE OR REPLACE THE MEDIATEK SOFTWARE AT ISSUE,
# OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY RECEIVER TO
# MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
#
# The following software/firmware and/or related documentation ("MediaTek Software")
# have been modified by MediaTek Inc. All revisions are subject to any receiver's
# applicable license agreements with MediaTek Inc.

##############################################################
# Include MakeFile
##############################################################

include $(MTK_PATH_PLATFORM)/makefile.mak

##############################################################
# Initialize Variables
##############################################################

C_FILES         := $(filter %.c, $(MOD_SRC))
ASM_FILES       := $(filter %.s, $(MOD_SRC))
ASM_FILES_S       := $(filter %.S, $(MOD_SRC))
DA_VERIFY_FILES := $(filter %.c, $(DA_VERIFY_SRC))
PLAT_MOD_FILES := $(filter %.c, $(MOD_PLAT_SRC))
C_FILES_PLUS    := $(filter %.c, $(MOD_SRC_PLUS))

OBJS_FROM_C           := $(C_FILES:%.c=%.o)
OBJS_FROM_ASM         := $(ASM_FILES:%.s=%.o)
OBJS_FROM_ASM_S       := $(ASM_FILES_S:%.S=%.o)
DA_VERIFY_OBJS_FROM_C := $(DA_VERIFY_SRC:%.c=%.o)
PLAT_MOD_OBJS_FROM_C := $(MOD_PLAT_SRC:%.c=%.o)
OBJS_FROM_C_PLUS      := $(C_FILES_PLUS:%.c=%.o)

All_OBJS += OBJS_FROM_C
All_OBJS += OBJS_FROM_ASM
All_OBJS += DA_VERIFY_OBJS_FROM_C
All_OBJS += PLAT_MOD_OBJS_FROM_C

OBJS_FROM_C           := $(addprefix $(MOD_OBJ)/, $(C_FILES:%.c=%.o))
OBJS_FROM_ASM         := $(addprefix $(MOD_OBJ)/, $(ASM_FILES:%.s=%.o))
OBJS_FROM_ASM_S         := $(addprefix $(MOD_OBJ)/, $(ASM_FILES_S:%.S=%.o))
DA_VERIFY_OBJS_FROM_C := $(addprefix $(DA_VERIFY_OBJ)/, $(DA_VERIFY_FILES:%.c=%.o))
PLAT_MOD_OBJS_FROM_C := $(addprefix $(MOD_PLAT_OBJ)/, $(PLAT_MOD_FILES:%.c=%.o))

OBJS_FROM_C_PLUS           := $(addprefix $(MOD_OBJ)/, $(OBJS_FROM_C_PLUS))

##############################################################
# Specify Builld Command
##############################################################

define COMPILE_C
	$(CC) $(C_OPTION) -o $@ $<
endef

define COMPILE_ASM
	$(AS) $(AFLAGS) -o $@ $<
endef

##############################################################
# Main Flow
##############################################################

all: show $(OBJS_FROM_C) $(OBJS_FROM_ASM) $(OBJS_FROM_ASM_S) $(DA_VERIFY_OBJS_FROM_C) $(PLAT_MOD_OBJS_FROM_C) $(OBJS_FROM_C_PLUS)

-include $(PWD)/tools/emigen/emigen.mk
-include $(PWD)/tools/ptgen/$(MTK_PLATFORM)/ptgen.mk
-include $(PWD)/tools/drvgen/drvgen.mk

show:
	@echo .......... Complete .........

$(OBJS_FROM_C) : $(MOD_OBJ)/%.o : %.c
	$(COMPILE_C)

$(OBJS_FROM_ASM_S) : $(MOD_OBJ)/%.o : %.S
	$(COMPILE_C)

$(OBJS_FROM_ASM) : $(MOD_OBJ)/%.o : %.s
	$(COMPILE_ASM)

$(DA_VERIFY_OBJS_FROM_C) : $(DA_VERIFY_OBJ)/%.o : %.c
	$(COMPILE_C)

$(PLAT_MOD_OBJS_FROM_C) : $(MOD_PLAT_OBJ)/%.o : %.c
	$(COMPILE_C)

# add for custom_emi.c/cust_part.c
$(OBJS_FROM_C_PLUS) : $(MOD_OBJ)/%.o : $(PRELOADER_OUT)/%.c
	$(COMPILE_C)

