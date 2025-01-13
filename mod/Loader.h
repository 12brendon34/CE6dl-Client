#include "../utils/Utils.h"

namespace Loader {

    struct ModInfo {
        std::wstring ModName;
        bool IsEnabled;
        int ModType;
        std::string ModPath;
    };

    std::string CreateModsFolder();
    void IndexPaks();
    std::vector<ModInfo>& GetModInfoList();
    void LoadModPaks();
}