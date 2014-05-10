#import <CoreFoundation/CoreFoundation.h> 
#include "ViewController.h"
#include <sys/socket.h> 
#include <netinet/in.h>

@interface NetworkController
+ (void) connect:(const char*)adresse srcport:(int)srcport dstport:(int)dstport sender:(id)sender;
+ (void)send:(const char*)data length:(int) length;
+ (void)sendCMD:(const NSString*)cmd;
@end