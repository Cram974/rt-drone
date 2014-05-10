
#include "NetworkController.h"

@interface NetworkController ()

@end

@implementation NetworkController

CFSocketRef _socket;
CFSocketRef _servsocket;

struct sockaddr_in _address;

+ (void) connect:(const char*)adresse srcport:(int)srcport dstport:(int)dstport sender:(id)sender{
    _socket = CFSocketCreate( kCFAllocatorDefault, PF_INET, SOCK_DGRAM, IPPROTO_UDP, kCFSocketDataCallBack, dataReceived, 0);
    
    _address.sin_len         = sizeof(_address);
    _address.sin_family      = AF_INET;
    _address.sin_port        = htons(dstport);
    int a,b,c,d;
    if(sscanf(adresse, "%i.%i.%i.%i", &a,&b,&c,&d)==4)
        _address.sin_addr.s_addr = a + (b<<8) + (c<<16) + (d<<24);//a.b.c.d
    
    struct sockaddr_in local_addr;
    local_addr.sin_len = sizeof(local_addr);
    local_addr.sin_family = AF_INET;
    local_addr.sin_port = htons(srcport);
    local_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    
    CFDataRef adressRef = CFDataCreate(kCFAllocatorDefault,(UInt8*)&local_addr,sizeof(local_addr));
    CFSocketContext ctx = {0, (__bridge void *)sender, NULL, NULL, NULL};
    
    _servsocket = CFSocketCreate(kCFAllocatorDefault, PF_INET, SOCK_DGRAM, IPPROTO_UDP, kCFSocketDataCallBack, (CFSocketCallBack)&dataReceived, &ctx);
    CFSocketSetAddress(_servsocket, adressRef);
    
    CFRunLoopSourceRef srcRef = CFSocketCreateRunLoopSource(kCFAllocatorDefault, _servsocket, 0);
    CFRunLoopAddSource(CFRunLoopGetCurrent(), srcRef, kCFRunLoopCommonModes);
    CFRelease(srcRef);
    
}

+ (void)send:(const char*)data length:(int)length{
    CFDataRef adressRef = CFDataCreate(kCFAllocatorDefault,(UInt8*)&_address,sizeof(_address));
    CFDataRef dataRef = CFDataCreate(kCFAllocatorDefault,(UInt8*)data,length);
    CFSocketSendData(_socket, adressRef, dataRef, 1);
}

+ (void)sendCMD:(NSString*)cmd{
    [NetworkController send:[cmd UTF8String] length:[cmd length]];
}
;
static void dataReceived(CFSocketRef s, CFSocketCallBackType type, CFDataRef address, const void *data, void *info)
{
    int length = CFDataGetLength(data);
    //char* buffer = (char*)CFDataGetBytePtr(data);
    char*buffer = malloc(length+1);
    
    memcpy(buffer, CFDataGetBytePtr(data), length);
    
    int x,y,z;

    if(sscanf(buffer, "set acc 3 %i %i %i$", &x,&y,&z)==3) {
        [(__bridge id)info setAccX:x];  
        [(__bridge id)info setAccY:y];  
        [(__bridge id)info setAccZ:z];  
    }
    else if(sscanf(buffer, "set gyro 3 %i %i %i$", &x,&y,&z)==3) {
        [(__bridge id)info setGyrX:x];  
        [(__bridge id)info setGyrY:y];  
        [(__bridge id)info setGyrZ:z];  
    }
    
}

@end