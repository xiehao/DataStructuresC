# 查找头文件
find_path(CRITERION_INCLUDE_DIR
    NAMES criterion/criterion.h
    PATHS
        /opt/homebrew/include     # M1 Mac
        /usr/local/include        # Intel Mac
        /usr/include
)

# 查找库文件
find_library(CRITERION_LIBRARY
    NAMES criterion
    PATHS
        /opt/homebrew/lib        # M1 Mac
        /usr/local/lib           # Intel Mac
        /usr/lib
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Criterion
    REQUIRED_VARS
        CRITERION_LIBRARY
        CRITERION_INCLUDE_DIR
)

if(Criterion_FOUND AND NOT TARGET Criterion::Criterion)
    add_library(Criterion::Criterion UNKNOWN IMPORTED)
    set_target_properties(Criterion::Criterion PROPERTIES
        IMPORTED_LOCATION "${CRITERION_LIBRARY}"
        INTERFACE_INCLUDE_DIRECTORIES "${CRITERION_INCLUDE_DIR}"
    )
endif()

mark_as_advanced(CRITERION_INCLUDE_DIR CRITERION_LIBRARY)
