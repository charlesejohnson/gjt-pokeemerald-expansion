#include "global.h"
#include "event_data.h"
#include "constants/vars.h"
#include "gjt_save_version.h"

// GJT: stamps a save-format version into every save. Future builds compare it to
// GJT_SAVE_VERSION_CURRENT and run upgrade steps for older saves (add a case below).
void GjtSaveVersion_OnLoad(void)
{
    u16 v = VarGet(VAR_GJT_SAVE_VERSION);

    // v0 = save made before versioning existed.
    switch (v)
    {
    case 0:
        // Nothing to upgrade yet.
        // fallthrough
    default:
        break;
    }
    VarSet(VAR_GJT_SAVE_VERSION, GJT_SAVE_VERSION_CURRENT);
}
