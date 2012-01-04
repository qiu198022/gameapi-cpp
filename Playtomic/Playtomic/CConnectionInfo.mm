//
//  ConnectionInfo.mm
//  Playtomic
//
//  Created by matias calegaris on 1/3/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifdef _IOSSDK_
#include "CConnectionInfo.h"
#include "../Reachability/Reachability.h"
#include "CPlaytomic.h"

namespace Playtomic
{
class CConnectionInfoiOS;
}
@interface ConnectionNotification : NSObject {
    Playtomic::CConnectionInfoiOS* mOwner; 
}

- (id) initWithOwner:(Playtomic::CConnectionInfoiOS*)owner;
- (void) checkNetworkStatus:(NSNotification *)notice;
@end


namespace Playtomic {

class CConnectionInfoiOS : public CConnectionInfoBase
{
public:
    ~CConnectionInfoiOS();
    virtual void Init();
    virtual EConnectionType GetConnectionType();
    
    void ConnectionChanged();
    
private:
    ConnectionNotification* notification;
    Reachability * hostReachable;
};
 
CConnectionInfoBase* CConnectionInfoBase::CreateInstance()
{
    return new CConnectionInfoiOS;
}
    
CConnectionInfoiOS::~CConnectionInfoiOS()
{
    [[NSNotificationCenter defaultCenter] removeObserver:notification];
    [notification release];
    [hostReachable release];
}

void CConnectionInfoiOS::Init()
{
    hostReachable = [[Reachability reachabilityWithHostName:@"www.playtomic.com"] retain];
    [hostReachable startNotifier];
    notification = [[ConnectionNotification alloc] initWithOwner:this];
    [[NSNotificationCenter defaultCenter] addObserver:notification
                                             selector:@selector(checkNetworkStatus:)
                                                 name:kReachabilityChangedNotification
                                               object:nil];
}

CConnectionInfoBase::EConnectionType CConnectionInfoiOS::GetConnectionType()
{
    // check if a pathway to a random host exist
    NetworkStatus internetStatus = [hostReachable currentReachabilityStatus];
    switch (internetStatus)
    
    {
        case NotReachable:
            return e_disconnected;
            break;
        case ReachableViaWiFi:
            return e_wifi;
            break;
        case ReachableViaWWAN:
            return e_mobile;
            break;

    }
    return e_disconnected;
}
    
void CConnectionInfoiOS::ConnectionChanged()
{
    if(GetConnectionType() == e_wifi)
    {
        gPlaytomic->WiFiBecomeActive();
    }
}
    
}//namespace playtomic end

@implementation ConnectionNotification

- (id) initWithOwner:(Playtomic::CConnectionInfoiOS *)owner
{
    self = [super init];
    
    mOwner = owner;
    return self;
}

- (void) checkNetworkStatus:(NSNotification *)notice
{
    mOwner->ConnectionChanged();
}
@end
#endif