INCLUDE(CMakeForceCompiler)

# CROSS COMPILER SETTING
SET(CMAKE_SYSTEM_NAME Generic)
CMAKE_MINIMUM_REQUIRED (VERSION 2.6)

# THE VERSION NUMBER
SET (Tutorial_VERSION_MAJOR 1)
SET (Tutorial_VERSION_MINOR 0)

# ENABLE ASM
ENABLE_LANGUAGE(ASM)

SET(CMAKE_STATIC_LIBRARY_PREFIX)
SET(CMAKE_STATIC_LIBRARY_SUFFIX)

SET(CMAKE_EXECUTABLE_LIBRARY_PREFIX)
SET(CMAKE_EXECUTABLE_LIBRARY_SUFFIX)

 
# CURRENT DIRECTORY
SET(ProjDirPath ${CMAKE_CURRENT_SOURCE_DIR})

# DEBUG LINK FILE
set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -T${ProjDirPath}/MCIMX6X_M4_ddr.ld  -static")

# RELEASE LINK FILE
set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -T${ProjDirPath}/MCIMX6X_M4_ddr.ld  -static")

# DEBUG ASM FLAGS
SET(CMAKE_ASM_FLAGS_DEBUG "${CMAKE_ASM_FLAGS_DEBUG} -g  -mcpu=cortex-m4  -mfloat-abi=hard  -mfpu=fpv4-sp-d16  -mthumb  -Wall  -fno-common  -ffunction-sections  -fdata-sections  -ffreestanding  -fno-builtin  -mapcs  -std=gnu99")

# DEBUG C FLAGS
SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g  -O0  -fno-strict-aliasing  -mcpu=cortex-m4  -mfloat-abi=hard  -mfpu=fpv4-sp-d16  -mthumb  -MMD  -MP  -Wall  -fno-common  -ffunction-sections  -fdata-sections  -ffreestanding  -fno-builtin  -mapcs  -std=gnu99")

# DEBUG CXX FLAGS
SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g  -O0  -fno-strict-aliasing  -mcpu=cortex-m4  -mfloat-abi=hard  -mfpu=fpv4-sp-d16  -mthumb  -MMD  -MP  -Wall  -fno-common  -ffunction-sections  -fdata-sections  -ffreestanding  -fno-builtin  -mapcs  -std=gnu++11 -fno-exceptions -fno-rtti")

# DEBUG LD FLAGS
SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -g  -mcpu=cortex-m4  -mfloat-abi=hard  -mfpu=fpv4-sp-d16  --specs=nano.specs  -lm  -Wall  -fno-common  -ffunction-sections  -fdata-sections  -ffreestanding  -fno-builtin  -Os  -mthumb  -mapcs  -Xlinker --gc-sections  -Xlinker -static  -Xlinker -z  -Xlinker muldefs")

# RELEASE ASM FLAGS
SET(CMAKE_ASM_FLAGS_RELEASE "${CMAKE_ASM_FLAGS_RELEASE} -mcpu=cortex-m4  -mfloat-abi=hard  -mfpu=fpv4-sp-d16  -mthumb  -Wall  -fno-common  -ffunction-sections  -fdata-sections  -ffreestanding  -fno-builtin  -mapcs  -std=gnu99")

# RELEASE C FLAGS
SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -Os  -fno-strict-aliasing  -mcpu=cortex-m4  -mfloat-abi=hard  -mfpu=fpv4-sp-d16  -mthumb  -MMD  -MP  -Wall  -fno-common  -ffunction-sections  -fdata-sections  -ffreestanding  -fno-builtin  -mapcs  -std=gnu99")

# RELEASE CXX FLAGS
SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Os  -fno-strict-aliasing  -mcpu=cortex-m4  -mfloat-abi=hard  -mfpu=fpv4-sp-d16  -mthumb  -MMD  -MP  -Wall  -fno-common  -ffunction-sections  -fdata-sections  -ffreestanding  -fno-builtin  -mapcs  -std=gnu++11  -fno-exceptions -fno-rtti")

