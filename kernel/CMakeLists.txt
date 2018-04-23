add_compile_options(
  $<$<COMPILE_LANGUAGE:C>:-std=c11>
  $<$<COMPILE_LANGUAGE:C>:-Wall>
  $<$<COMPILE_LANGUAGE:C>:-Werror>
  $<$<COMPILE_LANGUAGE:C>:-fpic>
  $<$<COMPILE_LANGUAGE:C>:-ffreestanding>
  $<$<COMPILE_LANGUAGE:C>:-fno-builtin>
  $<$<COMPILE_LANGUAGE:C>:-nostdlibinc>
)

include_directories("include")

include("cmake/${TARGET}.cmake")

# Assembly Boot Shim
add_library(boot OBJECT "arch/${ARCH}/boot.s")

# General Kernel Library
add_library(libk OBJECT panic.c string.c)

# Generate Kernel ELF
add_executable(
  kernel
  main.c
  $<TARGET_OBJECTS:boot>
  $<TARGET_OBJECTS:libk>
  $<TARGET_OBJECTS:platform>
)

# Customize ELF Linkage
set_target_properties(
  kernel
  PROPERTIES LINK_FLAGS
  "-T${CMAKE_CURRENT_SOURCE_DIR}/linker/${TARGET}.ld -z max-page-size=0x1000"
)

# Generate Flat Binary
add_custom_command(
  TARGET kernel POST_BUILD
  COMMAND ${CMAKE_OBJCOPY} -Obinary $<TARGET_FILE:kernel> $<TARGET_FILE_DIR:kernel>/kernel.bin
  COMMENT "Generating raw kernel binary"
  VERBATIM
)
