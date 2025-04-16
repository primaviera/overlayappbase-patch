#include <wups.h>

#include <function_patcher/function_patching.h>

#include <coreinit/title.h>

#include "cfg.hpp"
#include "logger.h"
#include "patches.hpp"

WUPS_PLUGIN_NAME("overlayappbase-patch");
WUPS_PLUGIN_DESCRIPTION("");
WUPS_PLUGIN_VERSION("v1.1");
WUPS_PLUGIN_AUTHOR("primaviera");
WUPS_PLUGIN_LICENSE("GPLv3");

WUPS_USE_WUT_DEVOPTAB();
WUPS_USE_STORAGE("overlayappbase_patch");

INITIALIZE_PLUGIN()
{
    initLogging();
    DEBUG_FUNCTION_LINE("Hello World!");

    cfg::init();
    if (FunctionPatcher_InitLibrary() != FUNCTION_PATCHER_RESULT_SUCCESS) {
        DEBUG_FUNCTION_LINE_ERR("Failed to init FunctionPatcher");
        return;
    }

    patches::perform_men_patches(cfg::patch_men);
}

DEINITIALIZE_PLUGIN()
{
    patches::perform_men_patches(false);
    patches::perform_hbm_patches(false);

    FunctionPatcher_DeInitLibrary();
    deinitLogging();
}

ON_APPLICATION_START()
{
    initLogging();
}

ON_APPLICATION_ENDS()
{
    deinitLogging();
}
