package io.flutter.plugins.firebase.firebaseremoteconfig;

import androidx.annotation.NonNull;

import com.google.firebase.FirebaseApp;
import com.google.firebase.remoteconfig.FirebaseRemoteConfig;
import com.google.firebase.remoteconfig.FirebaseRemoteConfigSettings;
import com.google.firebase.remoteconfig.FirebaseRemoteConfigValue;

import io.flutter.Log;
import io.flutter.plugins.firebase.firebaseremoteconfig.GeneratedAndroidFirebaseRemoteConfig.VoidResult;
import java.util.HashMap;
import java.util.Map;
import java.util.concurrent.Executor;

public class RemoteConfigHostApiImpl implements GeneratedAndroidFirebaseRemoteConfig.RemoteConfigHostApi {

  @Override
  public void ensureInitialized(String appName, VoidResult result) {
    FirebaseApp app = FirebaseApp.getInstance(appName);
    FirebaseRemoteConfig remoteConfig = FirebaseRemoteConfig.getInstance(app);
//    remoteConfig.ensureInitialized().continueWith((Executor) task -> {
//      result.success();
//      return null;
//    });
    remoteConfig.ensureInitialized().addOnCompleteListener(task -> {
      result.success();
    });
  }

  @Override
  public void activate(String appName, GeneratedAndroidFirebaseRemoteConfig.Result<Boolean> result) {
    FirebaseApp app = FirebaseApp.getInstance(appName);
    FirebaseRemoteConfig remoteConfig = FirebaseRemoteConfig.getInstance(app);
    remoteConfig.activate().addOnCompleteListener(task -> {
      result.success(task.getResult());
    });
  }

  @Override
  public void fetch(String appName, VoidResult result) {
    FirebaseApp app = FirebaseApp.getInstance(appName);
    FirebaseRemoteConfig remoteConfig = FirebaseRemoteConfig.getInstance(app);

    remoteConfig.fetch().addOnCompleteListener(task -> {
      result.success();
    });
  }

  @Override
  public void fetchAndActivate(String appName, GeneratedAndroidFirebaseRemoteConfig.Result<Boolean> result) {
    FirebaseApp app = FirebaseApp.getInstance(appName);
    FirebaseRemoteConfig remoteConfig = FirebaseRemoteConfig.getInstance(app);
    remoteConfig.fetchAndActivate().addOnCompleteListener(task -> {
      result.success(task.getResult());
    });
  }

  @Override
  public void setConfigSettings(@NonNull String appName, @NonNull Long fetchTimeout, @NonNull Long minimumFetchInterval, @NonNull VoidResult result) {
    FirebaseApp app = FirebaseApp.getInstance(appName);
    FirebaseRemoteConfig remoteConfig = FirebaseRemoteConfig.getInstance(app);
    FirebaseRemoteConfigSettings settings = new FirebaseRemoteConfigSettings.Builder()
      .setFetchTimeoutInSeconds(fetchTimeout)
      .setMinimumFetchIntervalInSeconds(minimumFetchInterval)
      .build();

    remoteConfig.setConfigSettingsAsync(settings).addOnCompleteListener(task -> {
      result.success();
    });
  }

  @Override
  public void setDefaults(String appName, Map<String, Object> defaultParameters, VoidResult result) {
    FirebaseApp app = FirebaseApp.getInstance(appName);
    FirebaseRemoteConfig remoteConfig = FirebaseRemoteConfig.getInstance(app);
    remoteConfig.setDefaultsAsync(defaultParameters).addOnCompleteListener(task -> {
      result.success();
    });
  }

  @Override
  public void getAll(String appName, GeneratedAndroidFirebaseRemoteConfig.NullableResult<Map<Object, Object>> result) {
    FirebaseApp app = FirebaseApp.getInstance(appName);
    FirebaseRemoteConfig remoteConfig = FirebaseRemoteConfig.getInstance(app);
    Map<String, FirebaseRemoteConfigValue> items = remoteConfig.getAll();
    Map<Object, Object> castedItem = new HashMap<>(items);
    result.success(castedItem);
  }

  @Override
  public void getProperties(String appName, GeneratedAndroidFirebaseRemoteConfig.NullableResult<Map<Object, Object>> result) {
    FirebaseApp app = FirebaseApp.getInstance(appName);
    FirebaseRemoteConfig remoteConfig = FirebaseRemoteConfig.getInstance(app);
    Map<Object, Object> configProperties = new HashMap<>();
    configProperties.put("fetchTimeout", remoteConfig.getInfo().getConfigSettings().getFetchTimeoutInSeconds());
    configProperties.put("minimumFetchInterval", remoteConfig.getInfo().getConfigSettings().getMinimumFetchIntervalInSeconds());
    configProperties.put("lastFetchTime", remoteConfig.getInfo().getFetchTimeMillis());
    configProperties.put("lastFetchStatus", mapLastFetchStatus(remoteConfig.getInfo().getLastFetchStatus()));

    Log.d(FirebaseRemoteConfigPlugin.TAG, "Sending fetchTimeout: " + configProperties.get("fetchTimeout"));

    result.success(configProperties);
  }

  @Override
  public void setConfigSettings(String appName, long fetchTimeout, long minimumFetchInterval, VoidResult result) {
    FirebaseApp app = FirebaseApp.getInstance(appName);
    FirebaseRemoteConfig remoteConfig = FirebaseRemoteConfig.getInstance(app);
    FirebaseRemoteConfigSettings settings = new FirebaseRemoteConfigSettings.Builder()
      .setFetchTimeoutInSeconds(fetchTimeout)
      .setMinimumFetchIntervalInSeconds(minimumFetchInterval)
      .build();

    remoteConfig.setConfigSettingsAsync(settings).addOnCompleteListener(task -> {
      result.success();
    });
  }

  private String mapLastFetchStatus(int status) {
    switch (status) {
      case FirebaseRemoteConfig.LAST_FETCH_STATUS_SUCCESS:
        return "success";
      case FirebaseRemoteConfig.LAST_FETCH_STATUS_THROTTLED:
        return "throttled";
      case FirebaseRemoteConfig.LAST_FETCH_STATUS_NO_FETCH_YET:
        return "noFetchYet";
      case FirebaseRemoteConfig.LAST_FETCH_STATUS_FAILURE:
        return "failure";
      default:
        return "failure";
    }
  }
}

