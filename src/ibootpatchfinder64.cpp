//
//  ibootpatchfinder64.cpp
//  liboffsetfinder64
//
//  Created by tihmstar on 28.07.20.
//  Copyright © 2020 tihmstar. All rights reserved.
//

#include "ibootpatchfinder64.hpp"

#include "ibootpatchfinder64_base.hpp"
#include "ibootpatchfinder64_iOS14.hpp"


using namespace std;
using namespace tihmstar::offsetfinder64;
using namespace tihmstar::libinsn;

#define IBOOT_STAGE_STR_OFFSET 0x200
#define IBOOT_MODE_STR_OFFSET 0x240
#define IBOOT_VERS_STR_OFFSET 0x280
#define iBOOT_BASE_OFFSET 0x318
#define iBOOT_14_BASE_OFFSET 0x300
#define KERNELCACHE_PREP_STRING "__PAGEZERO"
#define ENTERING_RECOVERY_CONSOLE "Entering recovery mode, starting command prompt"
#define DEBUG_ENABLED_DTRE_VAR_STR "debug-enabled"
#define DEFAULT_BOOTARGS_STR "rd=md0 nand-enable-reformat=1 -progress"
#define DEFAULT_BOOTARGS_STR_13 "rd=md0 -progress -restore"
#define CERT_STR "Apple Inc.1"


ibootpatchfinder64::ibootpatchfinder64(bool freeBuf)
: patchfinder64(freeBuf)
{
    //
}

ibootpatchfinder64 *ibootpatchfinder64::make_ibootpatchfinder64(const char * filename){
    bool didConstructSuccessfully = false;
    int fd = 0;
    uint8_t *buf = NULL;
    cleanup([&]{
        if (fd>0) close(fd);
        if (!didConstructSuccessfully) {
            safeFreeConst(buf);
        }
    })
    struct stat fs = {0};
    size_t bufSize = 0;
    
    assure((fd = open(filename, O_RDONLY)) != -1);
    assure(!fstat(fd, &fs));
    assure((buf = (uint8_t*)malloc(bufSize = fs.st_size)));
    assure(read(fd,(void*)buf,bufSize)== bufSize);
    

    auto ret = make_ibootpatchfinder64(buf, bufSize, true);
    didConstructSuccessfully = true;
    return ret;
}

ibootpatchfinder64 *ibootpatchfinder64::make_ibootpatchfinder64(const void *buffer, size_t bufSize, bool takeOwnership){
    uint8_t *buf = NULL;
    uint32_t vers = 0;
    uint32_t vers_arr[5];

    buf = (uint8_t*)buffer;
    assure(bufSize > 0x1000);
    
    assure(!strncmp((char*)&buf[IBOOT_VERS_STR_OFFSET], "iBoot", sizeof("iBoot")-1));
    retassure(*(uint32_t*)&buf[0] == 0x90000000, "invalid magic");

    retassure(vers = atoi((char*)&buf[IBOOT_VERS_STR_OFFSET+6]), "No iBoot version found!\n");
    std::string vers_str = std::string((char*)&buf[IBOOT_VERS_STR_OFFSET+6]);
    for(int i = 0; i < 5; i++) {
        std::size_t pos = vers_str.find('.');
        if(pos != std::string::npos) {
            vers_str = vers_str.substr(pos + 1, vers_str.size() - 1);
            vers_arr[i] = atoi((char*)vers_str.c_str());
        }
    }
    debug("iBoot-%d inputted\n", vers);

    if (vers >= 6671) {
        if(vers >= 7429 && vers < 8419) {
            printf("iOS 15 iBoot detected!\n");
        } else if(vers >= 8419 && vers <= 9000) {
            printf("iOS 16 iBoot detected!\n");
        } else if(vers < 7429) {
            printf("iOS 14 iBoot detected!\n");
        } else {
            printf("Unknown iOS versioned iBoot detected!\n");
        }
        return new ibootpatchfinder64_iOS14(buf,bufSize,takeOwnership);
    }
    
    return new ibootpatchfinder64_base(buf,bufSize,takeOwnership);
}

ibootpatchfinder64::~ibootpatchfinder64(){
    //
}

bool ibootpatchfinder64::has_kernel_load(){
    reterror("not implemented by provider");
}

bool ibootpatchfinder64::has_recovery_console(){
    reterror("not implemented by provider");
}

std::vector<patch> ibootpatchfinder64::get_sigcheck_patch(){
    reterror("not implemented by provider");
}

std::vector<patch> ibootpatchfinder64::get_demotion_patch(){
    reterror("not implemented by provider");
}

std::vector<patch> ibootpatchfinder64::get_boot_arg_patch(const char *bootargs){
    reterror("not implemented by provider");
}

std::vector<patch> ibootpatchfinder64::get_debug_enabled_patch(){
    reterror("not implemented by provider");
}

std::vector<patch> ibootpatchfinder64::get_cmd_handler_patch(const char *cmd_handler_str, uint64_t ptr){
    reterror("not implemented by provider");
}

std::vector<patch> ibootpatchfinder64::replace_bgcolor_with_memcpy(){
    reterror("not implemented by provider");
}

std::vector<patch> ibootpatchfinder64::get_ra1nra1n_patch(){
    reterror("not implemented by provider");
}

std::vector<patch> ibootpatchfinder64::get_unlock_nvram_patch(){
    reterror("not implemented by provider");
}

std::vector<patch> ibootpatchfinder64::get_nvram_nosave_patch(){
    reterror("not implemented by provider");
}

std::vector<patch> ibootpatchfinder64::get_nvram_noremove_patch(){
    reterror("not implemented by provider");
}

std::vector<patch> ibootpatchfinder64::get_freshnonce_patch(){
    reterror("not implemented by provider");
}

std::vector<patch> ibootpatchfinder64::get_change_reboot_to_fsboot_patch(){
    reterror("not implemented by provider");
}

std::vector<patch> ibootpatchfinder64::local_boot_patch(){
    reterror("not implemented by provider");
}

std::vector<patch> ibootpatchfinder64::renamed_snapshot_patch(){
    reterror("not implemented by provider");
}

loc_t ibootpatchfinder64::find_iBoot_logstr(uint64_t loghex, int skip, uint64_t shortdec){
    reterror("not implemented by provider");
}

uint32_t ibootpatchfinder64::get_el1_pagesize(){
    reterror("not implemented by provider");
}

std::vector<patch> ibootpatchfinder64::get_rw_and_x_mappings_patch_el1(){
    reterror("not implemented by provider");
}
