/*
 * Copyright (c) 2015, Intel Corporation
 * All rights reserved.
 *
 * Authors: Jeremy Compostella <jeremy.compostella@intel.com>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *    * Redistributions of source code must retain the above copyright
 *      notice, this list of conditions and the following disclaimer.
 *    * Redistributions in binary form must reproduce the above copyright
 *      notice, this list of conditions and the following disclaimer
 *      in the documentation and/or other materials provided with the
 *      distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include <lib.h>
#include <targets.h>
#include "log.h"

static struct target {
          debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
        enum boot_target bt;
        const CHAR16 *name;
        const CHAR16 *description;
} TARGETS[] = {
          debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
        { NORMAL_BOOT,    L"",           L"Android" },
          debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
        { NORMAL_BOOT,    L"boot",       L"Android" },
          debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
        { RECOVERY,       L"recovery",   L"Recovery OS" },
          debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
        { FASTBOOT,       L"bootloader", L"Fastboot mode" },
          debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
        { FASTBOOT,       L"fastboot",   L"Fastboot mode" },
          debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
        { DNX,            L"dnx",        L"Download and Execute mode" },
  debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
#ifdef CRASHMODE_USE_ADB
        { CRASHMODE,      L"crashmode",  L"Crashmode" },
  debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
#else
        { CRASHMODE,      NULL,          L"Crashmode" },
  debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
#endif
        /* Internal only */
        { CHARGER,        L"charging",   L"Charger mode" },
          debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
        { ESP_BOOTIMAGE,  NULL,          L"ESP bootimage" },
          debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
        { ESP_EFI_BINARY, NULL,          L"ESP efi binary" },
          debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
        { MEMORY,         NULL,          L"RAM bootimage" },
          debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
        { POWER_OFF,      NULL,          L"Power Off" },
          debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
        { EXIT_SHELL,     NULL,          L"Exit to shell" },
  debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
};

static struct target *find_entry(enum boot_target bt)
{
          debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
        UINTN i;

        for (i = 0; i < ARRAY_SIZE(TARGETS); i++)
                if (TARGETS[i].bt == bt)
                        return &TARGETS[i];

        return NULL;
}

const CHAR16 *boot_target_name(enum boot_target bt)
{
          debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
        struct target *target = find_entry(bt);
        return target ? target->name : NULL;
}

const CHAR16 *boot_target_description(enum boot_target bt)
{
          debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
        struct target *target = find_entry(bt);
        return target ? target->description : L"Unknown target";
}

enum boot_target name_to_boot_target(const CHAR16 *str)
{
          debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
        UINTN i;

        for (i = 0; i < ARRAY_SIZE(TARGETS); i++) {
                  debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
                if (!TARGETS[i].name)
                        continue;
                if (!StrCmp(str, TARGETS[i].name))
                        return TARGETS[i].bt;
        }

        return UNKNOWN_TARGET;
}

EFI_STATUS reboot_to_target(enum boot_target bt, EFI_RESET_TYPE type)
{
          debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
        const CHAR16 *name;

        if (bt == POWER_OFF) {
                  debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
                halt_system();
                return EFI_DEVICE_ERROR;
        }

        name = boot_target_name(bt);
        if (!name)
                return EFI_UNSUPPORTED;

        reboot((CHAR16 *)name, type);

        return EFI_DEVICE_ERROR;
};
