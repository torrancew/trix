set(TARGET i686-elf
    CACHE STRING "The target platform ID" FORCE)

set(CMAKE_SYSTEM_NAME TrixOS
    CACHE INTERNAL "")
set(CMAKE_SYSTEM_VERSION 0.0.1
    CACHE INTERNAL "")
set(CMAKE_SYSTEM_PROCESSOR i686
    CACHE INTERNAL "")

set(CMAKE_ASM_COMPILER /usr/bin/${TARGET}-as
    CACHE INTERNAL "")
set(CMAKE_C_COMPILER /usr/bin/clang
    CACHE INTERNAL "")
set(CMAKE_C_COMPILER_TARGET ${TARGET}
    CACHE INTERNAL "")

set(CMAKE_AR /usr/bin/${TARGET}-ar
    CACHE INTERNAL "")
set(CMAKE_LINKER /usr/bin/${TARGET}-ld
    CACHE INTERNAL "")
set(CMAKE_NM /usr/bin/${TARGET}-nm
    CACHE INTERNAL "")
set(CMAKE_OBJCOPY /usr/bin/${TARGET}-objcopy
    CACHE INTERNAL "")
set(CMAKE_OBJDUMP /usr/bin/${TARGET}-objdump
    CACHE INTERNAL "")
set(CMAKE_RANLIB /usr/bin/${TARGET}-ranlib
    CACHE INTERNAL "")
set(CMAKE_STRIP /usr/bin/${TARGET}-strip
    CACHE INTERNAL "")

set(CMAKE_C_LINK_EXECUTABLE "<CMAKE_LINKER> <CMAKE_C_LINK_FLAGS> <LINK_FLAGS> <OBJECTS> -o <TARGET> <LINK_LIBRARIES>"
    CACHE INTERNAL "")