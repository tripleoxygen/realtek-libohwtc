// SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (C) 2024 Fausto "O3" Ribeiro | ONT Lab <mailme@tripleoxygen.net>
 */

#ifndef _OMCI_FAL_H_
#define _OMCI_FAL_H_

#include <stdint.h>

#define API_OK 0x100
#define API_FAILED 0x101
#define API_NOT_REGISTERED 0x105

#define HWTC_SUPPORT_API_ID 0x14

uint32_t feature_api_is_registered(uint32_t id);
uint32_t feature_api_register(uint32_t id, void *api, void *func);
uint32_t feature_api_unregister(uint32_t id);

#endif
