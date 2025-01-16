#include "../utils/Utils.h"
#include "../engine/Link.h"

namespace Loader {

    struct ModInfo {
        std::string ModName;
        std::string ModPath;
        bool IsEnabled;
        int ModType;
    };

    std::string SetupModFolder(const std::string& subDir);
    void IndexMods();
    void LoadNativeMods();
    void LoadModPaks();
    void LoadResorcePacks(Engine::AssetManager* s_AssetManagerImpl);
}