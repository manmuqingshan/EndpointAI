/****************************************************************************
*  Copyright 2020 Gabriel Wang (Email:gabriel.wang@arm.com)                 *
*                                                                           *
*  Licensed under the Apache License, Version 2.0 (the "License");          *
*  you may not use this file except in compliance with the License.         *
*  You may obtain a copy of the License at                                  *
*                                                                           *
*     http://www.apache.org/licenses/LICENSE-2.0                            *
*                                                                           *
*  Unless required by applicable law or agreed to in writing, software      *
*  distributed under the License is distributed on an "AS IS" BASIS,        *
*  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. *
*  See the License for the specific language governing permissions and      *
*  limitations under the License.                                           *
*                                                                           *
****************************************************************************/

/*============================ INCLUDES ======================================*/

#include "fine_file_framework.h"
#include <string.h>
#include <rt_sys.h>

#ifdef   __cplusplus
extern "C" {
#endif

/* suppress some warnings for user applications when using arm-2d.
 */
#if defined(__clang__)
#   pragma clang diagnostic ignored "-Wunknown-warning-option"
#   pragma clang diagnostic ignored "-Wreserved-identifier"
#   pragma clang diagnostic ignored "-Wgnu-variable-sized-type-not-at-end"
#   pragma clang diagnostic ignored "-Wgnu-zero-variadic-macro-arguments"
#   pragma clang diagnostic ignored "-Wgnu-statement-expression"
#   pragma clang diagnostic ignored "-Wextra-semi-stmt"
#   pragma clang diagnostic ignored "-Wcompound-token-split-by-macro"
#   pragma clang diagnostic ignored "-Winitializer-overrides"
#   pragma clang diagnostic ignored "-Wgcc-compat"
#   pragma clang diagnostic ignored "-Wundef"
#   pragma clang diagnostic ignored "-Wdeclaration-after-statement"
#   pragma clang diagnostic ignored "-Wflexible-array-extensions"
#   pragma clang diagnostic ignored "-Wcast-qual"
#   pragma clang diagnostic ignored "-Wmissing-prototypes"
#   pragma clang diagnostic ignored "-Wmissing-field-initializers"
#   pragma clang diagnostic ignored "-Wmissing-declarations"
#elif defined(__IS_COMPILER_ARM_COMPILER_5__)
#   pragma diag_suppress 1296,174
#endif

/*============================ MACROS ========================================*/
#ifndef NOP
#   define NOP()            __asm volatile ("nop");
#endif



/*============================ MACROFIED FUNCTIONS ===========================*/
/*============================ TYPES =========================================*/

enum {
    FFF_FILE_TYPE_ID_FOLDER     = 0,                                            //!< folder
    FFF_FILE_TYPE_ID_MEM_FILE,                                                  //!< Memory File
    FFF_USER_TYPE_ID_START,
    /*---------- user defined file type begin -----------*/
    
    FFF_FILE_TYPE_ID_VGA = FFF_USER_TYPE_ID_START,                              //! example user file type: you can write stream to screen
    
    
    /*---------- user defined file type end -------------*/
    FFF_USER_TYPE_COUNT,
};



/*============================ GLOBAL VARIABLES ==============================*/
extern const uint8_t HOTEL_MP3_ROM[];
extern const uint32_t HOTEL_MP3_ROM_Length;

/*============================ LOCAL VARIABLES ===============================*/
/*============================ PROTOTYPES ====================================*/
/*============================ IMPLEMENTATION ================================*/


def_fff(MPSx_Local_Disk,
    use_fff_disk(disk_c,
        arm_mem_file_node_t         hotel_mp3;
    );
    
    use_fff_disk(disk_d,
        use_fff_folder(symphony,
            arm_mem_file_node_t     no_1_mp3;
            arm_mem_file_node_t     no_2_mp3;
            arm_mem_file_node_t     no_3_mp3;
            arm_mem_file_node_t     no_4_mp3;
        );
    );
)

imp_fff(MPSx_Local_Disk,

    fff_disk(disk_c, &MPSx_Local_Disk, disk_d,
        fff_disk_path("C:"),
        fff_list(
            //! memory file: cannon.mp3, read-only
            fff_mem_file(hotel_mp3, &MPSx_Local_Disk.disk_c, hotel_mp3, 
                fff_path("hotel.mp3"),
                fff_access(FFF_READ_ONLY),
                
                fff_mem_content(HOTEL_MP3_ROM, HOTEL_MP3_ROM_Length),
            ),
        ),
    ),
    
    fff_disk(disk_d, &MPSx_Local_Disk, disk_d,
        fff_disk_path("D:"),
        fff_list(
            fff_folder(symphony, &MPSx_Local_Disk.disk_d, symphony,
                fff_folder_path(
                    "symphony\\music\\beethoven", 
                    "symphony/music/beethoven"
                ),

                fff_list(
                    fff_mem_file(no_1_mp3, &MPSx_Local_Disk.disk_d.symphony, no_2_mp3, 
                        fff_path("no_1.mp3"),
                        fff_access(FFF_READ_WRITE),
                    ),
                    fff_mem_file(no_2_mp3, &MPSx_Local_Disk.disk_d.symphony, no_3_mp3, 
                        fff_path("no_2.mp3"),
                        fff_access(FFF_READ_WRITE),
                    ),
                    fff_mem_file(no_3_mp3, &MPSx_Local_Disk.disk_d.symphony, no_4_mp3, 
                        fff_path("no_3.mp3"),
                        fff_access(FFF_READ_WRITE),
                    ),
                    fff_mem_file(no_4_mp3, &MPSx_Local_Disk.disk_d.symphony, no_4_mp3, 
                        fff_path("no_4.mp3"),
                        fff_access(FFF_READ_WRITE),
                    ),
                ),
            ),
        ),
    ),
);


__attribute__((used))
char *_sys_command_string(char *cmd, int len)
{
    (void)cmd;
    (void)len;
    /* write a command line here, which will be passed to main */
    return "--input_file hotel.mp3";
}

/*----------------------------------------------------------------------------*
 * Compiler Specific Code to run __vsf_main_entry() before main()             *
 *----------------------------------------------------------------------------*/
__attribute__((used))
__attribute__((constructor, noreturn))
void __platform_main_entry(void)
{
    const arm_fff_cfg_t tCFG = {
        (const arm_file_node_t *)&MPSx_Local_Disk,
        "c:\\",
    };

    arm_fff_init(&tCFG);
    
    /* should not run to here, error occurred */
    while(1) {
        NOP();
    }
}

/* disable semihosting */
#if defined(__IS_COMPILER_ARM_COMPILER_5__) && __IS_COMPILER_ARM_COMPILER_5__
#   pragma import(__use_no_semihosting)
#elif defined(__IS_COMPILER_ARM_COMPILER_6__) && __IS_COMPILER_ARM_COMPILER_6__
__asm(".global __use_no_semihosting\n\t");
#   ifndef __MICROLIB
__asm(".global __ARM_use_no_argv\n\t");
#   endif
#endif

__attribute__((used))
__attribute__((noreturn))
void _sys_exit(int ch)
{
    (void)ch;
    while(1) {
        NOP();
    }
}

void _ttywrch(int ch)
{
    FFF_UNUSED(ch);
  //your_device_write(&c, 1);
}
int _sys_istty(FILEHANDLE fh)
{
    FFF_UNUSED(fh);
    return -1; /* buffered output */
}



#ifdef   __cplusplus
}
#endif

