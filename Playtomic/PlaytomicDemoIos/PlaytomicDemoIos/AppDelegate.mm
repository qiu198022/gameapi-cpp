//
//  AppDelegate.m
//  PlaytomicDemoIos
//
//  Created by matias calegaris on 11/16/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#import "AppDelegate.h"
#import "Playtomic/CPlaytomic.h"
#include "Playtomic/CLog.h"
#include "Playtomic/CData.h"
#include "Playtomic/CExceptionHandler.h"
//#include "Playtomic/CLogRequest.h"
#include <string>

void handleCrash(int signal)
{
    NSLog(@"crash!");
    //you can try to save any data you want to save here
}

@implementation AppDelegate

@synthesize window = _window;

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    self.window = [[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]];
    // Override point for customization after application launch.
    //NSString* path = [NSString stringWithString:[NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) objectAtIndex:0]];
   // path = [NSString stringWithFormat:@"%@/%@", path, @"pFailedLogs.txt"];
    std::string key("9f3f3b43cb234025");
    //char buff[256];
    //[path getCString:buff maxLength:256 encoding:NSUTF8StringEncoding];
   // Playtomic::CLogRequest::SetLogFileName( buff );
	Playtomic::CPlaytomic *mInstance = new Playtomic::CPlaytomic(4603, key, true);
    mInstance->Init();
    Playtomic::CExceptionHandler::SetHandlers();
    Playtomic::CExceptionHandler::SetSignalCallbackk(&handleCrash);
    mInstance->Log()->View();
    mInstance->Log()->Play();
    
    CPlaytomicResponsePtr response = Playtomic::gPlaytomic->Data()->Views();
    
    if (response->ResponseSucceded())
    {
        FData value;
        value = response->ResponseData().get("Value",value);
        NSLog(@"views = %s", value.asString().c_str());
    }
    else
    {
        NSLog(@"response failed error code = #%d", response->ResponseError());
    }
    void (*func)() = 0;
    
    func();
    
    self.window.backgroundColor = [UIColor whiteColor];
    [self.window makeKeyAndVisible];
    return YES;
}

- (void)applicationWillResignActive:(UIApplication *)application
{
    /*
     Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
     Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
     */
}

- (void)applicationDidEnterBackground:(UIApplication *)application
{
    /*
     Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later. 
     If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
     */
}

- (void)applicationWillEnterForeground:(UIApplication *)application
{
    /*
     Called as part of the transition from the background to the inactive state; here you can undo many of the changes made on entering the background.
     */
}

- (void)applicationDidBecomeActive:(UIApplication *)application
{
    /*
     Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
     */
}

- (void)applicationWillTerminate:(UIApplication *)application
{
    /*
     Called when the application is about to terminate.
     Save data if appropriate.
     See also applicationDidEnterBackground:.
     */
}

@end
