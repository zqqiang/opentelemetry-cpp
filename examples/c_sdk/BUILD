# Copyright Zhaoqing Qiang
# SPDX-License-Identifier: Apache-2.0

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "opentelemetry_c_sdk",
    srcs = [
        "c_sdk.cc",
    ],
    hdrs = [
        "c_sdk.h",
    ],
    defines = ["BAZEL_BUILD"],
    deps = [
        "//api",
        "//sdk:headers",
    ],
)