# RELEASE LD FLAGS
SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -mcpu=cortex-m4  -mfloat-abi=hard  -mfpu=fpv4-sp-d16  --specs=nano.specs  -lm  -Wall  -fno-common  -ffunction-sections  -fdata-sections  -ffreestanding  -fno-builtin  -Os  -mthumb  -mapcs  -Xlinker --gc-sections  -Xlinker -static  -Xlinker -z  -Xlinker muldefs")

# ASM MACRO
SET(CMAKE_ASM_FLAGS_DEBUG "${CMAKE_ASM_FLAGS_DEBUG}  -D__DEBUG")

# C MACRO
SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG}  -D__DEBUG")
SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG}  -DM4FIRMWARE")
SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE}  -D__NDEBUG")
SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE}  -DM4FIRMWARE")

# CXX MACRO

SET(INCLUDE_DIR)
file(GLOB_RECURSE H_SRCS_PATH ${ProjDirPath}/../*.h)
foreach(file ${H_SRCS_PATH})
    # MESSAGE( STATUS "file: ${file}")
    string(REGEX MATCH "((/.*)*/)" dir_path ${file})
    INCLUDE_DIRECTORIES(${dir_path})
    list(APPEND INCLUDE_DIR ${dir_path})
endforeach()

SET(DIR_SRCS  
    # ${ProjDirPath}/..
    ${ProjDirPath}/../dev
    ${ProjDirPath}/../board
    ${ProjDirPath}/../platform
    ${ProjDirPath}/../common
    ${ProjDirPath}/../devs
    ${ProjDirPath}/../relay
)

SET(ALL_SRCS)
# MESSAGE( STATUS "==========S file==========\n ${DIR_SRCS}")
foreach(DIR ${DIR_SRCS})
    file(GLOB_RECURSE C_SRCS_PATH ${DIR}/*.c)
    file(GLOB_RECURSE CPP_SRCS_PATH ${DIR}/*.cpp)
    file(GLOB_RECURSE S_SRCS_PATH ${DIR}/*.S)
    file(GLOB_RECURSE H_SRCS_PATH ${DIR}/*.h)
    list(APPEND ALL_SRCS ${C_SRCS_PATH} ${CPP_SRCS_PATH} ${S_SRCS_PATH} ${H_SRCS_PATH})
endforeach()

ADD_EXECUTABLE(dtu_m4 
    ${ALL_SRCS}
)
SET_TARGET_PROPERTIES(dtu_m4 PROPERTIES OUTPUT_NAME "dtu_m4.elf")

TARGET_LINK_LIBRARIES(dtu_m4 -Wl,--start-group)
# LIBRARIES
IF(CMAKE_BUILD_TYPE MATCHES Debug)
ELSEIF(CMAKE_BUILD_TYPE MATCHES Release)
ENDIF()

# SYSTEM LIBRARIES
TARGET_LINK_LIBRARIES(dtu_m4 m)
TARGET_LINK_LIBRARIES(dtu_m4 c)
TARGET_LINK_LIBRARIES(dtu_m4 c) #keep twice, for CXX
TARGET_LINK_LIBRARIES(dtu_m4 gcc)
TARGET_LINK_LIBRARIES(dtu_m4 nosys)
TARGET_LINK_LIBRARIES(dtu_m4 -Wl,--end-group)
TARGET_LINK_LIBRARIES(dtu_m4 "${ProjDirPath}/../platform/CMSIS/Lib/libarm_cortexM4lf_math.a")

# MAP FILE
SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG}  -Xlinker -Map=debug/dtu_m4.map")
SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE}  -Xlinker -Map=release/dtu_m4.map")

# BIN AND HEX
ADD_CUSTOM_COMMAND(TARGET dtu_m4 POST_BUILD COMMAND ${CMAKE_OBJCOPY} -Oihex ${EXECUTABLE_OUTPUT_PATH}/dtu_m4.elf ${EXECUTABLE_OUTPUT_PATH}/dtu_m4.hex)
ADD_CUSTOM_COMMAND(TARGET dtu_m4 POST_BUILD COMMAND ${CMAKE_OBJCOPY} -Obinary ${EXECUTABLE_OUTPUT_PATH}/dtu_m4.elf ${EXECUTABLE_OUTPUT_PATH}/dtu_m4.bin)
