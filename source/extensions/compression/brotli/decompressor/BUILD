load(
    "//bazel:envoy_build_system.bzl",
    "envoy_cc_extension",
    "envoy_cc_library",
    "envoy_extension_package",
)

licenses(["notice"])  # Apache 2

envoy_extension_package()

envoy_cc_library(
    name = "decompressor_lib",
    srcs = ["brotli_decompressor_impl.cc"],
    hdrs = ["brotli_decompressor_impl.h"],
    deps = [
        "//envoy/compression/decompressor:decompressor_interface",
        "//envoy/stats:stats_interface",
        "//envoy/stats:stats_macros",
        "//source/common/buffer:buffer_lib",
        "//source/common/runtime:runtime_features_lib",
        "//source/extensions/compression/brotli/common:brotli_base_lib",
        "@org_brotli//:brotlidec",
    ],
)

envoy_cc_extension(
    name = "config",
    srcs = ["config.cc"],
    hdrs = ["config.h"],
    deps = [
        ":decompressor_lib",
        "//source/common/http:headers_lib",
        "//source/extensions/compression/common/decompressor:decompressor_factory_base_lib",
        "@envoy_api//envoy/extensions/compression/brotli/decompressor/v3:pkg_cc_proto",
    ],
)
