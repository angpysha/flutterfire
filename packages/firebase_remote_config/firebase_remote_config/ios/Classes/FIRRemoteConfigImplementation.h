//
//  FIRRemoteConfigImplementation.h
//  firebase_remote_config
//
//  Created by Andrii on 18.05.2024.
//

#import <Foundation/Foundation.h>
#import "messages.g.h"

NS_ASSUME_NONNULL_BEGIN

@interface FIRRemoteConfigImplementation : NSObject<RemoteConfigHostApi>
- (void)ensureInitializedAppName:(NSString *)appName completion:(void (^)(FlutterError *_Nullable))completion;
- (void)activateAppName:(NSString *)appName completion:(void (^)(NSNumber *_Nullable, FlutterError *_Nullable))completion;
- (void)fetchAppName:(NSString *)appName completion:(void (^)(FlutterError *_Nullable))completion;
- (void)fetchAndActivateAppName:(NSString *)appName completion:(void (^)(NSNumber *_Nullable, FlutterError *_Nullable))completion;
- (void)setConfigSettingsAppName:(NSString *)appName fetchTimeout:(NSInteger)fetchTimeout minimumFetchInterval:(NSInteger)minimumFetchInterval completion:(void (^)(FlutterError *_Nullable))completion;
- (void)setDefaultsAppName:(NSString *)appName defaultParameters:(NSDictionary<NSString *, id> *)defaultParameters completion:(void (^)(FlutterError *_Nullable))completion;
- (void)getAllAppName:(NSString *)appName completion:(void (^)(NSDictionary<id, id> *_Nullable, FlutterError *_Nullable))completion;
- (void)getPropertiesAppName:(NSString *)appName completion:(void (^)(NSDictionary<id, id> *_Nullable, FlutterError *_Nullable))completion;
@end

NS_ASSUME_NONNULL_END
