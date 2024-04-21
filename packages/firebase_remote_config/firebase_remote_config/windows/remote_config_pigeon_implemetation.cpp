//
// Created by Andrii on 15.01.2024.
//

#include "remote_config_pigeon_implemetation.h"
#include "firebase/app.h"
#include "firebase/remote_config.h"
#include <future>


using namespace firebase::remote_config;
using namespace firebase;
using namespace flutter;

namespace firebase_remote_config_windows
{
    void remote_config_pigeon_implemetation::EnsureInitialized(
        const std::string& app_name,
        std::function<void(std::optional<FlutterError> reply)> result)
    {
        const auto firebase_app = App::GetInstance(app_name.c_str());
        const auto remote_config = RemoteConfig::GetInstance(firebase_app);

        const auto initialized_future = remote_config->EnsureInitialized();

        initialized_future.OnCompletion([result](const Future<ConfigInfo>& futureResult)
            {
                auto futureResultInfo = futureResult.result();
                auto isSuccess = futureResult.status() == kFutureStatusComplete;
                result(std::nullopt);
            });
    }

    void remote_config_pigeon_implemetation::Activate(
        const std::string& app_name,
        std::function<void(ErrorOr<bool> reply)> result)
    {
        const auto firebase_app = App::GetInstance(app_name.c_str());
        const auto remote_config = RemoteConfig::GetInstance(firebase_app);

        const auto activate_future = remote_config->Activate();

        activate_future.OnCompletion([result](const Future<bool>& activate_future_completion)
            {
                const bool is_success = activate_future_completion.result();

                result(ErrorOr<bool>(is_success));
            });
    }

    void remote_config_pigeon_implemetation::Fetch(
        const std::string& app_name,
        std::function<void(std::optional<FlutterError> reply)> result)
    {
        const auto firebase_app = App::GetInstance(app_name.c_str());
        const auto remote_config = RemoteConfig::GetInstance(firebase_app);

        const auto fetch_future = remote_config->EnsureInitialized();

        fetch_future.OnCompletion([result](const Future<ConfigInfo>& fetch_future_completion)
            {
                result(std::nullopt);
            });
    }

    void remote_config_pigeon_implemetation::FetchAndActivate(
        const std::string& app_name,
        std::function<void(ErrorOr<bool> reply)> result)
    {
        const auto firebase_app = App::GetInstance(app_name.c_str());
        const auto remote_config = RemoteConfig::GetInstance(firebase_app);

        const auto activate_future = remote_config->FetchAndActivate();

        activate_future.OnCompletion([result](const Future<bool>& activate_future_completion)
            {
                const bool is_success = activate_future_completion.result();

                result(ErrorOr<bool>(is_success));
            });
    }

    void remote_config_pigeon_implemetation::SetConfigSettings(
        const std::string& app_name,
        int64_t fetch_timeout,
        int64_t minimum_fetch_interval,
        std::function<void(std::optional<FlutterError> reply)> result)
    {
        const auto firebase_app = App::GetInstance(app_name.c_str());
        const auto remote_config = RemoteConfig::GetInstance(firebase_app);

        const ConfigSettings config_setting{ static_cast<uint64_t>(fetch_timeout), static_cast<uint64_t>(minimum_fetch_interval) };

        remote_config->SetConfigSettings(config_setting);

        result(std::nullopt);
    }

    Variant to_variant_(EncodableValue encodableValue)
    {
        if (std::holds_alternative<bool>(encodableValue))
        {
            auto value = std::get<bool>(encodableValue);
            return { value };
        }

        if (std::holds_alternative<int64_t>(encodableValue))
        {
            auto value = std::get<int64_t>(encodableValue);
            return { value };
        }

        if (std::holds_alternative<std::string>(encodableValue))
        {
            auto value = std::get<std::string>(encodableValue);
            return { value };
        }

        if (std::holds_alternative<double>(encodableValue))
        {
            auto value = std::get<double>(encodableValue);
            return { value };
        }

        return {};
    }

    std::vector<ConfigKeyValueVariant> convert_to_native_(const flutter::EncodableMap& default_parameters)
    {
        std::vector<ConfigKeyValueVariant> parameters;
        std::vector<std::pair<std::string, std::string>> storage;

        for (const auto& items : default_parameters) {
            if (std::holds_alternative<std::string>(items.first)) {
                std::string key_str = std::get<std::string>(items.first);


                ConfigKeyValueVariant kv;
                char* key = new char[key_str.size() + 1];
                //strcpy(key, key_str.c_str());
                strcpy_s(key, sizeof(char) * key_str.size() + 1, key_str.c_str());
                kv.key = key;
                kv.value = to_variant_(items.second);
                parameters.push_back(kv);
            }
        }

        return parameters;
    }

