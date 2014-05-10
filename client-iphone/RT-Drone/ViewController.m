//
//  ViewController.m
//  RT-Drone
//
//  Created by Marc Dijoux on 01/04/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "ViewController.h"

@interface ViewController ()

@end

@implementation ViewController
@synthesize connectSwitch;
@synthesize accXLabel;
@synthesize accYLabel;
@synthesize accZLabel;
@synthesize accXBar;
@synthesize accYBar;
@synthesize accZBar;
@synthesize gyrXLabel;
@synthesize gyrYLabel;
@synthesize gyrZLabel;
@synthesize gyrXBar;
@synthesize gyrYBar;
@synthesize gyrZBar;
@synthesize motorPercentLabel;
@synthesize motorPercentSlide;

- (void)viewDidLoad
{
    [super viewDidLoad];
    [NetworkController connect:"127.0.0.1"/*"192.168.1.1"*/ srcport:4243 dstport:4242 sender:self];
	// Do any additional setup after loading the view, typically from a nib.
}

- (void)viewDidUnload
{
    [self setAccXLabel:nil];
    [self setAccYLabel:nil];
    [self setAccZLabel:nil];
    [self setGyrXLabel:nil];
    [self setGyrYLabel:nil];
    [self setGyrZLabel:nil];
    [self setMotorPercentLabel:nil];
    [self setMotorPercentSlide:nil];
    [self setAccXBar:nil];
    [self setAccYBar:nil];
    [self setAccZBar:nil];
    [self setGyrXBar:nil];
    [self setGyrYBar:nil];
    [self setGyrZBar:nil];
    [self setConnectSwitch:nil];
    [super viewDidUnload];
    // Release any retained subviews of the main view.
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    return interfaceOrientation == UIInterfaceOrientationPortrait;
}

- (void)setAccX:(short)value{
    accXBar.progress = (200+value)/400.0;
    accXLabel.text = [NSString stringWithFormat:@"x: %i G",value];
}
- (void)setAccY:(short)value{
    accYBar.progress = (200+value)/400.0;
    accYLabel.text = [NSString stringWithFormat:@"y: %i G",value];
}
- (void)setAccZ:(short)value{
    accZBar.progress = (200+value)/400.0;
    accZLabel.text = [NSString stringWithFormat:@"z: %i G",value];
}
- (void)setGyrX:(short)value{
    gyrXBar.progress = (200+value)/400.0;
    gyrXLabel.text = [NSString stringWithFormat:@"x: %i °/s²",value];
}
- (void)setGyrY:(short)value{
    gyrYBar.progress = (200+value)/400.0;
    gyrYLabel.text = [NSString stringWithFormat:@"y: %i °/s²",value];

}
- (void)setGyrZ:(short)value{
    gyrZBar.progress = (200+value)/400.0;
    gyrZLabel.text = [NSString stringWithFormat:@"z: %i °/s²",value];

}

- (IBAction)changeMotorSpeed:(id)sender {
    motorPercentLabel.text = [NSString stringWithFormat:@"%i%%",(int)motorPercentSlide.value];
    
    if(connectSwitch.on){
        [NetworkController sendCMD:[NSString stringWithFormat:@"set motor speed 1 %i$",(int)motorPercentSlide.value]];
    }
}

- (IBAction)connectToDrone:(id)sender {
    if(!connectSwitch.on){
        [NetworkController sendCMD:@"set motor speed 1 0$"];
    }
    else{
        [NetworkController sendCMD:[NSString stringWithFormat:@"set motor speed 1 %i$",(int)motorPercentSlide.value]];
    }
}




- (void)startTheBackgroundJob{  
    [self performSelectorOnMainThread:@selector(getSensorsValues) withObject:nil waitUntilDone:NO];  
}  

- (void)getSensorsValues {  
        [self setAccX:(rand()%401)-200];
        [self setAccY:(rand()%401)-200];
        [self setAccZ:(rand()%401)-200];
        [self setGyrX:(rand()%401)-200];
        [self setGyrY:(rand()%401)-200];
        [self setGyrZ:(rand()%401)-200];
        if(connectSwitch.on)
            [NSTimer scheduledTimerWithTimeInterval:0.7 target:self selector:@selector(getSensorsValues) userInfo:nil repeats:NO];
}
@end
