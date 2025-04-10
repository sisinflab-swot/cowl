# Data

file(GLOB COWL_TOOLS_DATA CONFIGURE_DEPENDS "${COWL_DATA_DIR}/*.owl")
file(COPY ${COWL_TOOLS_DATA} DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")

# Sources

set(COWL_TOOLS_SRC_DIR "${COWL_TOOLS_DIR}/src")

# Targets

add_custom_target(cowl-tools COMMENT "Build the tools")

add_executable(cowl-stats)
target_sources(cowl-stats PRIVATE "${COWL_TOOLS_SRC_DIR}/stats.c")
target_compile_features(cowl-stats PRIVATE ${COWL_COMPILE_FEATURES})
target_compile_options(cowl-stats PRIVATE ${COWL_WARNING_OPTIONS})
target_link_libraries(cowl-stats PRIVATE cowl)
add_dependencies(cowl-tools cowl-stats)

if(COWL_LTO_ENABLED)
    set_target_properties(cowl-stats PROPERTIES INTERPROCEDURAL_OPTIMIZATION ON)
endif()

if(COWL_CLANG_TIDY)
    clang_tidy_check(cowl-stats)
endif()

if(COWL_TESTS)
    add_test(NAME "Tool: stats" COMMAND cowl-stats test_onto.owl)
endif()
