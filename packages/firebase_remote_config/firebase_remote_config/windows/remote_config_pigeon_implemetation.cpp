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

        ConfigSettings config_setting{static_cast<uint64_t>(fetch_timeout), static_cast<uint64_t>(minimum_fetch_interval)};

        remote_config->SetConfigSettings(config_setting);
    }

    void remote_config_pigeon_implemetation::SetDefaults(
        const std::string& app_name,
        const flutter::EncodableMap& default_parameters,
        std::function<void(std::optional<FlutterError> reply)> result)
    {
        auto firebase_app = App::GetInstance(app_name.c_str());
        auto remote_config = RemoteConfig::GetInstance(firebase_app);

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

    void remote_config_pigeon_implemetation::GetAll(
        const std::string& app_name,
        std::function<void(ErrorOr<std::optional<flutter::EncodableMap>> reply)
        > result)
    {
        // auto firebase_app = App::GetInstance(app_name.c_str());
        // auto remote_config = RemoteConfig::GetInstance(firebase_app);
        //
        // auto get_all = remote_config->GetAll();
        //
        // auto all_mapped = mapParameters(get_all);
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


    void remote_config_pigeon_implemetation::GetProperties(
        const std::string& app_name,
        std::function<void(ErrorOr<std::optional<flutter::EncodableMap>> reply)> result)
    {
//        auto firebase_app = App::GetInstance(app_name.c_str());
//        auto remote_config = RemoteConfig::GetInstance(firebase_app);
//
//        auto configSettings = remote_config->GetConfigSettings();
//        auto fetchTimeout = static_cast<int64_t>(configSettings.fetch_timeout_in_milliseconds);
//        auto minFetchTimeout = static_cast<int64_t>(configSettings.minimum_fetch_interval_in_milliseconds);
//
//        auto configInfo = remote_config->GetInfo();
//        auto lastFetch = static_cast<int64_t>(configInfo.fetch_time);
//        auto lastFetchStatus = configInfo.last_fetch_status;
//        auto lastFetchStatusMapped = mapLastFetchStatus(lastFetchStatus);
//
//        flutter::EncodableMap values;
//
//        values.insert({ EncodableValue("fetchTimeout"), EncodableValue(fetchTimeout) });
//        values.insert({ EncodableValue("minimumFetchInterval"), EncodableValue(minFetchTimeout) });
//        values.insert({ EncodableValue("lastFetchTime"), EncodableValue(lastFetch) });
//        values.insert({ EncodableValue("lastFetchStatus"), EncodableValue(lastFetchStatusMapped.c_str()) });
//
//        auto to_return = ErrorOr<std::optional<flutter::EncodableMap>>(std::make_optional(values));

       // result(ErrorOr<std::optional<flutter::EncodableMap>>(flutter::Error("not impl")));
    }
}
