//
//  ViewController.h
//  RT-Drone
//
//  Created by Marc Dijoux on 01/04/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "NetworkController.h"

@interface ViewController : UIViewController
@property (weak, nonatomic) IBOutlet UISwitch *connectSwitch;
@property (weak, nonatomic) IBOutlet UILabel *accXLabel;
@property (weak, nonatomic) IBOutlet UILabel *accYLabel;
@property (weak, nonatomic) IBOutlet UILabel *accZLabel;
@property (weak, nonatomic) IBOutlet UIProgressView *accXBar;
@property (weak, nonatomic) IBOutlet UIProgressView *accYBar;
@property (weak, nonatomic) IBOutlet UIProgressView *accZBar;
@property (weak, nonatomic) IBOutlet UILabel *gyrXLabel;
@property (weak, nonatomic) IBOutlet UILabel *gyrYLabel;
@property (weak, nonatomic) IBOutlet UILabel *gyrZLabel;
@property (weak, nonatomic) IBOutlet UIProgressView *gyrXBar;
@property (weak, nonatomic) IBOutlet UIProgressView *gyrYBar;
@property (weak, nonatomic) IBOutlet UIProgressView *gyrZBar;
@property (weak, nonatomic) IBOutlet UILabel *motorPercentLabel;
@property (weak, nonatomic) IBOutlet UISlider *motorPercentSlide;

- (void)setAccX:(short)value;
- (void)setAccY:(short)value;
- (void)setAccZ:(short)value;
- (void)setGyrX:(short)value;
- (void)setGyrY:(short)value;
- (void)setGyrZ:(short)value;
- (IBAction)changeMotorSpeed:(id)sender;
- (IBAction)connectToDrone:(id)sender;
- (void)startTheBackgroundJob;

@end
