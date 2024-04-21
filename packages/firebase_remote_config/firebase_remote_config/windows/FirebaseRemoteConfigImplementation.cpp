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

    std::string mapLastFetchStatus(LastFetchStatus lastFetchStatus)
    {
        if (lastFetchStatus == kLastFetchStatusSuccess) {
            return "success";
        }
        else if (lastFetchStatus == kLastFetchStatusFailure)
            return "failure";
        else if (lastFetchStatus == kLastFetchStatusPending) {
            return "noFetchYet";
        }
        else {
            return "failure";
        }
        return "success";
    }

    std::string FirebaseRemoteConfigImplementation::plugin_name()
    {
        return "plugins.flutter.io/firebase_remote_config";
    }

    std::string map_source(ValueSource source)
    {
        if (source == kValueSourceStaticValue)
        {
            return "static";
        }
        else if (source == kValueSourceDefaultValue)
        {
            return "default";
        }
        else if (source == kValueSourceRemoteValue)
        {
            return "remote";
        }
        else
        {
            return "static";
        }
    }

    flutter::EncodableMap createRemoteConfigValuesMap(std::string key, RemoteConfig* remote_config) {
        flutter::EncodableMap parsed_parameters;

        ValueInfo value_info{};
        auto data = remote_config->GetData(key.c_str(), &value_info);

        parsed_parameters.insert({ EncodableValue("value"), EncodableValue(data) });
        const auto source_mapped = map_source(value_info.source);
        parsed_parameters.insert({ EncodableValue("source"), EncodableValue(source_mapped.c_str()) });
        return parsed_parameters;

    }

    flutter::EncodableMap mapParameters(const std::map<std::string, firebase::Variant>& parameters, RemoteConfig* remote_config)
    {
        flutter::EncodableMap map_;

        for (const auto& val : parameters)
        {
            auto param = val.second;
            auto name = val.first;

            map_.insert({ name, createRemoteConfigValuesMap(name, remote_config) });

        }

        return map_;
    }

    void get_all_parameters(RemoteConfig* remote_config)
    {
    }

    flutter::EncodableMap FirebaseRemoteConfigImplementation::get_plugin_constants(const ::firebase::App& firebaseApp)
    {
        auto app = const_cast<::firebase::App*>(&firebaseApp);
        //app->SetDefaultConfigPath()
        const auto remoteConfig = RemoteConfig::GetInstance(app);
        const auto configSettings = remoteConfig->GetConfigSettings();
        auto fetchTimeout = static_cast<int64_t>(configSettings.fetch_timeout_in_milliseconds);
        auto minFetchTimeout = static_cast<int64_t>(configSettings.minimum_fetch_interval_in_milliseconds);

        const auto configInfo = remoteConfig->GetInfo();
        const auto lastFetch = static_cast<int64_t>(configInfo.fetch_time);
        const auto lastFetchStatus = configInfo.last_fetch_status;
        const auto lastFetchStatusMapped = mapLastFetchStatus(lastFetchStatus);

        flutter::EncodableMap values;

        values.insert({ EncodableValue("fetchTimeout"), EncodableValue(fetchTimeout) });
        values.insert({ EncodableValue("minimumFetchInterval"), EncodableValue(minFetchTimeout) });
        values.insert({ EncodableValue("lastFetchTime"), EncodableValue(lastFetch) });
        values.insert({ EncodableValue("lastFetchStatus"), EncodableValue(lastFetchStatusMapped.c_str()) });

        const auto allItems = remoteConfig->GetAll();

        auto converted = mapParameters(allItems, remoteConfig);

        values.insert({ EncodableValue("parameters"), converted });

        return values;
    }
}
