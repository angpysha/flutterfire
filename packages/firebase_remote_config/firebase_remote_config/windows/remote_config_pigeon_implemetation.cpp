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
        auto firebase_app = App::GetInstance(app_name.c_str());
        auto remote_config = RemoteConfig::GetInstance(firebase_app);

        auto initialized_future = remote_config->EnsureInitialized();

        initialized_future.OnCompletion([result](const Future<ConfigInfo>& futureResult)
            {
                auto futureResultInfo = futureResult.result();
                auto isSuccess = futureResult.status() == kFutureStatusComplete;
                result(std::nullopt);
            });

        //remote_config->

        //        initialized_future.OnCompletion([&] (const Future<ConfigInfo*>) -> {
        //            result(std::nullopt);
        //        });
    }

    // someFunction<int>([](const std::future<int>& futureResult) {
    //     try {
    //         // Access the result of the future. Note: this blocks until the future is ready.
    //         int result = futureResult.get();
    //         std::cout << "Result: " << result << std::endl;
    //     }
    //     catch (const std::exception& e) {
    //         std::cerr << "Error: " << e.what() << std::endl;
    //     }
    //     });

    void remote_config_pigeon_implemetation::Activate(
        const std::string& app_name,
        std::function<void(ErrorOr<bool> reply)> result)
    {
        auto firebase_app = App::GetInstance(app_name.c_str());
        auto remote_config = RemoteConfig::GetInstance(firebase_app);

        auto activate_future = remote_config->Activate();

        activate_future.OnCompletion([result](const Future<bool>& activate_future_completion)
            {
                bool is_success = activate_future_completion.result();

                result(ErrorOr<bool>(is_success));
            });
    }

    void remote_config_pigeon_implemetation::Fetch(
        const std::string& app_name,
        std::function<void(std::optional<FlutterError> reply)> result)
    {
        auto firebase_app = App::GetInstance(app_name.c_str());
        auto remote_config = RemoteConfig::GetInstance(firebase_app);

        auto fetch_future = remote_config->EnsureInitialized();

        fetch_future.OnCompletion([result](const Future<ConfigInfo>& fetch_future_completion)
            {
                result(std::nullopt);
            });
    }

    void remote_config_pigeon_implemetation::FetchAndActivate(
        const std::string& app_name,
        std::function<void(ErrorOr<bool> reply)> result)
    {
        auto firebase_app = App::GetInstance(app_name.c_str());
        auto remote_config = RemoteConfig::GetInstance(firebase_app);

        auto activate_future = remote_config->FetchAndActivate();

        activate_future.OnCompletion([result](const Future<bool>& activate_future_completion)
            {
                bool is_success = activate_future_completion.result();

                result(ErrorOr<bool>(is_success));
            });
    }

    void remote_config_pigeon_implemetation::SetConfigSettings(
        const std::string& app_name,
        int64_t fetch_timeout,
        int64_t minimum_fetch_interval,
        std::function<void(std::optional<FlutterError> reply)> result)
    {
        auto firebase_app = App::GetInstance(app_name.c_str());
        auto remote_config = RemoteConfig::GetInstance(firebase_app);

        ConfigSettings config_setting{ static_cast<uint64_t>(fetch_timeout), static_cast<uint64_t>(minimum_fetch_interval) };

        remote_config->SetConfigSettings(config_setting);

        result(std::nullopt);
    }

    Variant to_variant_(EncodableValue encodableValue)
    {
        /// Null, or no data.
       // kTypeNull,
            /// A 64-bit integer.
            //kTypeInt64,
            /// A double-precision floating point number.
           // kTypeDouble,
            /// A boolean value.
            //kTypeBool,
            /// A statically-allocated string we point to.
            //kTypeStaticString,
            /// A std::string.
           // kTypeMutableString,
            /// A std::vector of Variant.
           // kTypeVector,
            /// A std::map, mapping Variant to Variant.
          //  kTypeMap,
            /// An statically-allocated blob of data that we point to. Never constructed
            /// by default. Use Variant::FromStaticBlob() to create a Variant of this
            /// type.
          //  kTypeStaticBlob,
            /// A blob of data that the Variant holds. Never constructed by default. Use
            /// Variant::FromMutableBlob() to create a Variant of this type, and copy
            /// binary data from an existing source.
         //   kTypeMutableBlob,

        // std::variant<std::monostate,
        //     bool,
        //     int32_t,
        //     int64_t,
        //     double,
        //     std::string,
        //     std::vector<uint8_t>,
        //     std::vector<int32_t>,
        //     std::vector<int64_t>,
        //     std::vector<double>,
        //     EncodableList,
        //     EncodableMap,
        //     CustomEncodableValue,
        //     std::vector<float>>;
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
        /* std::vector<ConfigKeyValue> parameter;

         for (auto &items : default_parameters)
         {
             if (std::holds_alternative<std::string>(items.first) && std::holds_alternative<std::string>(items.second))
             {
                 std::string key_str = std::get<std::string>(items.first);
                 std::string value_str = std::get<std::string>(items.second);

                 ConfigKeyValue value = { key_str.c_str(), value_str.c_str() };
                 parameter.push_back(value);
             }
         }

         return parameter;*/
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
        auto firebase_app = App::GetInstance(app_name.c_str());
        auto remote_config = RemoteConfig::GetInstance(firebase_app);

        auto converted_vector = convert_to_native_(default_parameters);
        int iii = 0;
        remote_config->SetDefaults(converted_vector.data(), converted_vector.size());
        //remote_config->SetDefaults()
       // remote_config->SetDefaults()
    }

    // flutter::EncodableMap mapParameters(std::map<std::string, firebase::Variant> parameters)
    // {
    //     flutter::EncodableMap map_;
    //
    //     for (const auto& val : parameters)
    //     {
    //         auto param = val.second;
    //         auto name = val.first;
    //
    //         if (param.is_string())
    //         {
    //             auto str_val = param.string_value();
    //             map_.insert({ flutter::EncodableValue(name.c_str()), EncodableValue(param.string_value()) });
    //         }
    //         else if (param.is_bool())
    //         {
    //             map_.insert({ flutter::EncodableValue(name.c_str()), EncodableValue(param.bool_value()) });
    //         }
    //         else if (param.is_int64())
    //         {
    //             int64_t int64_val = param.int64_value();
    //             map_.insert({ flutter::EncodableValue(name.c_str()), EncodableValue(int64_val) });
    //         }
    //     }
    //
    //     return map_;
    // }

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

        // value.
        //
        //parsed_parameters.insert({"value", value.blob_data()});
        ValueInfo value_info;
        auto data = remote_config->GetData(key.c_str(), &value_info);

        parsed_parameters.insert({ EncodableValue("value"), EncodableValue(data) });
        auto source_mapped = map_source_(value_info.source);
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
        auto firebase_app = App::GetInstance(app_name.c_str());
        auto remote_config = RemoteConfig::GetInstance(firebase_app);

        auto get_all = remote_config->GetAll();
        //
        auto all_mapped = map_parameters(get_all, remote_config);
        //
        // auto to_return = ErrorOr<std::optional<flutter::EncodableMap>>(std::make_optional(all_mapped));
        //
        // result(to_return);
        // auto activate_future = remote_config->Activate();
        //
        // activate_future.OnCompletion([result](const Future<bool>& activate_future_completion)
        //     {
        //         bool is_success = activate_future_completion.result();
        //
        //         result(ErrorOr<bool>(is_success));
        //     });

        result(ErrorOr(std::make_optional(all_mapped)));
    }
    //
    // std::string mapLastFetchStatus(LastFetchStatus lastFetchStatus){
    //     if (lastFetchStatus == kLastFetchStatusSuccess) {
    //         return "success";
    //     } else if (lastFetchStatus == kLastFetchStatusFailure) {
    //         return "failure";
    //     } else if (lastFetchStatus == kLastFetchStatusPending) {
    //         return "noFetchYet";
    //     } else {
    //         return "failure";
    //     }
    //     return "success";
    // }

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
        auto firebase_app = App::GetInstance(app_name.c_str());
        auto remote_config = RemoteConfig::GetInstance(firebase_app);

        auto configSettings = remote_config->GetConfigSettings();
        auto fetchTimeout = static_cast<int64_t>(configSettings.fetch_timeout_in_milliseconds);
        auto minFetchTimeout = static_cast<int64_t>(configSettings.minimum_fetch_interval_in_milliseconds);

        auto configInfo = remote_config->GetInfo();
        auto lastFetch = static_cast<int64_t>(configInfo.fetch_time);
        auto lastFetchStatus = configInfo.last_fetch_status;
        auto lastFetchStatusMapped = map_last_fetch_status(lastFetchStatus);
        //
        flutter::EncodableMap values;

        values.insert({ EncodableValue("fetchTimeout"), EncodableValue(fetchTimeout) });
        values.insert({ EncodableValue("minimumFetchInterval"), EncodableValue(minFetchTimeout) });
        values.insert({ EncodableValue("lastFetchTime"), EncodableValue(lastFetch) });
        values.insert({ EncodableValue("lastFetchStatus"), EncodableValue(lastFetchStatusMapped.c_str()) });
        //
        auto to_return = ErrorOr<std::optional<flutter::EncodableMap>>(std::make_optional(values));

        result(to_return);
        //result(ErrorOr<std::optional<flutter::EncodableMap>>(flutter::Error("not impl")));
    }
}
