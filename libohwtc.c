// SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (C) 2024 Fausto "O3" Ribeiro | ONT Lab <mailme@tripleoxygen.net>
 */

#include "omci_fal.h"
#include <stdint.h>
#include <stdio.h>

static const char copyright[] __attribute__((used)) =
	"2024 Fausto \"O3\" Ribeiro - ONT Lab | tripleoxygen.net";

static uint32_t hwtc_dummy_handler(void *api)
{
	return 0;
}

uint32_t feature_module_init(void *api)
{
	uint32_t ret;

	ret = feature_api_register(HWTC_SUPPORT_API_ID, api,
				   &hwtc_dummy_handler);
	if (ret != API_OK) {
		fprintf(stderr, "[libohwtc] Failed to register API: %u\n", ret);
		return API_FAILED;
	}
	return API_OK;
}

uint32_t feature_module_exit()
{
	feature_api_unregister(HWTC_SUPPORT_API_ID);

	return API_OK;
}