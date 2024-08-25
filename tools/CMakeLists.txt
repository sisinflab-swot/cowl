# Output setup

file(GLOB COWL_TOOLS_DATA CONFIGURE_DEPENDS "${COWL_DATA_DIR}/*.owl")
file(COPY ${COWL_TOOLS_DATA} DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")

# Targets

add_custom_target(cowl-tools COMMENT "Build the tools")

add_executable(cowl-stats EXCLUDE_FROM_ALL)
target_sources(cowl-stats PRIVATE "${COWL_TOOLS_DIR}/stats.c")
target_link_libraries(cowl-stats PRIVATE cowl)
add_dependencies(cowl-tools cowl-stats)

if(COWL_CLANG_TIDY)
    clang_tidy_check(cowl-stats)
endif()
