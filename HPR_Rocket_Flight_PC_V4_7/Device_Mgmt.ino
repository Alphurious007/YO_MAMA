//-----------------------------------------------
//Written by SparkyVT, TRA #12111, NAR #85720, L3
//-----------Change Log--------------------------
//22 OCT 23: Initial Build
//19 NOV 23: Increased devices supported
//***************************************************************************
//The system interfaces with the sensors through generic "begin" and "get" functions, i.e. beginAccel(), getAccel(),...
//Each function can either use an external library or use optimized drivers provided in Sensor_Drivers.ino
//The "begin" function is used to initialize the sensor and put it at the necessary gain and oupt data rates
//The "get" function is used to retrieve the raw data from the sensor.  Raw sensor dat is necessary to use the built-in calilbration
//***************************************************************************
//----------------------------
//LIST OF FUNCTIONS
//----------------------------
//beginAccel(): starts accelerometer
//getAccel(): gets accelerometer data
//beginGyro(): starts gyro
//getGyro(): gets gyro data
//beginHighG(): starts high-g accelerometer
//getHighG(): gets high-g accelerometer data
//beginMag(): starts magnetometer if exernal to IMU
//getMag(): gets magnetometer data
//beginBaro(): starts the barometer
//getBaro(): gets the barometer data
//beginRadio(): starts radio telemetry
//setRadioFreq(): sets the radio frequency
//setRadioPwr(): sets the radio power
//radioSleep(): sets the radio to sleep mode
//radioSendPkt(): sends the data packet
//clearTXdone(): clears TX flags on the radio
//GNSSconfig(): configures the GNSS unit for flight conditions
//GNSSpowerSaveMode(): reduces power consumption post-flight

void beginAccel() {

  switch (sensors.accel) {

    case 1:
      sensors.statusAccel = beginLSM303_A();
      break;

    case 2:
      sensors.statusAccel = sensors.statusGyro = beginLSM9DS1_AG();
      break;

    case 3:
      sensors.statusAccel = sensors.statusGyro = beginLSM6DS33();
      break;

    case 4:
      sensors.statusAccel = sensors.statusGyro = beginMPU6050();
      break;

    case 5:
      sensors.statusAccel = sensors.statusGyro = beginMPU9250_AG();
      break;
    
    case 6:
      sensors.statusAccel = sensors.statusGyro= beginLSM6DSOX();
      break;

    case 7://External Library          
      sensors.statusAccel = beginExternalAccel();
      break;
      
    default:
      sensors.statusAccel = beginExternalAccel();
      break;}

  //set G level
  g = (int16_t)(1.0 / accel.gainX);

  //set the g-trigger
  gTrigger = 2.5 * g;

  accel.gainX *= 9.80665;
  accel.gainY *= 9.80665;
  accel.gainZ *= 9.80665;}

void getAccel() {

  switch (sensors.accel) {

    case 1:
      getLSM303_A();
      break;

    case 2:
      getLSM9DS1_AG();
      break;

    case 3:
      getLSM6DS33();
      break;

    case 4: 
      getMPU6050();
      break;
    
    case 5:
      getMPU9250_AG();
      break;
    
    case 6:
      getLSM6DSOX();
      break;

    case 7://External Library

      getExternalAccel();

      break;
      
    default:
      getExternalAccel();
      break;}

  //indicate new sample
  accel.newSamp = true;

  //remove bias
  accel.rawX -= accel.biasX;
  accel.rawY -= accel.biasY;
  accel.rawZ -= accel.biasZ;
  

  //orient sensor data
  accel.x = accel.rawZ;
  accel.y = accel.rawY ;
  accel.z = accel.rawX * (-1);


  }



void beginMag() {

  switch (sensors.mag) {

    case 0://not present
      break;

    case 1:
      sensors.statusMag = beginLSM303_M();
      break;

    case 2:
      sensors.statusMag = beginLSM9DS1_M();
      break;

    case 3:
      sensors.statusMag = beginLIS3MDL();
      break;

    case 4:
      sensors.statusMag = beginMPU9250_M();
      break;
    
    case 5://External Library
      sensors.statusMag = beginExternalMag();
      break;
      
    default:
      sensors.statusMag = beginExternalMag();
      break;}
}

