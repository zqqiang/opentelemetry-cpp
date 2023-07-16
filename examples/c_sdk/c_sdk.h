// Copyright Zhaoqing Qiang
// SPDX-License-Identifier: Apache-2.0

#pragma once

#define LDGPLUSPLUS 1

#ifdef __cplusplus
extern "C" {
#endif

void InitOptions(char *url);
void InitTracer();
void CleanupTracer();

void OnHttpRequest(const char *uri);

#ifdef __cplusplus
}
#endif