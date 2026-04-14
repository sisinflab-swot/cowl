# Data

file(GLOB bench_data CONFIGURE_DEPENDS "${COWL_DATA_DIR}/*.owl")
file(COPY ${bench_data} DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")

# Sources

set(COWL_BENCH_SRC_DIR "${COWL_BENCH_DIR}/src")
file(GLOB COWL_BENCH_SOURCES CONFIGURE_DEPENDS "${COWL_BENCH_SRC_DIR}/*.c")

# Targets

add_executable(cowl-bench)
target_sources(cowl-bench PRIVATE ${COWL_BENCH_SOURCES})
set_target_properties(cowl-bench PROPERTIES INTERPROCEDURAL_OPTIMIZATION ${COWL_LTO_ENABLED})
target_compile_features(cowl-bench PRIVATE ${COWL_COMPILE_FEATURES})
target_compile_options(cowl-bench PRIVATE ${COWL_WARNING_OPTIONS})
target_link_libraries(cowl-bench PRIVATE cowl)

if(COWL_CLANG_TIDY)
    clang_tidy_check(cowl-bench)
endif()

if(COWL_TESTS)
    add_test(NAME "Benchmark" COMMAND cowl-bench)
endif()
