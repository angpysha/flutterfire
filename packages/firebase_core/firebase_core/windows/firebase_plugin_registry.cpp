//
// Created by Andrii on 13.01.2024.
//

#include "include/firebase_core/firebase_plugin_registry.h"
#include "firebase/app.h"
#include <windows.h>
#include "include/firebase_core/singleton.h"

extern firebase_core_windows::FirebasePluginRegistry* registry_instance_ = 0;

namespace firebase_core_windows {

    // std::map <std::string, FlutterFirebasePlugin*> FirebasePluginRegistry::pluginConstants_{};

    FirebasePluginRegistry* FirebasePluginRegistry::GetInstance() {
        if (registry_instance_ == 0) {
            registry_instance_ = new FirebasePluginRegistry();
        }

        return registry_instance_;
    }

    void FirebasePluginRegistry::RegisterPlugin(std::string pluginName, std::string version,
                                                FlutterFirebasePlugin *plugin) {
//        std::lock_guard<std::mutex> lock(mutex_);
        firebase::App::RegisterLibrary(pluginName.c_str(), version.c_str(),
                                       nullptr);

//        auto plugin_name = plugin->plugin_name();
//        auto plugin_constants = plugin->get_plugin_constants();

//        this->pluginConstants_.insert(
//            { plugin->plugin_name(), plugin });
        pluginConstants_[plugin->plugin_name()] = plugin;
    }

    std::map<std::string, FlutterFirebasePlugin *> &FirebasePluginRegistry::pluginConstants() {
//        std::lock_guard<std::mutex> lock(mutex_);
        return this->pluginConstants_;
    }

//    FirebasePluginRegistry* FirebasePluginRegistry::GetSharedInstance() {
//        // Name of the shared memory
//        static const wchar_t* sharedMemName = L"FlutterFirebasePluginSharedSingleton";
//
//        // Create/Open a file mapping object in shared memory
//        HANDLE hMapFile = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, sharedMemName);
//        if (hMapFile == NULL) {
//            hMapFile = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, sizeof(FirebasePluginRegistry), sharedMemName);
//        }
//
//        // Map the shared memory segment
//        void* pBuf = MapViewOfFile(hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(FirebasePluginRegistry));
//        if (pBuf == NULL) {
//            CloseHandle(hMapFile);
//            throw std::runtime_error("Could not map view of file");
//        }
//
//        // Placement new to construct the object in the shared memory
//        FirebasePluginRegistry* instance = new (pBuf) FirebasePluginRegistry();
//        return instance;
//    }

    void FirebasePluginRegistry::put_plugin_ref(std::shared_ptr<FlutterFirebasePlugin> plugin) {
        this->pConstants_.push_back(plugin);
    }

    std::vector<std::shared_ptr<FlutterFirebasePlugin>>& FirebasePluginRegistry::p_constants() {
        return pConstants_;
    }
}

//extern "C" firebase_core_windows::FirebasePluginRegistry* GetFlutterFirebaseRegistry()
//{
//    return &firebase_core_windows::FirebasePluginRegistry::GetInstance();
//}

MY_DLL_API ::firebase_core_windows::FirebasePluginRegistry &get_flutter_firebase_plugin_registry() {
    ::firebase_core_windows::FirebasePluginRegistry &singl = singleton<::firebase_core_windows::FirebasePluginRegistry>();
    return singl;
}

MY_DLL_API void add_plugin_constant(std::shared_ptr<::firebase_core_windows::FlutterFirebasePlugin> item) {
    ::firebase_core_windows::FirebasePluginRegistry &singl = singleton<::firebase_core_windows::FirebasePluginRegistry>();
    singl.put_plugin_ref(item);
}