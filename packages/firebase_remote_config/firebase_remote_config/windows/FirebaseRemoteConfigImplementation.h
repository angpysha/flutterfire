//
// Created by Andrii on 13.01.2024.
//
#pragma once
#ifndef WINDOWS_FIREBASEREMOTECONFIGIMPLEMENTATION_H
#define WINDOWS_FIREBASEREMOTECONFIGIMPLEMENTATION_H
#include "messages.g.h"
#include "firebase_core/flutter_firebase_plugin.h"
//#include "firebase/app.h"


#include <string>
//#include "firebase_core/firebase_core_plugin_c_api.h"


namespace firebase_remote_config_windows {

    class FirebaseRemoteConfigImplementation :
            //public TestHostApi,
            public firebase_core_windows::FlutterFirebasePlugin {
    public:
        FirebaseRemoteConfigImplementation() {}
//        virtual ~FirebaseRemoteConfigImplementation() override {}

        virtual std::string plugin_name() override;

        virtual flutter::EncodableMap get_plugin_constants(const ::firebase::App &) override;

    private:
        std::string app_name_;
    };
}


#endif //WINDOWS_FIREBASEREMOTECONFIGIMPLEMENTATION_H
