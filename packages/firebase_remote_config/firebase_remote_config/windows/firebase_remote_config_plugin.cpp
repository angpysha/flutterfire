#include "firebase_remote_config_plugin.h"

// This must be included before many other Windows headers.
#include <windows.h>

// For getPlatformVersion; remove unless needed for your plugin implementation.
#include <VersionHelpers.h>

#include <flutter/method_channel.h>
#include <flutter/plugin_registrar_windows.h>
#include <flutter/standard_method_codec.h>
#include "firebase_core/firebase_plugin_registry.h"
#include "firebase/remote_config.h"
#include "firebase/app.h"
#include <memory>
#include <sstream>

// #include "FirebaseRemoteConfigImplementation.h"
#include "FirebaseRemoteConfigImplementation.h"
//#include "firebase_core/singleton.h"
#include "messages.g.h"
#include "remote_config_pigeon_implemetation.h"

using namespace firebase::remote_config;

extern "C" firebase_core_windows::FirebasePluginRegistry* GetFlutterFirebaseRegistry();


namespace firebase_remote_config_windows
{
    // static
    void FirebaseRemoteConfigPlugin::RegisterWithRegistrar(
        flutter::PluginRegistrarWindows* registrar)
    {
        auto channel =
            std::make_unique<flutter::MethodChannel<flutter::EncodableValue>>(
                registrar->messenger(), "firebase_remote_config",
                &flutter::StandardMethodCodec::GetInstance());

        auto plugin = std::make_unique<FirebaseRemoteConfigPlugin>();

        channel->SetMethodCallHandler(
            [plugin_pointer = plugin.get()](const auto& call, auto result)
            {
                plugin_pointer->HandleMethodCall(call, std::move(result));
            });

        // auto remoteConfigImplementation = new FirebaseRemoteConfigImplementation();
        // RemoteConfigHostApi::SetUp(registrar->messenger(), remoteConfigImplementation);
        //   auto firebaseRegistry = (firebase_core_windows::FirebasePluginRegistry*)get_flutter_firebase_plugin_registry();
        auto firebaseRegistry = firebase_core_windows::FirebasePluginRegistry::GetInstance();
        auto shared_plugin = std::make_shared<FirebaseRemoteConfigImplementation>();

        //firebaseRegistry->RegisterPlugin("test", "test", remoteConfigImplementation);
        ::firebase::App::RegisterLibrary("firebase_remote_config", "5.0.0", nullptr);
        firebaseRegistry->put_plugin_ref(shared_plugin);
        //add_plugin_constant(shared_plugin);

        auto impl = new remote_config_pigeon_implemetation();
        RemoteConfigHostApi::SetUp(registrar->messenger(), impl);

        registrar->AddPlugin(std::move(plugin));
    }

    FirebaseRemoteConfigPlugin::FirebaseRemoteConfigPlugin()
    {
    }

    FirebaseRemoteConfigPlugin::~FirebaseRemoteConfigPlugin()
    {
    }

    void FirebaseRemoteConfigPlugin::HandleMethodCall(
        const flutter::MethodCall<flutter::EncodableValue>& method_call,
        std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result)
    {
        if (method_call.method_name().compare("getPlatformVersion") == 0)
        {
            std::ostringstream version_stream;
            version_stream << "Windows ";
            if (IsWindows10OrGreater())
            {
                version_stream << "10+";
            }
            else if (IsWindows8OrGreater())
            {
                version_stream << "8";
            }
            else if (IsWindows7OrGreater())
            {
                version_stream << "7";
            }
            result->Success(flutter::EncodableValue(version_stream.str()));
        }
        else
        {
            result->NotImplemented();
        }
    }
} // namespace firebase_remote_config