void getMag() {

  //get the sensor data
  switch (sensors.mag) {

    case 0://not present
      break;

    case 1:
      getLSM303_M();
      break;
    
    case 2:
      getLSM9DS1_M();
      break;

    case 3:
      getLIS3MDL();
      break;

    case 4:
      getMPU9250_M();
      break;
    
    case 5://External Library
      getExternalMag();
      break;
    
    default:
      getExternalMag();
      break;}

  //indicate new sample
  mag.newSamp = true;

  //remove bias
  mag.rawX -= mag.biasX;
  mag.rawY -= mag.biasY;
  mag.rawZ -= mag.biasZ;

  //translate sensor data
  mag.x = mag.rawZ;
  mag.y = mag.rawY ;
  mag.z = mag.rawX * (-1);
}

void beginGyro() {

  switch (sensors.gyro) {

    case 0://not present
      break;

    case 1:
      sensors.statusGyro = beginL3GD20H();
      break;

    case 2://LSM9DS1 - handled in accel setup
      break;

    case 3://LSM6DS33 - handled in accel setup
      break;

    case 4://MPU6050 - handled in accel setup
      break;

    case 5://MPU9250 - handled in accel setup
      break;

    case 6://LSM6DSOX - handled in accel setup
      break;

    case 7://External Library
      sensors.statusGyro = beginExternalGyro();
      break;

    default:
      sensors.statusGyro = beginExternalGyro();
      break;}
}

void getGyro() {

  //get sensor data
  switch (sensors.gyro) {
    
    case 0://not present
      break;

    case 1:
      getL3GD20H();
      break;

    case 2://LSM9DS1 - done in getAccel()
      break;

    case 3://LSM6DS33 - done in getAccel()
      break;

    case 4://MPU6050 - done in getAccel()
      break;

    case 5://MPU9250 - done in getAccel()
      break;

    case 6://LSM6DSOX - done in getAccel()
      break;
    
    case 7://External Library
      getExternalGyro();
      break;

    default:
      getExternalGyro();
      break;}

  //indicate new sample
  gyro.newSamp = true;

  //remove bias
  gyro.rawX -= gyro.biasX;
  gyro.rawY -= gyro.biasY;
  gyro.rawZ -= gyro.biasZ;

  //orient sensor data
  gyro.x = gyro.rawZ;
  gyro.y = gyro.rawY;
  gyro.z = gyro.rawX * (-1);}

void beginHighG() {

  switch (sensors.highG) {

    case 0://not present
      break;

    case 1:
      sensors.statusHighG = beginADS1115('S');
      break;

    case 2:
      sensors.statusHighG = beginH3LIS331DL();
      break;

    case 3:
      sensors.statusHighG = beginADXL377();
      break;

    case 4:
      sensors.statusHighG = beginExternalHighG();
      break;

    default:
      sensors.statusHighG = beginExternalHighG();
      break;}

  //set G level
  high1G = (int16_t)(1.0 / highG.gainX);
  highG.gainX *= 9.80665;
  highG.gainY *= 9.80665;
  highG.gainZ *= 9.80665;}

void getHighG() {

  switch (sensors.highG) {

    case 0://not present
      break;

    case 1:
      getADS1115();
      break;

    case 2:
      getH3LIS331DL();
      break;

    case 3:
      getADXL377();
      break;

    case 4:
      getExternalHighG();
      break;

    default:
      getExternalHighG();
      break;}

  //indicate new sample
  highG.newSamp = true;

  //remove bias
  highG.rawX -= highG.biasX;
  highG.rawY -= highG.biasY;
  highG.rawZ -= highG.biasZ;

  //orient sensor data
  highG.x = highG.rawZ;
  highG.y = highG.rawY;
  highG.z = highG.rawX  * (-1);
  }

void beginBaro() {

  switch (sensors.baro) {

    case 1:
      sensors.statusBaro = beginBMP180();
      break;

    case 2:
      sensors.statusBaro = beginMPL3115A2();
      break;

    case 3:
      sensors.statusBaro = beginBMP280();
      break;

    case 4:
      sensors.statusBaro = beginBMP388();
      break;

    case 5:
      sensors.statusBaro = beginMS56XX();
      break;

    case 6:
      sensors.statusBaro = beginMS56XX();
      break;

    case 7:
      sensors.statusBaro = beginLPS25H();
      break;

    case 8:
      sensors.statusBaro = beginExternalBaro();
      break;

    default:
      sensors.statusBaro = beginExternalBaro();
      break;}
}

