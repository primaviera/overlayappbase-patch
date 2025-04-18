#include <wups.h>
#include <wups/config/WUPSConfigItemBoolean.h>
#include <wups/config_api.h>

#include "logger.h"

namespace cfg {

bool patch_men = false;
bool patch_hbm = false;

void bool_changed(ConfigItemBoolean* item, bool new_value)
{
    if (std::string_view("patch_men") == item->identifier)
        patch_men = new_value;
    if (std::string_view("patch_hbm") == item->identifier)
        patch_hbm = new_value;

    WUPSStorageAPI::Store(item->identifier, new_value);
}

WUPSConfigAPICallbackStatus open(WUPSConfigCategoryHandle root_handle)
{
    try {
        WUPSConfigCategory root = WUPSConfigCategory(root_handle);

        root.add(WUPSConfigItemBoolean::Create("patch_men", "Patch Wii U Menu",
            false, patch_men,
            &bool_changed));

        root.add(WUPSConfigItemBoolean::Create("patch_hbm", "Patch HOME Menu",
            false, patch_hbm,
            &bool_changed));

    } catch (std::exception& e) {
        DEBUG_FUNCTION_LINE_ERR("Failed to open config menu: %s\n", e.what());
        return WUPSCONFIG_API_CALLBACK_RESULT_ERROR;
    }
    return WUPSCONFIG_API_CALLBACK_RESULT_SUCCESS;
}

void close()
{
    DEBUG_FUNCTION_LINE_ERR("Failed to close storage");
}

#define LOAD(key, default_value)                                                                             \
    if ((res = WUPSStorageAPI::GetOrStoreDefault(#key, key, default_value)) != WUPS_STORAGE_ERROR_SUCCESS) { \
        DEBUG_FUNCTION_LINE_ERR("GetOrStoreDefault failed: %s (%d)", WUPSStorageAPI_GetStatusStr(res), res); \
    }

void init()
{
    WUPSConfigAPIOptionsV1 options = { .name = "overlayappbase-patch" };
    if (WUPSConfigAPI_Init(options, open, close)) {
        DEBUG_FUNCTION_LINE_ERR("Failed to init config api");
    }

    WUPSStorageError res;
    LOAD(patch_men, false);
    LOAD(patch_hbm, false);

    if ((res = WUPSStorageAPI::SaveStorage()) != WUPS_STORAGE_ERROR_SUCCESS) {
        DEBUG_FUNCTION_LINE_ERR("SaveStorage failed: %s (%d)", WUPSStorageAPI_GetStatusStr(res), res);
    }
}

#undef LOAD

}
