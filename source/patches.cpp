#include <wups.h>

#include <function_patcher/function_patching.h>
#include <kernel/kernel.h>

#include <coreinit/filesystem.h>

#include "cfg.hpp"
#include "logger.h"
#include "patches.hpp"

namespace patches {

DECL_FUNCTION(int, ShouldLoadNormalLayout, void) {
    return 1;
}

const uint64_t men_tids[3] = {
    0x5001010040000, 0x5001010040100, 0x5001010040200
};

function_replacement_data_t men_v277 = REPLACE_FUNCTION_OF_EXECUTABLE_BY_ADDRESS_WITH_VERSION(
        ShouldLoadNormalLayout,
	men_tids, sizeof(men_tids) / sizeof(men_tids[0]),
        "men.rpx",
        0x1E0B00,
        277, 277);
PatchedFunctionHandle men_v277_handle = 0;

function_replacement_data_t men_v257 = REPLACE_FUNCTION_OF_EXECUTABLE_BY_ADDRESS_WITH_VERSION(
        ShouldLoadNormalLayout,
	men_tids, sizeof(men_tids) / sizeof(men_tids[0]),
        "men.rpx",
        0x1E0A10,
        257, 257);
PatchedFunctionHandle men_v257_handle = 0;

void perform_men_patches(bool enable)
{
    if (enable) {
        if (auto res = FunctionPatcher_AddFunctionPatch(&men_v277, &men_v277_handle, nullptr) != FUNCTION_PATCHER_RESULT_SUCCESS) {
            DEBUG_FUNCTION_LINE_ERR("Failed to perform patch (%d)", res);
	}
        if (auto res = FunctionPatcher_AddFunctionPatch(&men_v257, &men_v257_handle, nullptr) != FUNCTION_PATCHER_RESULT_SUCCESS) {
            DEBUG_FUNCTION_LINE_ERR("Failed to perform patch (%d)", res);
	}
    } else {
        FunctionPatcher_RemoveFunctionPatch(men_v277_handle);
        FunctionPatcher_RemoveFunctionPatch(men_v257_handle);
    }
}

void perform_hbm_patches(bool enable)
{
    // TODO: Add proper patches once Wii U Menu works
    if (enable) {
    } else {
    }
}

DECL_FUNCTION(int, FSOpenFile, FSClient* pClient, FSCmdBlock* pCmd, const char* path, const char* mode, int* handle, int error)
{
    // HOME Menu tries to open Hbm2-2.pack everytime it is loaded, so this is perfect to perform patches
    if (strcmp("/vol/content/Common/Package/Hbm2-2.pack", path) == 0) {
        perform_hbm_patches(cfg::patch_hbm);
    }

    int result = real_FSOpenFile(pClient, pCmd, path, mode, handle, error);
    return result;
}
WUPS_MUST_REPLACE_FOR_PROCESS(FSOpenFile, WUPS_LOADER_LIBRARY_COREINIT, FSOpenFile, WUPS_FP_TARGET_PROCESS_ALL);
} // namespace patches
