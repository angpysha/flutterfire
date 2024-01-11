// Copyright 2022, the Chromium project authors.  Please see the AUTHORS file
// for details. All rights reserved. Use of this source code is governed by a
// BSD-style license that can be found in the LICENSE file.

import 'package:pigeon/pigeon.dart';

@ConfigurePigeon(
  PigeonOptions(
    dartOut: 'lib/src/pigeon/messages.pigeon.dart',
    // We export in the lib folder to expose the class to other packages.
    dartTestOut: 'lib/src/pigeon/test_api.dart',
    javaOut:
        '../firebase_remote_config/android/src/main/java/io/flutter/plugins/firebase/firebaseremoteconfig/GeneratedAndroidFirebaseRemoteConfig.java',
    javaOptions: JavaOptions(
      package: 'io.flutter.plugins.firebase.firebaseremoteconfig',
      className: 'GeneratedAndroidFirebaseRemoteConfig',
    ),
    objcHeaderOut: '../firebase_remote_config/ios/Classes/messages.g.h',
    objcSourceOut: '../firebase_remote_config/ios/Classes/messages.g.m',
    cppHeaderOut: '../firebase_remote_config/windows/messages.g.h',
    cppSourceOut: '../firebase_remote_config/windows/messages.g.cpp',
    cppOptions: CppOptions(namespace: 'firebase_remote_config_windows'),
    // copyrightHeader: 'pigeons/copyright.txt',
  ),
)

enum PigeonValueSource {
  /// The value was defined by a static constant.
  valueStatic,

  /// The value was defined by default config.
  valueDefault,

  /// The value was defined by fetched config.
  valueRemote,
}

/// RemoteConfigValue encapsulates the value and source of a Remote Config
/// parameter.
class PigeonRemoteConfigValue {
  /// Wraps a value with metadata and type-safe getters.
  PigeonRemoteConfigValue(this._value, this.source);

  List<int>? _value;

  /// Indicates at which source this value came from.
  final PigeonValueSource source;
}

@HostApi()
abstract class RemoteConfigHostApi {
  @async
  void ensureInitialized(String appName);

  @async
  bool activate(String appName);

  @async
  void fetch(String appName);

  @async
  bool fetchAndActivate(String appName);

  @async
  void setConfigSettings(String appName, int fetchTimeout, int minimumFetchInterval);

  @async
  void setDefaults(String appName, Map<String, Object> defaultParameters);

  @async
  Map<Object, Object>? getAll(String appName);

  @async
  Map<Object, Object>? getProperties(String appName);
}
