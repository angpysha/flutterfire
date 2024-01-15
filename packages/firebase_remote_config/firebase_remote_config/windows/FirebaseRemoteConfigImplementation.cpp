//
// Created by Andrii on 13.01.2024.
//

#include "FirebaseRemoteConfigImplementation.h"
#include <optional>
#include "firebase/remote_config.h"

using namespace firebase::remote_config;
using namespace firebase;
using namespace flutter;

namespace firebase_remote_config_windows
{
    //    std::string mapLastFetchStatus(LastFetchStatus lastFetchStatus);

 /*   void FirebaseRemoteConfigImplementation::EnsureInitialized(
            const std::string &app_name,
            std::function<void(std::optional < FlutterError > reply)> result) {
        auto firebase_app = App::GetInstance(app_name.c_str());
        auto remote_config = RemoteConfig::GetInstance(firebase_app);

        auto initialized_future = remote_config->EnsureInitialized();

        initialized_future.OnCompletion([&] (const Future<ConfigInfo*>) -> {
           result(std::nullopt);
        });
    }

    void FirebaseRemoteConfigImplementation::Activate(
            const std::string &app_name,
            std::function<void(ErrorOr<bool> reply)> result) {
        result(ErrorOr<bool>(FlutterError("nit implemented")));
    }

    void FirebaseRemoteConfigImplementation::Fetch(
            const std::string &app_name,
            std::function<void(std::optional < FlutterError > reply)> result) {

    }

    void FirebaseRemoteConfigImplementation::FetchAndActivate(
            const std::string &app_name,
            std::function<void(ErrorOr<bool> reply)> result) {
        result(FlutterError("nit implemented"));
    }

    void FirebaseRemoteConfigImplementation::SetConfigSettings(
            const std::string &app_name,
            int64_t fetch_timeout,
            int64_t minimum_fetch_interval,
            std::function<void(std::optional < FlutterError > reply)> result) {
        result(FlutterError("nit implemented"));
    }

    void FirebaseRemoteConfigImplementation::SetDefaults(
            const std::string &app_name,
            const flutter::EncodableMap &default_parameters,
            std::function<void(std::optional<FlutterError>reply)> result) {
        result(FlutterError("nit implemented"));
    }

    void FirebaseRemoteConfigImplementation::GetAll(
            const std::string &app_name,
            std::function<void(ErrorOr<std::optional<flutter::EncodableMap>> reply)

    > result) {
    result(ErrorOr<std::optional < flutter::EncodableMap>>
    (FlutterError("nit implemented")));

    }

    void FirebaseRemoteConfigImplementation::GetProperties(
            const std::string &app_name,
            std::function<void(ErrorOr < std::optional < flutter::EncodableMap >> reply)> result) {
        result(ErrorOr < std::optional < flutter::EncodableMap >> (FlutterError("nit implemented")));

    }*/

    std::string mapLastFetchStatus(LastFetchStatus lastFetchStatus)
    {
                if (lastFetchStatus == kLastFetchStatusSuccess) {
                    return "success";
                } else if (lastFetchStatus == kLastFetchStatusFailure) {
                    return "failure";
                } else if (lastFetchStatus == kLastFetchStatusPending) {
                    return "noFetchYet";
                } else {
                    return "failure";
                }
        return "success";
    }

    std::string FirebaseRemoteConfigImplementation::plugin_name()
    {
        return "plugins.flutter.io/firebase_remote_config";
    }

    flutter::EncodableMap mapParameters(std::map<std::string, firebase::Variant> parameters)
    {
        flutter::EncodableMap map_;

        for (const auto &val : parameters)
        {
            auto param = val.second;
            auto name = val.first;

            if (param.is_string())
            {
                auto str_val = param.string_value();
                map_.insert({ flutter::EncodableValue(name.c_str()), EncodableValue(param.string_value()) });
            } else if (param.is_bool())
            {
                map_.insert({ flutter::EncodableValue(name.c_str()), EncodableValue(param.bool_value()) });
            } else if (param.is_int64())
            {
                int64_t int64_val = param.int64_value();
                map_.insert({ flutter::EncodableValue(name.c_str()), EncodableValue(int64_val) });
            }
        }

        return map_;
    }

    flutter::EncodableMap FirebaseRemoteConfigImplementation::get_plugin_constants(const ::firebase::App& firebaseApp)
    {
        //auto appps = firebase::App::GetApps();
        //auto app = firebase::App::GetInstance(name.c_str());
        auto app = const_cast<::firebase::App*>(&firebaseApp);
        auto remoteConfig = RemoteConfig::GetInstance(app);
        auto configSettings = remoteConfig->GetConfigSettings();
        auto fetchTimeout = static_cast<int64_t>(configSettings.fetch_timeout_in_milliseconds);
        auto minFetchTimeout = static_cast<int64_t>(configSettings.minimum_fetch_interval_in_milliseconds);
        
        auto configInfo = remoteConfig->GetInfo();
        auto lastFetch = static_cast<int64_t>(configInfo.fetch_time);
        auto lastFetchStatus = configInfo.last_fetch_status;
        auto lastFetchStatusMapped = mapLastFetchStatus(lastFetchStatus);

        flutter::EncodableMap values;

        values.insert({EncodableValue("fetchTimeout"), EncodableValue(fetchTimeout)});
        values.insert({EncodableValue("minimumFetchInterval"), EncodableValue(minFetchTimeout)});
        values.insert({EncodableValue("lastFetchTime"), EncodableValue(lastFetch)});
        values.insert({EncodableValue("lastFetchStatus"), EncodableValue(lastFetchStatusMapped.c_str())});

        auto allItems = remoteConfig->GetAll();

        auto converted = mapParameters(allItems);

        values.insert({ EncodableValue("parameters"), converted });

        return values;
        //    }

        // [configProperties setValue : @([fetchTimeout longValue]) forKey : @"fetchTimeout"] ;
        // [configProperties setValue : @([minimumFetchInterval longValue]) forKey : @"minimumFetchInterval"] ;
        // [configProperties setValue : @([lastFetchMillis longValue]) forKey : @"lastFetchTime"] ;
        // [configProperties setValue : [self mapLastFetchStatus : [remoteConfig lastFetchStatus] ]
        //     forKey : @"lastFetchStatus"] ;
    }
}
