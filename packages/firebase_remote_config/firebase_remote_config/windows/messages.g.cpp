// Autogenerated from Pigeon (v16.0.0), do not edit directly.
// See also: https://pub.dev/packages/pigeon

#undef _HAS_EXCEPTIONS

#include "messages.g.h"

#include <flutter/basic_message_channel.h>
#include <flutter/binary_messenger.h>
#include <flutter/encodable_value.h>
#include <flutter/standard_message_codec.h>

#include <map>
#include <optional>
#include <string>

namespace firebase_remote_config_windows {
using flutter::BasicMessageChannel;
using flutter::CustomEncodableValue;
using flutter::EncodableList;
using flutter::EncodableMap;
using flutter::EncodableValue;

FlutterError CreateConnectionError(const std::string channel_name) {
    return FlutterError(
        "channel-error",
        "Unable to establish connection on channel: '" + channel_name + "'.",
        EncodableValue(""));
}

/// The codec used by RemoteConfigHostApi.
const flutter::StandardMessageCodec& RemoteConfigHostApi::GetCodec() {
  return flutter::StandardMessageCodec::GetInstance(&flutter::StandardCodecSerializer::GetInstance());
}

// Sets up an instance of `RemoteConfigHostApi` to handle messages through the `binary_messenger`.
void RemoteConfigHostApi::SetUp(
  flutter::BinaryMessenger* binary_messenger,
  RemoteConfigHostApi* api) {
  {
    auto channel = std::make_unique<BasicMessageChannel<>>(binary_messenger, "dev.flutter.pigeon.firebase_remote_config_platform_interface.RemoteConfigHostApi.ensureInitialized", &GetCodec());
    if (api != nullptr) {
      channel->SetMessageHandler([api](const EncodableValue& message, const flutter::MessageReply<EncodableValue>& reply) {
        try {
          const auto& args = std::get<EncodableList>(message);
          const auto& encodable_app_name_arg = args.at(0);
          if (encodable_app_name_arg.IsNull()) {
            reply(WrapError("app_name_arg unexpectedly null."));
            return;
          }
          const auto& app_name_arg = std::get<std::string>(encodable_app_name_arg);
          api->EnsureInitialized(app_name_arg, [reply](std::optional<FlutterError>&& output) {
            if (output.has_value()) {
              reply(WrapError(output.value()));
              return;
            }
            EncodableList wrapped;
            wrapped.push_back(EncodableValue());
            reply(EncodableValue(std::move(wrapped)));
          });
        } catch (const std::exception& exception) {
          reply(WrapError(exception.what()));
        }
      });
    } else {
      channel->SetMessageHandler(nullptr);
    }
  }
  {
    auto channel = std::make_unique<BasicMessageChannel<>>(binary_messenger, "dev.flutter.pigeon.firebase_remote_config_platform_interface.RemoteConfigHostApi.activate", &GetCodec());
    if (api != nullptr) {
      channel->SetMessageHandler([api](const EncodableValue& message, const flutter::MessageReply<EncodableValue>& reply) {
        try {
          const auto& args = std::get<EncodableList>(message);
          const auto& encodable_app_name_arg = args.at(0);
          if (encodable_app_name_arg.IsNull()) {
            reply(WrapError("app_name_arg unexpectedly null."));
            return;
          }
          const auto& app_name_arg = std::get<std::string>(encodable_app_name_arg);
          api->Activate(app_name_arg, [reply](ErrorOr<bool>&& output) {
            if (output.has_error()) {
              reply(WrapError(output.error()));
              return;
            }
            EncodableList wrapped;
            wrapped.push_back(EncodableValue(std::move(output).TakeValue()));
            reply(EncodableValue(std::move(wrapped)));
          });
        } catch (const std::exception& exception) {
          reply(WrapError(exception.what()));
        }
      });
    } else {
      channel->SetMessageHandler(nullptr);
    }
  }
  {
    auto channel = std::make_unique<BasicMessageChannel<>>(binary_messenger, "dev.flutter.pigeon.firebase_remote_config_platform_interface.RemoteConfigHostApi.fetch", &GetCodec());
    if (api != nullptr) {
      channel->SetMessageHandler([api](const EncodableValue& message, const flutter::MessageReply<EncodableValue>& reply) {
        try {
          const auto& args = std::get<EncodableList>(message);
          const auto& encodable_app_name_arg = args.at(0);
          if (encodable_app_name_arg.IsNull()) {
            reply(WrapError("app_name_arg unexpectedly null."));
            return;
          }
          const auto& app_name_arg = std::get<std::string>(encodable_app_name_arg);
          api->Fetch(app_name_arg, [reply](std::optional<FlutterError>&& output) {
            if (output.has_value()) {
              reply(WrapError(output.value()));
              return;
            }
            EncodableList wrapped;
            wrapped.push_back(EncodableValue());
            reply(EncodableValue(std::move(wrapped)));
          });
        } catch (const std::exception& exception) {
          reply(WrapError(exception.what()));
        }
      });
    } else {
      channel->SetMessageHandler(nullptr);
    }
  }
  {
    auto channel = std::make_unique<BasicMessageChannel<>>(binary_messenger, "dev.flutter.pigeon.firebase_remote_config_platform_interface.RemoteConfigHostApi.fetchAndActivate", &GetCodec());
    if (api != nullptr) {
      channel->SetMessageHandler([api](const EncodableValue& message, const flutter::MessageReply<EncodableValue>& reply) {
        try {
          const auto& args = std::get<EncodableList>(message);
          const auto& encodable_app_name_arg = args.at(0);
          if (encodable_app_name_arg.IsNull()) {
            reply(WrapError("app_name_arg unexpectedly null."));
            return;
          }
          const auto& app_name_arg = std::get<std::string>(encodable_app_name_arg);
          api->FetchAndActivate(app_name_arg, [reply](ErrorOr<bool>&& output) {
            if (output.has_error()) {
              reply(WrapError(output.error()));
              return;
            }
            EncodableList wrapped;
            wrapped.push_back(EncodableValue(std::move(output).TakeValue()));
            reply(EncodableValue(std::move(wrapped)));
          });
        } catch (const std::exception& exception) {
          reply(WrapError(exception.what()));
        }
      });
    } else {
      channel->SetMessageHandler(nullptr);
    }
  }
  {
    auto channel = std::make_unique<BasicMessageChannel<>>(binary_messenger, "dev.flutter.pigeon.firebase_remote_config_platform_interface.RemoteConfigHostApi.setConfigSettings", &GetCodec());
    if (api != nullptr) {
      channel->SetMessageHandler([api](const EncodableValue& message, const flutter::MessageReply<EncodableValue>& reply) {
        try {
          const auto& args = std::get<EncodableList>(message);
          const auto& encodable_app_name_arg = args.at(0);
          if (encodable_app_name_arg.IsNull()) {
            reply(WrapError("app_name_arg unexpectedly null."));
            return;
          }
          const auto& app_name_arg = std::get<std::string>(encodable_app_name_arg);
          const auto& encodable_fetch_timeout_arg = args.at(1);
          if (encodable_fetch_timeout_arg.IsNull()) {
            reply(WrapError("fetch_timeout_arg unexpectedly null."));
            return;
          }
          const int64_t fetch_timeout_arg = encodable_fetch_timeout_arg.LongValue();
          const auto& encodable_minimum_fetch_interval_arg = args.at(2);
          if (encodable_minimum_fetch_interval_arg.IsNull()) {
            reply(WrapError("minimum_fetch_interval_arg unexpectedly null."));
            return;
          }
          const int64_t minimum_fetch_interval_arg = encodable_minimum_fetch_interval_arg.LongValue();
          api->SetConfigSettings(app_name_arg, fetch_timeout_arg, minimum_fetch_interval_arg, [reply](std::optional<FlutterError>&& output) {
            if (output.has_value()) {
              reply(WrapError(output.value()));
              return;
            }
            EncodableList wrapped;
            wrapped.push_back(EncodableValue());
            reply(EncodableValue(std::move(wrapped)));
          });
        } catch (const std::exception& exception) {
          reply(WrapError(exception.what()));
        }
      });
    } else {
      channel->SetMessageHandler(nullptr);
    }
  }
  {
    auto channel = std::make_unique<BasicMessageChannel<>>(binary_messenger, "dev.flutter.pigeon.firebase_remote_config_platform_interface.RemoteConfigHostApi.setDefaults", &GetCodec());
    if (api != nullptr) {
      channel->SetMessageHandler([api](const EncodableValue& message, const flutter::MessageReply<EncodableValue>& reply) {
        try {
          const auto& args = std::get<EncodableList>(message);
          const auto& encodable_app_name_arg = args.at(0);
          if (encodable_app_name_arg.IsNull()) {
            reply(WrapError("app_name_arg unexpectedly null."));
            return;
          }
          const auto& app_name_arg = std::get<std::string>(encodable_app_name_arg);
          const auto& encodable_default_parameters_arg = args.at(1);
          if (encodable_default_parameters_arg.IsNull()) {
            reply(WrapError("default_parameters_arg unexpectedly null."));
            return;
          }
          const auto& default_parameters_arg = std::get<EncodableMap>(encodable_default_parameters_arg);
          api->SetDefaults(app_name_arg, default_parameters_arg, [reply](std::optional<FlutterError>&& output) {
            if (output.has_value()) {
              reply(WrapError(output.value()));
              return;
            }
            EncodableList wrapped;
            wrapped.push_back(EncodableValue());
            reply(EncodableValue(std::move(wrapped)));
          });
        } catch (const std::exception& exception) {
          reply(WrapError(exception.what()));
        }
      });
    } else {
      channel->SetMessageHandler(nullptr);
    }
  }
  {
    auto channel = std::make_unique<BasicMessageChannel<>>(binary_messenger, "dev.flutter.pigeon.firebase_remote_config_platform_interface.RemoteConfigHostApi.getAll", &GetCodec());
    if (api != nullptr) {
      channel->SetMessageHandler([api](const EncodableValue& message, const flutter::MessageReply<EncodableValue>& reply) {
        try {
          const auto& args = std::get<EncodableList>(message);
          const auto& encodable_app_name_arg = args.at(0);
          if (encodable_app_name_arg.IsNull()) {
            reply(WrapError("app_name_arg unexpectedly null."));
            return;
          }
          const auto& app_name_arg = std::get<std::string>(encodable_app_name_arg);
          api->GetAll(app_name_arg, [reply](ErrorOr<std::optional<EncodableMap>>&& output) {
            if (output.has_error()) {
              reply(WrapError(output.error()));
              return;
            }
            EncodableList wrapped;
            auto output_optional = std::move(output).TakeValue();
            if (output_optional) {
              wrapped.push_back(EncodableValue(std::move(output_optional).value()));
            } else {
              wrapped.push_back(EncodableValue());
            }
            reply(EncodableValue(std::move(wrapped)));
          });
        } catch (const std::exception& exception) {
          reply(WrapError(exception.what()));
        }
      });
    } else {
      channel->SetMessageHandler(nullptr);
    }
  }
  {
    auto channel = std::make_unique<BasicMessageChannel<>>(binary_messenger, "dev.flutter.pigeon.firebase_remote_config_platform_interface.RemoteConfigHostApi.getProperties", &GetCodec());
    if (api != nullptr) {
      channel->SetMessageHandler([api](const EncodableValue& message, const flutter::MessageReply<EncodableValue>& reply) {
        try {
          const auto& args = std::get<EncodableList>(message);
          const auto& encodable_app_name_arg = args.at(0);
          if (encodable_app_name_arg.IsNull()) {
            reply(WrapError("app_name_arg unexpectedly null."));
            return;
          }
          const auto& app_name_arg = std::get<std::string>(encodable_app_name_arg);
          api->GetProperties(app_name_arg, [reply](ErrorOr<std::optional<EncodableMap>>&& output) {
            if (output.has_error()) {
              reply(WrapError(output.error()));
              return;
            }
            EncodableList wrapped;
            auto output_optional = std::move(output).TakeValue();
            if (output_optional) {
              wrapped.push_back(EncodableValue(std::move(output_optional).value()));
            } else {
              wrapped.push_back(EncodableValue());
            }
            reply(EncodableValue(std::move(wrapped)));
          });
        } catch (const std::exception& exception) {
          reply(WrapError(exception.what()));
        }
      });
    } else {
      channel->SetMessageHandler(nullptr);
    }
  }
}

EncodableValue RemoteConfigHostApi::WrapError(std::string_view error_message) {
  return EncodableValue(EncodableList{
    EncodableValue(std::string(error_message)),
    EncodableValue("Error"),
    EncodableValue()
  });
}

EncodableValue RemoteConfigHostApi::WrapError(const FlutterError& error) {
  return EncodableValue(EncodableList{
    EncodableValue(error.code()),
    EncodableValue(error.message()),
    error.details()
  });
}

}  // namespace firebase_remote_config_windows