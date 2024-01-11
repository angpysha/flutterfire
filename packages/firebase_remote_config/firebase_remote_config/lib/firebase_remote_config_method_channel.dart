import 'package:flutter/foundation.dart';
import 'package:flutter/services.dart';

import 'firebase_remote_config_platform_interface.dart';

/// An implementation of [FirebaseRemoteConfigPlatform] that uses method channels.
class MethodChannelFirebaseRemoteConfig extends FirebaseRemoteConfigPlatform {
  /// The method channel used to interact with the native platform.
  @visibleForTesting
  final methodChannel = const MethodChannel('firebase_remote_config');

  @override
  Future<String?> getPlatformVersion() async {
    final version = await methodChannel.invokeMethod<String>('getPlatformVersion');
    return version;
  }
}
