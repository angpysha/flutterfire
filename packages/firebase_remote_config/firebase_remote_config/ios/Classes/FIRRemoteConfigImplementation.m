//
//  FIRRemoteConfigImplementation.m
//  firebase_remote_config
//
//  Created by Andrii on 18.05.2024.
//

#import "FIRRemoteConfigImplementation.h"
#import "Firebase/Firebase.h"
#import "FirebaseRemoteConfig/FirebaseRemoteConfig.h"
#import "Flutter/FlutterCodecs.h"

@implementation FIRRemoteConfigImplementation
- (void)ensureInitializedAppName:(NSString *)appName completion:(void (^)(FlutterError *_Nullable))completion {
    FIRApp* firebaseApp = [FIRApp defaultApp];
    
    if (firebaseApp == nil) {
        completion(nil);
        return;
    }
    
    id remoteConfig = [FIRRemoteConfig remoteConfigWithApp:firebaseApp];
    
    [remoteConfig ensureInitializedWithCompletionHandler:^(NSError * _Nullable error) {
        completion(nil);
//        if (error) {
//            completion([FlutterError] );
//        } else {
//            completion(nil);
//        }
    }];
    
}

- (void)activateAppName:(NSString *)appName completion:(void (^)(NSNumber *_Nullable, FlutterError *_Nullable))completion {
    FIRApp* firebaseApp = [FIRApp defaultApp];
    
    if (firebaseApp == nil) {
        FlutterError *error = [FlutterError errorWithCode:@"1" message:@"Cannot create firevase app instance" details:nil];
        completion(0, error);
        return;
    }
    
    FIRRemoteConfig* remoteConfig = [FIRRemoteConfig remoteConfigWithApp:firebaseApp];

    [remoteConfig activateWithCompletion:^(BOOL changed, NSError * _Nullable error) {
        NSNumber *res = [NSNumber numberWithBool:changed];
        completion(res, nil);
    }];
}

- (void) fetchAppName:(NSString *)appName completion:(void (^)(FlutterError *_Nullable))completion {
    FIRApp* firebaseApp = [FIRApp defaultApp];
    
    if (firebaseApp == nil) {
        FlutterError *error = [FlutterError errorWithCode:@"1" message:@"Cannot create firevase app instance" details:nil];
        completion(error);
        return;
    }
    
    FIRRemoteConfig* remoteConfig = [FIRRemoteConfig remoteConfigWithApp:firebaseApp];
    
    [remoteConfig fetchWithCompletionHandler:^(FIRRemoteConfigFetchStatus status, NSError * _Nullable error) {
        completion(nil);
    }];
}

- (void)fetchAndActivateAppName:(NSString *)appName completion:(void (^)(NSNumber *_Nullable, FlutterError *_Nullable))completion {
    FIRApp* firebaseApp = [FIRApp defaultApp];
    
    if (firebaseApp == nil) {
        FlutterError *error = [FlutterError errorWithCode:@"1" message:@"Cannot create firevase app instance" details:nil];
        completion(0, error);
        return;
    }
    
    FIRRemoteConfig* remoteConfig = [FIRRemoteConfig remoteConfigWithApp:firebaseApp];
    
    [remoteConfig fetchAndActivateWithCompletionHandler:^(FIRRemoteConfigFetchAndActivateStatus status, NSError * _Nullable error) {
            NSNumber* numberStatus = [NSNumber numberWithBool:status != FIRRemoteConfigFetchAndActivateStatusError];
            
            completion(numberStatus, nil);
        }];
}

- (void)setConfigSettingsAppName:(NSString *)appName fetchTimeout:(NSInteger)fetchTimeout minimumFetchInterval:(NSInteger)minimumFetchInterval completion:(void (^)(FlutterError *_Nullable))completion {
    FIRApp* firebaseApp = [FIRApp defaultApp];
    
    if (firebaseApp == nil) {
        FlutterError *error = [FlutterError errorWithCode:@"1" message:@"Cannot create firevase app instance" details:nil];
        completion(error);
        return;
    }
    
    FIRRemoteConfig* remoteConfig = [FIRRemoteConfig remoteConfigWithApp:firebaseApp];
    
    FIRRemoteConfigSettings* settings = [[FIRRemoteConfigSettings alloc] init];
    
    settings.minimumFetchInterval = minimumFetchInterval;
    settings.fetchTimeout = fetchTimeout;
    
    [remoteConfig setConfigSettings:settings];
    
    completion(nil);
}

- (void)setDefaultsAppName:(NSString *)appName defaultParameters:(NSDictionary<NSString *, id> *)defaultParameters completion:(void (^)(FlutterError *_Nullable))completion {
    FIRApp* firebaseApp = [FIRApp defaultApp];
    
    if (firebaseApp == nil) {
        FlutterError *error = [FlutterError errorWithCode:@"1" message:@"Cannot create firevase app instance" details:nil];
        completion(error);
        return;
    }
    
    FIRRemoteConfig* remoteConfig = [FIRRemoteConfig remoteConfigWithApp:firebaseApp];
    
    [remoteConfig setDefaults:defaultParameters];
    completion(nil);
}

