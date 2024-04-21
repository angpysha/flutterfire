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

#include "FirebaseRemoteConfigImplementation.h"
#include <flutter/event_channel.h>
#include <flutter/event_stream_handler_functions.h>

#include "messages.g.h"
#include "remote_config_pigeon_implemetation.h"

using namespace firebase::remote_config;

extern "C" firebase_core_windows::FirebasePluginRegistry * GetFlutterFirebaseRegistry();


namespace firebase_remote_config_windows
{
    const char* kEventChannelName = "plugins.flutter.io/firebase_remote_config_updated";
    std::unique_ptr<flutter::EventSink<flutter::EncodableValue>> sink_;

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

        const auto firebase_registry = firebase_core_windows::FirebasePluginRegistry::GetInstance();
        const auto shared_plugin = std::make_shared<FirebaseRemoteConfigImplementation>();

        ::firebase::App::RegisterLibrary("firebase_remote_config", "5.0.0", nullptr);
        firebase_registry->put_plugin_ref(shared_plugin);

        const auto impl = new remote_config_pigeon_implemetation();
        RemoteConfigHostApi::SetUp(registrar->messenger(), impl);

        const auto event_channel = std::make_unique<flutter::EventChannel<flutter::EncodableValue>>(
            registrar->messenger(), kEventChannelName,
            &flutter::StandardMethodCodec::GetInstance());

        auto eventChannelHandler = std::make_unique<flutter::StreamHandlerFunctions<flutter::EncodableValue>>([&](const flutter::EncodableValue* arguments,
            std::unique_ptr<flutter::EventSink<flutter::EncodableValue>> sink)->std::unique_ptr < flutter::StreamHandlerError < flutter::EncodableValue >>
            {
                //sink_ = std::move(sink);
                auto firebaseApp = ::firebase::App::GetInstance(firebase_core_windows::FirebasePluginRegistry::GetInstance()->app_name.c_str());
                auto remoteConfig = ::firebase::remote_config::RemoteConfig::GetInstance(firebaseApp);
                auto registration = remoteConfig->AddOnConfigUpdateListener([&sink, this](ConfigUpdate&& config_update, RemoteConfigError error)
                    {
                        const auto updatedKeys = config_update.updated_keys;
                        flutter::EncodableList keys{};

                        for (const auto& key : updatedKeys)
                        {
                            keys.push_back(flutter::EncodableValue(key));
                        }
                        sink->Success(flutter::EncodableValue(keys));
                        /*flutter::EncodableMap map;
                        map[flutter::EncodableValue("source")] = flutter::EncodableValue(static_cast<int>(config_update.source));
                        map[flutter::EncodableValue("status")] = flutter::EncodableValue(static_cast<int>(config_update.status));
                        map[flutter::EncodableValue("lastFetchTime")] = flutter::EncodableValue(static_cast<int>(config_update.last_fetch_time));
                        map[flutter::EncodableValue("failureReason")] = flutter::EncodableValue(static_cast<int>(config_update.failure_reason));
                        map[flutter::EncodableValue("message")] = flutter::EncodableValue(config_update.message);
                        map[flutter::EncodableValue("value")] = flutter::EncodableValue(config_update.value);
                        sink->Success(flutter::EncodableValue(map));*/
                    });
                //remoteConfig->AddOnConfigUpdateListener()

                return nullptr;
            },
            [](const flutter::EncodableValue* arguments) ->std::unique_ptr < flutter::StreamHandlerError < flutter::EncodableValue >>
            {
                return nullptr;
            });

        event_channel->SetStreamHandler(std::move(eventChannelHandler));
        //event_channel->

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
