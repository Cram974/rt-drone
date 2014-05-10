#define ITG3200_ADDR_AD0_HIGH  0x69   //AD0=1 0x69 I2C address when AD0 is connected to HIGH (VCC) - default for sparkfun breakout
#define ITG3200_ADDR_AD0_LOW   0x68   //AD0=0 0x68 I2C address when AD0 is connected to LOW (GND)

#define GYROSTART_UP_DELAY  70    // 50ms from gyro startup + 20ms register r/w startup

/* ---- Registers ---- */
#define WHO_AM_I           0x00  // RW   SETUP: I2C address   
#define SMPLRT_DIV         0x15  // RW   SETUP: Sample Rate Divider       
#define DLPF_FS            0x16  // RW   SETUP: Digital Low Pass Filter/ Full Scale range
#define INT_CFG            0x17  // RW   Interrupt: Configuration
#define INT_STATUS         0x1A  // R   Interrupt: Status
#define TEMP_OUT           0x1B  // R   SENSOR: Temperature 2bytes
#define GYRO_XOUT          0x1D  // R   SENSOR: Gyro X 2bytes  
#define GYRO_YOUT          0x1F  // R   SENSOR: Gyro Y 2bytes
#define GYRO_ZOUT          0x21  // R   SENSOR: Gyro Z 2bytes
#define PWR_MGM            0x3E  // RW  Power Management

/* ---- bit maps ---- */
#define DLPFFS_FS_SEL             0x18  // 00011000
#define DLPFFS_DLPF_CFG           0x07  // 00000111
#define INTCFG_ACTL               0x80  // 10000000
#define INTCFG_OPEN               0x40  // 01000000
#define INTCFG_LATCH_INT_EN       0x20  // 00100000
#define INTCFG_INT_ANYRD_2CLEAR   0x10  // 00010000
#define INTCFG_ITG_RDY_EN         0x04  // 00000100
#define INTCFG_RAW_RDY_EN         0x01  // 00000001
#define INTSTATUS_ITG_RDY         0x04  // 00000100
#define INTSTATUS_RAW_DATA_RDY    0x01  // 00000001
#define PWRMGM_HRESET             0x80  // 10000000
#define PWRMGM_SLEEP              0x40  // 01000000
#define PWRMGM_STBY_XG            0x20  // 00100000
#define PWRMGM_STBY_YG            0x10  // 00010000
#define PWRMGM_STBY_ZG            0x08  // 00001000
#define PWRMGM_CLK_SEL            0x07  // 00000111

/******************************/
/*    REGISTERS FLAGS         */
/******************************/
// Sample Rate Divider
#define SRD_NONE                0x00 // default    FsampleHz=SampleRateHz/(divider+1)

// Gyro Full Scale Range
#define FS_RANGE2000               0x18   // default

// Digital Low Pass Filter BandWidth and SampleRate
#define DLPF_BW256_SR8          0x00   // default    256Khz BW and 8Khz SR
#define DLPF_BW188_SR1          0x01
#define DLPF_BW098_SR1          0x02
#define DLPF_BW042_SR1          0x03
#define DLPF_BW020_SR1          0x04
#define DLPF_BW010_SR1          0x05
#define DLPF_BW005_SR1          0x06

// Interrupt Active logic lvl
#define INT_ACTIVE_ONHIGH       0x00 // default
#define INT_ACTIVE_ONLOW        0x80
// Interrupt drive type
#define INT_PUSH_PULL           0x00 // default
#define INT_OPEN_DRAIN          0x40
// Interrupt Latch mode
#define INT_PULSE_50US          0x00 // default
#define INT_UNTIL_INT_CLEARED   0x20
// Interrupt Latch clear method
#define INT_READ_STATUSREG      0x00 // default
#define INT_READ_ANYREG         0x10
// Interrupt when Device is Ready?
#define INT_DEVICE_RDY             0x04
// Interrupt when data available
#define INT_DATA_AVBLE_EN        0x01


// Power management
#define PW_HRESET                 0x80
#define PW_SLEEP                  0x40
#define PW_STBY_XG               0x20
#define PW_STBY_YG               0x10
#define PW_STBY_ZG               0x08 
// Clock Source - user parameters
#define PW_INTERNALOSC             0x00 // default
#define PW_PLL_XGYRO_REF           0x01
#define PW_PLL_YGYRO_REF           0x02
#define PW_PLL_ZGYRO_REF           0x03
#define PW_PLL_EXTERNAL32          0x04 // 32.768 kHz
#define PW_PLL_EXTERNAL19          0x05 // 19.2 Mhz

