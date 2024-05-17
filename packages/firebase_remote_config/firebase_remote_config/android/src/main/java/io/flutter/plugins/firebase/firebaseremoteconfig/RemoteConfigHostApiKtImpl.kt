//package io.flutter.plugins.firebase.firebaseremoteconfig
//
//import com.google.firebase.FirebaseApp
//import com.google.firebase.remoteconfig.FirebaseRemoteConfig
//import com.google.firebase.remoteconfig.FirebaseRemoteConfigSettings
//import com.google.firebase.remoteconfig.FirebaseRemoteConfigValue
//import io.flutter.Log
//import io.flutter.plugins.firebase.firebaseremoteconfig.GeneratedAndroidFirebaseRemoteConfig.VoidResult
//
//class RemoteConfigHostApiKtImpl : GeneratedAndroidFirebaseRemoteConfig.RemoteConfigHostApi {
//  override fun ensureInitialized(
//    appName: String,
//    result: VoidResult
//  ) {
//    val app = FirebaseApp.getInstance(appName)
//    val remoteConfig = FirebaseRemoteConfig.getInstance(app)
//    remoteConfig.ensureInitialized().continueWith {
//      result.success()
//    }
//  }
//
//  override fun activate(
//    appName: String,
//    result: GeneratedAndroidFirebaseRemoteConfig.Result<Boolean>
//  ) {
//    val app = FirebaseApp.getInstance(appName)
//    val remoteConfig = FirebaseRemoteConfig.getInstance(app)
//    remoteConfig.activate().continueWith { task ->
//      result.success(task.result)
//    }
//  }
//
//  override fun fetch(appName: String, result: VoidResult) {
//    val app = FirebaseApp.getInstance(appName)
//    val remoteConfig = FirebaseRemoteConfig.getInstance(app)
//
//    remoteConfig.fetch().continueWith { task ->
//      result.success()
//    }
//  }
//
//
//  override fun fetchAndActivate(
//    appName: String,
//    result: GeneratedAndroidFirebaseRemoteConfig.Result<Boolean>
//  ) {
//    val app = FirebaseApp.getInstance(appName)
//    val remoteConfig = FirebaseRemoteConfig.getInstance(app)
//    remoteConfig.fetchAndActivate().continueWith { task ->
//      result.success(task.result)
//    }
//  }
//
//  override fun setDefaults(
//    appName: String,
//    defaultParameters: MutableMap<String, Any>,
//    result: VoidResult
//  ) {
//    val app = FirebaseApp.getInstance(appName)
//    val remoteConfig = FirebaseRemoteConfig.getInstance(app)
//    remoteConfig.setDefaultsAsync(defaultParameters).continueWith { task ->
//      result.success()
//    }
//  }
//
//  override fun getAll(
//    appName: String,
//    result: GeneratedAndroidFirebaseRemoteConfig.NullableResult<MutableMap<Any, Any>>
//  ) {
//    val app = FirebaseApp.getInstance(appName)
//    val remoteConfig = FirebaseRemoteConfig.getInstance(app)
//    val items = remoteConfig.all
//    val castedItem = parseParameters(items).toMutableMap()
//    result.success(castedItem)
//  }
//
//  override fun getProperties(
//    appName: String,
//    result: GeneratedAndroidFirebaseRemoteConfig.NullableResult<MutableMap<Any, Any>>
//  ) {
//    val app = FirebaseApp.getInstance(appName)
//    val remoteConfig = FirebaseRemoteConfig.getInstance(app)
//    val configProperties: MutableMap<Any, Any> = HashMap()
//    configProperties["fetchTimeout"] = remoteConfig.info.configSettings.fetchTimeoutInSeconds
//    configProperties["minimumFetchInterval"] =
//      remoteConfig.info.configSettings.minimumFetchIntervalInSeconds
//    configProperties["lastFetchTime"] = remoteConfig.info.fetchTimeMillis
//    configProperties["lastFetchStatus"] = mapLastFetchStatus(remoteConfig.info.lastFetchStatus)
//    Log.d(
//      FirebaseRemoteConfigPlugin.TAG,
//      "Sending fetchTimeout: " + configProperties["fetchTimeout"]
//    )
//
//    result.success(configProperties)
//  }
//
//  override fun setConfigSettings(
//    appName: String,
//    fetchTimeout: Long,
//    minimumFetchInterval: Long,
//    result: VoidResult
//  ) {
//    val app = FirebaseApp.getInstance(appName)
//    val remoteConfig = FirebaseRemoteConfig.getInstance(app)
//    val settings = FirebaseRemoteConfigSettings.Builder()
//      .setFetchTimeoutInSeconds(fetchTimeout)
//      .setMinimumFetchIntervalInSeconds(minimumFetchInterval)
//      .build()
//
//    remoteConfig.setConfigSettingsAsync(settings).continueWith { task ->
//      result.success()
//    }
//  }
//
//  private fun mapLastFetchStatus(status: Int): String {
//    return when (status) {
//      FirebaseRemoteConfig.LAST_FETCH_STATUS_SUCCESS -> "success"
//      FirebaseRemoteConfig.LAST_FETCH_STATUS_THROTTLED -> "throttled"
//      FirebaseRemoteConfig.LAST_FETCH_STATUS_NO_FETCH_YET -> "noFetchYet"
//      FirebaseRemoteConfig.LAST_FETCH_STATUS_FAILURE -> "failure"
//      else -> "failure"
//    }
//  }
//
//  private fun parseParameters(parameters: Map<String, FirebaseRemoteConfigValue>): Map<Any, Any> {
//    val parsedParameters: MutableMap<Any, Any> = java.util.HashMap()
//    for (key in parameters.keys) {
//      parsedParameters[key] = createRemoteConfigValueMap(parameters[key]!!)
//    }
//    return parsedParameters
//  }
//
//  private fun createRemoteConfigValueMap(
//    remoteConfigValue: FirebaseRemoteConfigValue
//  ): Map<String, Any> {
//    val valueMap: MutableMap<String, Any> = java.util.HashMap()
//    valueMap["value"] = remoteConfigValue.asByteArray()
//    valueMap["source"] = mapValueSource(remoteConfigValue.source)
//    return valueMap
//  }
//
//  private fun mapValueSource(source: Int): String {
//    return when (source) {
//      FirebaseRemoteConfig.VALUE_SOURCE_DEFAULT -> "default"
//      FirebaseRemoteConfig.VALUE_SOURCE_REMOTE -> "remote"
//      FirebaseRemoteConfig.VALUE_SOURCE_STATIC -> "static"
//      else -> "static"
//    }
//  }
//}
