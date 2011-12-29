//
//  CheckWifi.h
//  Playtomic
//
//  Created by matias calegaris on 12/28/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef Playtomic_CONNECTION_INFO_h
#define Playtomic_CONNECTION_INFO_h

namespace Playtomic {

    enum EConnectionType {
        e_disconnected = -1,
        e_mobile,
        e_wifi
    };
EConnectionType CheckConnectionType();
    
}

#endif
