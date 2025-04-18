#include <wups.h>

#include <coreinit/title.h>

#include "cfg.hpp"
#include "logger.h"
#include "patches.hpp"

WUPS_PLUGIN_NAME("overlayappbase-patch");
WUPS_PLUGIN_DESCRIPTION("");
WUPS_PLUGIN_VERSION("v1.0");
WUPS_PLUGIN_AUTHOR("primaviera");
WUPS_PLUGIN_LICENSE("GPLv3");

WUPS_USE_WUT_DEVOPTAB();
WUPS_USE_STORAGE("overlayappbase_patch");

INITIALIZE_PLUGIN()
{
    cfg::init();
}

DEINITIALIZE_PLUGIN()
{
    patches::perform_men_patches(false);
    patches::perform_hbm_patches(false);
}

ON_APPLICATION_START()
{
    auto title = OSGetTitleID();
    if (cfg::patch_men) {
        if (title == 0x5001010040000 || title == 0x5001010040100 || title == 0x5001010040200) {
            patches::perform_men_patches(true);
        }
    }
}