void getBaro() {

  switch (sensors.baro) {

    case 1:
      getBMP180();
      break;

    case 2:
      getMPL3115A2();
      break;

    case 3:
      getBMP280();
      break;

    case 4:
      getBMP388();
      break;

    case 5:
      getMS56XX();
      break;

    case 6:
      getMS56XX();
      break;

    case 7:
      getLPS25H();
      break;

    case 8://External Library
      getExternalBaro();
      break;

    default:
      getExternalBaro();
      break;}
}

void beginRadio(){

  switch (sensors.radio){

    case 0:
      break;

    case 1:
      sensors.statusRadio = beginSX127X(pins.radioRST);
      break;

    case 2:
      sensors.statusRadio = beginRFD900();

    case 3:
      sensors.statusRadio = beginExternalRadio();
      break;

    default:
      sensors.statusRadio = beginExternalRadio();
      break;}
}

void setRadioFreq(float freq){

  switch(sensors.radio){
    
    case 0:
      break;

    case 1:
      setFreqSX127X(freq);
      break;
    
    case 2:
      break;

    case 3:
      setExternalRadioFreq(freq);
      break;

    default:
      setExternalRadioFreq(freq);
      break;}
}

bool configRadio70cm(){

  bool response = false;

  switch(sensors.radio){
    
    case 0:
      break;

    case 1:
      response = config70cmSX127X();
      break;
    
    case 2:
      break;

    case 3:
      response = configExternalRadio70cm();
      break;

    default:
      response =configExternalRadio70cm();
      break;}

  return response;}

void setRadioPWR(uint16_t pwr){

    switch(sensors.radio){

      case 0:
        break;

      case 1:
        setPwrSX127X(pwr);
        break;

      case 2:
        break;

      case 3:
        setExternalRadioPwr(pwr);
        break;

      default:
        setExternalRadioPwr(pwr);
        break;}
}

void radioSleep(){

  switch(sensors.radio){

    case 0:
      break;

    case 1:
      setModeSX127X(SleepMode);
      break;

    case 2:
      break;
    
    case 3:
      externalRadioSleep();
      break;

    default:
      externalRadioSleep();
      break;}
}

void clearTXdone(){

  switch(sensors.radio){

    case 0:
      break;

    case 1: 
      clearFlagsSX127X();
      break;

    case 2:
      break;

    case 3:
      clearFlagsExternalRadio();
      break;

    default:
      clearFlagsExternalRadio();
  }}

bool radioSendPkt(uint8_t* data, uint8_t len){

  bool response = false;

    switch(sensors.radio){

      case 0:
        break;

      case 1:
        response = sendPktSX127X(data, len);
        break;

      case 2:
        response = sendPktRFD900(data, len);

      case 3:
        response = sendExternalRadioDataPkt(data, len);
        break;
      
      default:
        response = sendExternalRadioDataPkt(data, len);}

  return response;}

void restoreGPSdefaults(){

  switch (sensors.GNSS) {

    case 0:
      break;

    case 1: 
      UBLOXrestorDefaults(true);
      break;

    case 2:
      UBLOXrestorDefaults(true);
      break;

    case 3:
      UBLOXrestorDefaults(true);
      break;

    case 4:
      break;

    default:
      break;}
}

void GNSSconfig(){

  switch (sensors.GNSS) {

    case 0:
      break;

    case 1: 
      UBLOXconfig(sensors.GNSS, settings.testMode, settings.flyBack);
      break;

    case 2:
      UBLOXconfig(sensors.GNSS, settings.testMode, settings.flyBack);
      break;

    case 3:
      UBLOXconfig(sensors.GNSS, settings.testMode, settings.flyBack);
      break;

    case 4:
      ExternalGNSSconfig();
      break;

    default:
      ExternalGNSSconfig();
      break;}
}

void GNSSpowerSave(){

  switch (sensors.GNSS) {

    case 0:
      break;

    case 1: 
      UBLOXpowerSave(sensors.GNSS, settings.testMode);
      break;

    case 2:
      UBLOXpowerSave(sensors.GNSS, settings.testMode);
      break;

    case 3:
      UBLOXpowerSave(sensors.GNSS, settings.testMode);
      break;

    case 4:
      externalGNSS_PSM();
      break;

    default:
      externalGNSS_PSM();
      break;}
}