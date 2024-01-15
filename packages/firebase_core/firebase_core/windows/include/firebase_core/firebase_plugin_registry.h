//
// Created by Andrii on 13.01.2024.
//

#ifndef TODO_POINTS_FIREBASE_PLUGIN_REGISTRY_H
#define TODO_POINTS_FIREBASE_PLUGIN_REGISTRY_H

#ifdef BUILDING_SHARED_DLL
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT __declspec(dllimport)
#endif

#include "../../messages.g.h"
#include "firebase/app.h"
#include <string>
#include <map>
#include "flutter_firebase_plugin.h"
#include <mutex>
#include <memory>
#include "firebase_core_api.h"
#include <time.h>
#include <vector>

namespace firebase_core_windows {

    class FirebasePluginRegistry {
    public:
         FirebasePluginRegistry ()
         {
             srand(time(NULL));
             value_ = rand() % 150;
             test_strings_ = {};
             pConstants_ = {};
             test_strings_.push_back("testt");
         }

         static FirebasePluginRegistry* GetInstance();
//        static FirebasePluginRegistry* GetInstance() {
//            static FirebasePluginRegistry instance;
//            return &instance;
//        }
//
//        static FirebasePluginRegistry* GetSharedInstance();
//
//        FirebasePluginRegistry(const FirebasePluginRegistry&) = delete;
//        FirebasePluginRegistry& operator=(const FirebasePluginRegistry&) = delete;

        void RegisterPlugin(std::string pluginName, std::string version, FlutterFirebasePlugin* plugin);

        std::map<std::string, FlutterFirebasePlugin*>& pluginConstants();
        void put_plugin_ref(std::shared_ptr<FlutterFirebasePlugin>);
        std::vector<std::shared_ptr<FlutterFirebasePlugin>>& p_constants();

    private:
//        FirebasePluginRegistry() = default;
//        mutable std::mutex mutex_;
        std::map<std::string, FlutterFirebasePlugin*> pluginConstants_;
        int value_;
        std::vector<std::string> test_strings_;
        std::vector<std::shared_ptr<FlutterFirebasePlugin>> pConstants_;
    };

}
#endif //TODO_POINTS_FIREBASE_PLUGIN_REGISTRY_H

MY_DLL_API ::firebase_core_windows::FirebasePluginRegistry& get_flutter_firebase_plugin_registry();

MY_DLL_API void add_plugin_constant(std::shared_ptr<::firebase_core_windows::FlutterFirebasePlugin> item);