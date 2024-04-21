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
        //"plugins.flutter.io/firebase_remote_config_updated"

        auto event_channel = std::make_unique<flutter::EventChannel<flutter::EncodableValue>>(
            registrar->messenger(), kEventChannelName,
            &flutter::StandardMethodCodec::GetInstance());

        // auto eventChannelHandler = [](std::unique_ptr<flutter::StreamHandler<flutter::EncodableMap>> handler)
        // {
        //     handler->
        // };

        // template <typename T>
        // using StreamHandlerListen =
        //     std::function<std::unique_ptr<StreamHandlerError<T>>(
        //         const T* arguments,
        //         std::unique_ptr<EventSink<T>>&& events)>;

        // auto eventChannelHandler = std::make_unique<flutter::StreamHandler<flutter::EncodableValue>>(
        //     [](const flutter::EncodableValue* arguments,
        //         std::unique_ptr<flutter::EventSink<flutter::EncodableValue>> events,
        //         std::unique_ptr<flutter::StreamHandlerError<flutter::EncodableValue>> error) {
        //             // Handle the event here.
        //     },
        //     [](const flutter::EncodableValue* arguments,
        //     std::unique_ptr<flutter::StreamHandlerError<flutter::EncodableValue>> error) {
        //             // Handle cancellation here.
        //     });
        // template <typename T>
        // using StreamHandlerCancel =
        //     std::function<std::unique_ptr<StreamHandlerError<T>>(const T* arguments)>;

       // event_channel->SetStreamHandler(std::move(eventChannelHandler));


        auto eventChannelHandler = std::make_unique<flutter::StreamHandlerFunctions<flutter::EncodableValue>>([&](const flutter::EncodableValue* arguments,
            std::unique_ptr<flutter::EventSink<flutter::EncodableValue>> sink)->std::unique_ptr < flutter::StreamHandlerError < flutter::EncodableValue >>
            {
                sink_ = std::move(sink);
                auto firebaseApp = ::firebase::App::GetInstance();
                auto remoteConfig = ::firebase::remote_config::RemoteConfig::GetInstance(firebaseApp);

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
