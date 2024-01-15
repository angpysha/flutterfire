//
// Created by Andrii on 13.01.2024.
//

#ifndef WINDOWS_FIREBASEREMOTECONFIGIMPLEMENTATION_H
#define WINDOWS_FIREBASEREMOTECONFIGIMPLEMENTATION_H
#include "messages.g.h"
#include "firebase_core/flutter_firebase_plugin.h"
//#include "firebase/app.h"


#include <string>
//#include "firebase_core/firebase_core_plugin_c_api.h"


namespace firebase_remote_config_windows {

    class FirebaseRemoteConfigImplementation :
            public RemoteConfigHostApi,
            public firebase_core_windows::FlutterFirebasePlugin {
    public:
        FirebaseRemoteConfigImplementation() {}
//        virtual ~FirebaseRemoteConfigImplementation() override {}

        virtual std::string plugin_name() override;

        virtual flutter::EncodableMap get_plugin_constants(const ::firebase::App &) override;
//        virtual void EnsureInitialized(
//                const std::string& app_name,
//                std::function<void(std::optional<FlutterError> reply)> result) override;
//        virtual void Activate(
//                const std::string& app_name,
//                std::function<void(ErrorOr<bool> reply)> result) override;
//        virtual void Fetch(
//                const std::string& app_name,
//                std::function<void(std::optional<FlutterError> reply)> result) override;
//        virtual void FetchAndActivate(
//                const std::string& app_name,
//                std::function<void(ErrorOr<bool> reply)> result) override;
//        virtual void SetConfigSettings(
//                const std::string& app_name,
//                int64_t fetch_timeout,
//                int64_t minimum_fetch_interval,
//                std::function<void(std::optional<FlutterError> reply)> result) override;
//        virtual void SetDefaults(
//                const std::string& app_name,
//                const flutter::EncodableMap& default_parameters,
//                std::function<void(std::optional<FlutterError> reply)> result) override;
//        virtual void GetAll(
//                const std::string& app_name,
//                std::function<void(ErrorOr<std::optional<flutter::EncodableMap>> reply)> result) override;
//        virtual void GetProperties(
//                const std::string& app_name,
//                std::function<void(ErrorOr<std::optional<flutter::EncodableMap>> reply)> result)  override;
    private:
        std::string app_name_;
    };
}


#endif //WINDOWS_FIREBASEREMOTECONFIGIMPLEMENTATION_H
