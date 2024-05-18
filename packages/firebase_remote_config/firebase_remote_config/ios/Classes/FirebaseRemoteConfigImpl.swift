////
////  FirebaseRemoteConfigImpl.swift
////  firebase_remote_config
////
////  Created by Andrii on 17.05.2024.
////
//
//import Foundation
//import FirebaseRemoteConfig
//
//@objc public class FirebaseRemoteConfigImpl : NSObject, RemoteConfigHostApi {
//    public func ensureInitializedAppName(_ appName: String, completion: @escaping (FlutterError?) -> Void) {
//        guard let firebaseApp = FirebaseApp.app(name: appName) else {
//            completion(FlutterError(code: "firebase_remote_config", message: "Firebase app with name \(appName) not found", details: nil))
//            return
//        }
//        
//        let firebaseRemoteConfig = RemoteConfig.remoteConfig(app: firebaseApp)
//        
//        firebaseRemoteConfig.ensureInitialized { error in
//            completion(nil)
//        }
//    }
//    
//    public func activateAppName(_ appName: String, completion: @escaping (NSNumber?, FlutterError?) -> Void) {
//        guard let firebaseApp = FirebaseApp.app(name: appName) else {
//            completion(0, FlutterError(code: "firebase_remote_config", message: "Firebase app with name \(appName) not found", details: nil))
//            return
//        }
//        
//        let firebaseRemoteConfig = RemoteConfig.remoteConfig(app: firebaseApp)
//        
//        firebaseRemoteConfig.activate { status, error in
//            completion(status ? 1 : 0, nil)
//        }
//    }
//
//    public func fetchAppName(_ appName: String, completion: @escaping (FlutterError?) -> Void) {
//        guard let firebaseApp = FirebaseApp.app(name: appName) else {
//            completion(FlutterError(code: "firebase_remote_config", message: "Firebase app with name \(appName) not found", details: nil))
//            return
//        }
//        
//        let firebaseRemoteConfig = RemoteConfig.remoteConfig(app: firebaseApp)
//        
//        firebaseRemoteConfig.fetch { status, error in
//            completion(nil)
//        }
//    }
//    
//    public func fetchAndActivateAppName(_ appName: String, completion: @escaping (NSNumber?, FlutterError?) -> Void) {
//        guard let firebaseApp = FirebaseApp.app(name: appName) else {
//            completion(0, FlutterError(code: "firebase_remote_config", message: "Firebase app with name \(appName) not found", details: nil))
//            return
//        }
//        
//        let firebaseRemoteConfig = RemoteConfig.remoteConfig(app: firebaseApp)
//        
//        firebaseRemoteConfig.fetchAndActivate { status, error in
//            completion(status != RemoteConfigFetchAndActivateStatus.error  ? 1 : 0, nil)
//        }
//    }
//    
//    public func setConfigSettingsAppName(_ appName: String, fetchTimeout: Int, minimumFetchInterval: Int, completion: @escaping (FlutterError?) -> Void) {
//        guard let firebaseApp = FirebaseApp.app(name: appName) else {
//            completion(FlutterError(code: "firebase_remote_config", message: "Firebase app with name \(appName) not found", details: nil))
//            return
//        }
//        
//        let firebaseRemoteConfig = RemoteConfig.remoteConfig(app: firebaseApp)
//        
//        var settings = RemoteConfigSettings()
//        
//        settings.minimumFetchInterval = TimeInterval(minimumFetchInterval)
//        settings.fetchTimeout = TimeInterval(fetchTimeout)
//        
//        firebaseRemoteConfig.configSettings = settings
//        
//        completion(nil)
//    }
//    
//    public func setDefaultsAppName(_ appName: String, defaultParameters: [String : Any], completion: @escaping (FlutterError?) -> Void) {
//        guard let firebaseApp = FirebaseApp.app(name: appName) else {
//            completion(FlutterError(code: "firebase_remote_config", message: "Firebase app with name \(appName) not found", details: nil))
//            return
//        }
//        
//        let firebaseRemoteConfig = RemoteConfig.remoteConfig(app: firebaseApp)
//    
//        let maped = defaultParameters.map { key, value in
//            return (key, value as! NSObject)
//        }
//        
//        let mapped = Dictionary(uniqueKeysWithValues: maped)
//        
//        firebaseRemoteConfig.setDefaults(mapped)
//    }
//    
//    public func getAllAppName(_ appName: String, completion: @escaping ([AnyHashable : Any]?, FlutterError?) -> Void) {
//        guard let firebaseApp = FirebaseApp.app(name: appName) else {
//            completion(nil, FlutterError(code: "firebase_remote_config", message: "Firebase app with name \(appName) not found", details: nil))
//            return
//        }
//        
//        let firebaseRemoteConfig = RemoteConfig.remoteConfig(app: firebaseApp)
//    
//        let keys = getAllKeys(remoteConfig: firebaseRemoteConfig)
//        
//        completion(keys as? [AnyHashable : Any], nil)
//    }
//    
////    public func allAppName(_ appName: String) async -> ([AnyHashable : Any]?, FlutterError?) {
////
////    }
//    
//    public func getPropertiesAppName(_ appName: String, completion: @escaping ([AnyHashable : Any]?, FlutterError?) -> Void) {
//        
//        guard let firebaseApp = FirebaseApp.app(name: appName) else {
//            completion(nil, FlutterError(code: "firebase_remote_config", message: "Firebase app with name \(appName) not found", details: nil))
//            return
//        }
//        
//        let firebaseRemoteConfig = RemoteConfig.remoteConfig(app: firebaseApp)
//        
//        let keys = getAllKeys(remoteConfig: firebaseRemoteConfig)
//        
//        completion(keys as? [AnyHashable : Any], nil)
//    }
//    
////    public func propertiesAppName(_ appName: String) async -> ([AnyHashable : Any]?, FlutterError?) {
////
////    }
//    
//    private func getAllKeys(remoteConfig: RemoteConfig) -> NSDictionary {
//        let keySet = NSMutableSet()
//        let staticKeys = remoteConfig.allKeys(from: .static)
//        let defaultKeys = remoteConfig.allKeys(from: .default)
//        let remoteKeys = remoteConfig.allKeys(from: .remote)
//        
//        keySet.add(staticKeys)
//        keySet.add(defaultKeys)
//        keySet.add(remoteKeys)
//        
//        var parameters = NSMutableDictionary()
//        
//        for key in keySet {
//            let remoteConfigValue = remoteConfig.configValue(forKey: key as! String)
//            parameters[key] = createRemoteConfigValueDict(remoteConfigValue: remoteConfigValue)
//        }
//        
//        return parameters
////        [keySet addObjectsFromArray:[remoteConfig allKeysFromSource:FIRRemoteConfigSourceStatic]];
////        [keySet addObjectsFromArray:[remoteConfig allKeysFromSource:FIRRemoteConfigSourceDefault]];
////        [keySet addObjectsFromArray:[remoteConfig allKeysFromSource:FIRRemoteConfigSourceRemote]];
////
////        NSMutableDictionary *parameters = [[NSMutableDictionary alloc] init];
////        for (NSString *key in keySet) {
////          parameters[key] = [self createRemoteConfigValueDict:[remoteConfig configValueForKey:key]];
////        }
////        return parameters;
//    }
//    
//    private func createRemoteConfigValueDict(remoteConfigValue : RemoteConfigValue) -> NSMutableDictionary {
//        var valueDict = NSMutableDictionary()
//        valueDict["value"] = FlutterStandardTypedData(bytes: remoteConfigValue.dataValue)
//        valueDict["source"] = mapValueFromSource(source: remoteConfigValue.source)
//        
//        return valueDict
//    }
//    
//    private func mapValueFromSource(source: RemoteConfigSource) -> String {
//        switch source {
//            case .remote:
//                return "remote"
//            case .default:
//                return "default"
//            case .static:
//                return "static"
//            @unknown default:
//                return "static"
//        }
//    }
////    - (NSString *)mapValueSource:(FIRRemoteConfigSource)source {
////      if (source == FIRRemoteConfigSourceStatic) {
////        return @"static";
////      } else if (source == FIRRemoteConfigSourceDefault) {
////        return @"default";
////      } else if (source == FIRRemoteConfigSourceRemote) {
////        return @"remote";
////      } else {
////        return @"static";
////      }
////    }
////    - (NSMutableDictionary *)createRemoteConfigValueDict:(FIRRemoteConfigValue *)remoteConfigValue {
////      NSMutableDictionary *valueDict = [[NSMutableDictionary alloc] init];
////      valueDict[@"value"] = [FlutterStandardTypedData typedDataWithBytes:[remoteConfigValue dataValue]];
////      valueDict[@"source"] = [self mapValueSource:[remoteConfigValue source]];
////      return valueDict;
////    }
//}