    void remote_config_pigeon_implemetation::SetDefaults(
        const std::string& app_name,
        const flutter::EncodableMap& default_parameters,
        std::function<void(std::optional<FlutterError> reply)> result)
    {
        const auto firebase_app = App::GetInstance(app_name.c_str());
        const auto remote_config = RemoteConfig::GetInstance(firebase_app);

        const auto converted_vector = convert_to_native_(default_parameters);
        
        remote_config->SetDefaults(converted_vector.data(), converted_vector.size());
    }

    std::string map_source_(ValueSource source)
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

    flutter::EncodableMap create_remote_config_values_map(std::string key, RemoteConfig* remote_config) {
        flutter::EncodableMap parsed_parameters;

        ValueInfo value_info{};
        auto data = remote_config->GetData(key.c_str(), &value_info);

        parsed_parameters.insert({ EncodableValue("value"), EncodableValue(data) });
        const auto source_mapped = map_source_(value_info.source);
        parsed_parameters.insert({ EncodableValue("source"), EncodableValue(source_mapped.c_str()) });
        return parsed_parameters;

    }

    flutter::EncodableMap map_parameters(std::map<std::string, firebase::Variant> parameters, RemoteConfig* remote_config)
    {
        flutter::EncodableMap map_;

        for (const auto& val : parameters)
        {
            auto param = val.second;
            auto name = val.first;

            map_.insert({ name, create_remote_config_values_map(name, remote_config) });

        }

        return map_;
    }

    void remote_config_pigeon_implemetation::GetAll(
        const std::string& app_name,
        std::function<void(ErrorOr<std::optional<flutter::EncodableMap>> reply)
        > result)
    {
        const auto firebase_app = App::GetInstance(app_name.c_str());
        const auto remote_config = RemoteConfig::GetInstance(firebase_app);

        const auto get_all = remote_config->GetAll();
        //
        auto all_mapped = map_parameters(get_all, remote_config);

        result(ErrorOr(std::make_optional(all_mapped)));
    }

    std::string map_last_fetch_status(LastFetchStatus lastFetchStatus)
    {
        if (lastFetchStatus == kLastFetchStatusSuccess) {
            return "success";
        }
        else if (lastFetchStatus == kLastFetchStatusFailure) {
            return "failure";
        }
        else if (lastFetchStatus == kLastFetchStatusPending) {
            return "noFetchYet";
        }
        else {
            return "failure";
        }
        return "success";
    }

    void remote_config_pigeon_implemetation::GetProperties(
        const std::string& app_name,
        std::function<void(ErrorOr<std::optional<flutter::EncodableMap>> reply)> result)
    {
        const auto firebase_app = App::GetInstance(app_name.c_str());
        const auto remote_config = RemoteConfig::GetInstance(firebase_app);

        const auto configSettings = remote_config->GetConfigSettings();
        auto fetchTimeout = static_cast<int64_t>(configSettings.fetch_timeout_in_milliseconds);
        auto minFetchTimeout = static_cast<int64_t>(configSettings.minimum_fetch_interval_in_milliseconds);

        const auto configInfo = remote_config->GetInfo();
        const auto lastFetch = static_cast<int64_t>(configInfo.fetch_time);
        const auto lastFetchStatus = configInfo.last_fetch_status;
        const auto lastFetchStatusMapped = map_last_fetch_status(lastFetchStatus);
        //
        flutter::EncodableMap values;

        values.insert({ EncodableValue("fetchTimeout"), EncodableValue(fetchTimeout) });
        values.insert({ EncodableValue("minimumFetchInterval"), EncodableValue(minFetchTimeout) });
        values.insert({ EncodableValue("lastFetchTime"), EncodableValue(lastFetch) });
        values.insert({ EncodableValue("lastFetchStatus"), EncodableValue(lastFetchStatusMapped.c_str()) });
        //
        const auto to_return = ErrorOr<std::optional<flutter::EncodableMap>>(std::make_optional(values));

        result(to_return);
        //result(ErrorOr<std::optional<flutter::EncodableMap>>(flutter::Error("not impl")));
    }
}