- (void)getAllAppName:(NSString *)appName completion:(void (^)(NSDictionary<id, id> *_Nullable, FlutterError *_Nullable))completion {
    FIRApp* firebaseApp = [FIRApp defaultApp];
    
    if (firebaseApp == nil) {
        FlutterError *error = [FlutterError errorWithCode:@"1" message:@"Cannot create firevase app instance" details:nil];
        completion(nil, error);
        return;
    }
    
    FIRRemoteConfig* remoteConfig = [FIRRemoteConfig remoteConfigWithApp:firebaseApp];
    
    NSDictionary<id,id>* parametes = [self getAllParametersForInstance:remoteConfig];
    
    completion(parametes, nil);
}

- (void)getPropertiesAppName:(NSString *)appName completion:(void (^)(NSDictionary<id, id> *_Nullable, FlutterError *_Nullable))completion {
    FIRApp* firebaseApp = [FIRApp defaultApp];
    
    if (firebaseApp == nil) {
        FlutterError *error = [FlutterError errorWithCode:@"1" message:@"Cannot create firevase app instance" details:nil];
        completion(nil, error);
        return;
    }
    
    FIRRemoteConfig* remoteConfig = [FIRRemoteConfig remoteConfigWithApp:firebaseApp];
    
    NSDictionary* properties = [self configPropertiesForInstance:remoteConfig];
    
    completion(properties, nil);
}

- (NSDictionary *_Nonnull)configPropertiesForInstance:(FIRRemoteConfig *)remoteConfig {
  NSNumber *fetchTimeout = @([[remoteConfig configSettings] fetchTimeout]);
  NSNumber *minimumFetchInterval = @([[remoteConfig configSettings] minimumFetchInterval]);
  NSNumber *lastFetchMillis = @([[remoteConfig lastFetchTime] timeIntervalSince1970] * 1000);

  NSMutableDictionary *configProperties = [[NSMutableDictionary alloc] init];
  [configProperties setValue:@([fetchTimeout longValue]) forKey:@"fetchTimeout"];
  [configProperties setValue:@([minimumFetchInterval longValue]) forKey:@"minimumFetchInterval"];
  [configProperties setValue:@([lastFetchMillis longValue]) forKey:@"lastFetchTime"];
  [configProperties setValue:[self mapLastFetchStatus:[remoteConfig lastFetchStatus]]
                      forKey:@"lastFetchStatus"];
  return configProperties;
}

- (NSDictionary *)getAllParametersForInstance:(FIRRemoteConfig *)remoteConfig {
  NSMutableSet *keySet = [[NSMutableSet alloc] init];
  [keySet addObjectsFromArray:[remoteConfig allKeysFromSource:FIRRemoteConfigSourceStatic]];
  [keySet addObjectsFromArray:[remoteConfig allKeysFromSource:FIRRemoteConfigSourceDefault]];
  [keySet addObjectsFromArray:[remoteConfig allKeysFromSource:FIRRemoteConfigSourceRemote]];

  NSMutableDictionary *parameters = [[NSMutableDictionary alloc] init];
  for (NSString *key in keySet) {
    parameters[key] = [self createRemoteConfigValueDict:[remoteConfig configValueForKey:key]];
  }
  return parameters;
}

- (NSMutableDictionary *)createRemoteConfigValueDict:(FIRRemoteConfigValue *)remoteConfigValue {
  NSMutableDictionary *valueDict = [[NSMutableDictionary alloc] init];
  valueDict[@"value"] = [FlutterStandardTypedData typedDataWithBytes:[remoteConfigValue dataValue]];
  valueDict[@"source"] = [self mapValueSource:[remoteConfigValue source]];
  return valueDict;
}

- (NSString *)mapLastFetchStatus:(FIRRemoteConfigFetchStatus)status {
  if (status == FIRRemoteConfigFetchStatusSuccess) {
    return @"success";
  } else if (status == FIRRemoteConfigFetchStatusFailure) {
    return @"failure";
  } else if (status == FIRRemoteConfigFetchStatusThrottled) {
    return @"throttled";
  } else if (status == FIRRemoteConfigFetchStatusNoFetchYet) {
    return @"noFetchYet";
  } else {
    return @"failure";
  }
}

- (NSString *)mapValueSource:(FIRRemoteConfigSource)source {
  if (source == FIRRemoteConfigSourceStatic) {
    return @"static";
  } else if (source == FIRRemoteConfigSourceDefault) {
    return @"default";
  } else if (source == FIRRemoteConfigSourceRemote) {
    return @"remote";
  } else {
    return @"static";
  }
}
@end
