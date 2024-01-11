import 'package:plugin_platform_interface/plugin_platform_interface.dart';

import 'firebase_remote_config_method_channel.dart';

abstract class FirebaseRemoteConfigPlatform extends PlatformInterface {
  /// Constructs a FirebaseRemoteConfigPlatform.
  FirebaseRemoteConfigPlatform() : super(token: _token);

  static final Object _token = Object();

  static FirebaseRemoteConfigPlatform _instance = MethodChannelFirebaseRemoteConfig();

  /// The default instance of [FirebaseRemoteConfigPlatform] to use.
  ///
  /// Defaults to [MethodChannelFirebaseRemoteConfig].
  static FirebaseRemoteConfigPlatform get instance => _instance;

  /// Platform-specific implementations should set this with their own
  /// platform-specific class that extends [FirebaseRemoteConfigPlatform] when
  /// they register themselves.
  static set instance(FirebaseRemoteConfigPlatform instance) {
    PlatformInterface.verifyToken(instance, _token);
    _instance = instance;
  }

  Future<String?> getPlatformVersion() {
    throw UnimplementedError('platformVersion() has not been implemented.');
  }
}
