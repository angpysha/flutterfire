//
// Created by Andrii on 15.01.2024.
//

#ifndef TODO_POINTS_REMOTE_CONFIG_PIGEON_IMPLEMETATION_H
#define TODO_POINTS_REMOTE_CONFIG_PIGEON_IMPLEMETATION_H

#include "messages.g.h"

namespace firebase_remote_config_windows {
    class remote_config_pigeon_implemetation : public RemoteConfigHostApi {
    public:

        remote_config_pigeon_implemetation() {}

        virtual ~remote_config_pigeon_implemetation() override {}

        virtual void EnsureInitialized(
                const std::string &app_name,
                std::function<void(std::optional<FlutterError>reply)> result) override;

        virtual void Activate(
                const std::string &app_name,
                std::function<void(ErrorOr<bool> reply)> result) override;

        virtual void Fetch(
                const std::string &app_name,
                std::function<void(std::optional < FlutterError > reply)> result) override;

        virtual void FetchAndActivate(
                const std::string &app_name,
                std::function<void(ErrorOr<bool> reply)> result) override;

        virtual void SetConfigSettings(
                const std::string &app_name,
                int64_t fetch_timeout,
                int64_t minimum_fetch_interval,
                std::function<void(std::optional < FlutterError > reply)> result) override;

        virtual void SetDefaults(
                const std::string &app_name,
                const flutter::EncodableMap &default_parameters,
                std::function<void(std::optional < FlutterError > reply)> result) override;

        virtual void GetAll(
                const std::string &app_name,
                std::function<void(ErrorOr<std::optional < flutter::EncodableMap>> reply)

        > result)
        override;

        virtual void GetProperties(
            const std::string& app_name,
            std::function<void(ErrorOr<std::optional<flutter::EncodableMap>> reply)> result) override;
    };
}


#endif //TODO_POINTS_REMOTE_CONFIG_PIGEON_IMPLEMETATION_H
