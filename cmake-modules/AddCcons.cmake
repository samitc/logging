include(ExternalProject)
if (MSVC)
    set(RELEASE_LIB_DIR ReleaseLibs)
    set(DEBUG_LIB_DIR DebugLibs)
elseif (XCODE_VERSION)
    set(RELEASE_LIB_DIR Release)
    set(DEBUG_LIB_DIR Debug)
else ()
    set(RELEASE_LIB_DIR "")
    set(DEBUG_LIB_DIR "")
endif ()

set(CCONS_CMAKE_ARGS
        "-DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}"
		"-DBUILD_TESTS=OFF")
set(CCONS_RELEASE_LIB_DIR "")
set(CCONS_DEBUGLIB_DIR "")
if (MSVC)
    set(CCONS_CMAKE_ARGS ${CCONS_CMAKE_ARGS}
            "-DCMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG:PATH=${DEBUG_LIB_DIR}"
            "-DCMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE:PATH=${RELEASE_LIB_DIR}")
endif ()
set(CCONS_PREFIX "${CMAKE_CURRENT_BINARY_DIR}/ccons")
# try to find git - if found, setup ccons
find_package(Git)
if (NOT GIT_FOUND)
    set(AddCcons_FOUND false CACHE BOOL "Was ccons setup correctly?")
else (NOT GIT_FOUND)
    set(AddCcons_FOUND true CACHE BOOL "Was ccons setup correctly?")

    ExternalProject_Add(ccons
            GIT_REPOSITORY https://github.com/samitc/ccons.git
            TIMEOUT 10
            PREFIX "${CCONS_PREFIX}"
            CMAKE_ARGS "${CCONS_CMAKE_ARGS}"
            LOG_DOWNLOAD ON
            LOG_CONFIGURE ON
            LOG_BUILD ON
            # Disable install
            INSTALL_COMMAND ""
            )

    set(LIB_PREFIX "${CMAKE_STATIC_LIBRARY_PREFIX}")
    set(LIB_SUFFIX "${CMAKE_STATIC_LIBRARY_SUFFIX}")
    set(CCONS_DEBUG_LIBRARIES
            "${LIB_PREFIX}ccons${LIB_SUFFIX}"
            "${CMAKE_THREAD_LIBS_INIT}")
    SET(CCONS_RELEASE_LIBRARIES
            "${LIB_PREFIX}ccons${LIB_SUFFIX}"
            "${CMAKE_THREAD_LIBS_INIT}")

    ExternalProject_Get_Property(ccons source_dir)
    include_directories(PUBLIC ${source_dir}/Src)

    ExternalProject_Get_Property(ccons binary_dir)
	set(CCONS_DEBUG_DIRECTORY ${binary_dir}/${DEBUG_LIB_DIR})
	set(CCONS_RELEASE_DIRECTORY ${binary_dir}/${RELEASE_LIB_DIR})
endif (NOT GIT_FOUND)