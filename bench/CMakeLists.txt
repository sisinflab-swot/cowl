# Data

file(GLOB COWL_TEST_DATA CONFIGURE_DEPENDS "${COWL_DATA_DIR}/*.owl")
file(COPY ${COWL_TEST_DATA} DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")

# Sources

set(COWL_BENCH_SRC_DIR "${COWL_BENCH_DIR}/src")
file(GLOB COWL_BENCH_SOURCES CONFIGURE_DEPENDS "${COWL_BENCH_SRC_DIR}/*.c")

# Targets

add_executable(cowl-bench)
target_sources(cowl-bench PRIVATE ${COWL_BENCH_SOURCES})
target_compile_features(cowl-bench PRIVATE ${COWL_COMPILE_FEATURES})
target_compile_options(cowl-bench PRIVATE ${COWL_WARNING_OPTIONS})
target_link_libraries(cowl-bench PRIVATE cowl)

if(COWL_LTO_ENABLED)
    set_property(TARGET cowl-bench PROPERTY INTERPROCEDURAL_OPTIMIZATION ON)
endif()

if(COWL_CLANG_TIDY)
    clang_tidy_check(cowl-bench)
endif()

if(COWL_TESTS)
    add_test(NAME "Benchmark" COMMAND cowl-bench)
endif()
