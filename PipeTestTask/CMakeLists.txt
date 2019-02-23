
link_libraries(glfw)

include_directories(${glfw_INCLUDE_DIRS})

if (BUILD_SHARED_LIBS)
    link_libraries("${MATH_LIBRARY}")
endif()

if (MSVC)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

include_directories("${GLFW_SOURCE_DIR}/deps")

if (WIN32)
    set(ICON glfw.rc)
elseif (APPLE)
    set(ICON glfw.icns)
    set_source_files_properties(glfw.icns PROPERTIES
        MAXOSX_PACKAGE_LOCATION "Resources")
endif()

set(GLAD "${GLFW_SOURCE_DIR}/deps/glad/glad.h"
         "${GLFW_SOURCE_DIR}/deps/glad.c")
set(GETOPT "${GLFW_SOURCE_DIR}/deps/getopt.h"
           "${GLFW_SOURCE_DIR}/deps/getopt.c")
set(TINYCTHREAD "${GLFW_SOURCE_DIR}/deps/tinycthread.h"
                "${GLFW_SOURCE_DIR}/deps/tinycthread.c")

add_executable(pipe WIN32 MACOSX_BUNDLE pipe.c ${ICON} ${GLAD})

set(WINDOWS_BINARIES pipe)
set(CONSOLE_BINARIES pipe)

set_target_properties(${WINDOWS_BINARIES} ${CONSOLE_BINARIES} PROPERTIES FOLDER "Pipe")

if (MSVC)
    # Tell MSVC to use main instead of WinMain for Windows subsystem executables
    set_target_properties(${WINDOWS_BINARIES} ${CONSOLE_BINARIES} PROPERTIES
		LINK_FLAGS "/SUBSYSTEM:CONSOLE")
 #                         LINK_FLAGS "/ENTRY:mainCRTStartup")
endif()

if (APPLE)

    set_target_properties(pipe PROPERTIES MACOSX_BUNDLE_BUNDLE_NAME "Pipe")
    set_target_properties(${WINDOWS_BINARIES} PROPERTIES
                          RESOURCE glfw.icns
                          MACOSX_BUNDLE_SHORT_VERSION_STRING ${GLFW_VERSION}
                          MACOSX_BUNDLE_LONG_VERSION_STRING ${GLFW_VERSION_FULL}
                          MACOSX_BUNDLE_ICON_FILE glfw.icns
                          MACOSX_BUNDLE_INFO_PLIST "${GLFW_SOURCE_DIR}/CMake/MacOSXBundleInfo.plist.in")
endif()

