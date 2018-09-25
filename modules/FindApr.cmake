# Apache Portable Runtime

find_path(APR_INCLUDE_DIR
        NAMES apr_pools.h
        PATHS ${APR_ROOT_DIR}/include/apr-1)

find_library(APR_LIBRARY
        NAMES libapr-1.a apr.exp libapr-1.0.dylib libapr-1.a libapr-1.dylib
        PATHS ${APR_ROOT_DIR}/lib SHARED IMPORTED GLOBAL)

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set LOGGING_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(APR DEFAULT_MSG APR_INCLUDE_DIR APR_LIBRARY)

if (APR_FOUND)
    set(APR_LIBRARIES ${APR_LIBRARY} )
    set(APR_INCLUDE_DIRS ${APR_INCLUDE_DIR} )
    set(APR_DEFINITIONS )
else ()
    MESSAGE(STATUS "APR NOT FOUND")
endif ()

mark_as_advanced(APR_ROOT_DIR APR_INCLUDE_DIR APR_LIBRARY)
