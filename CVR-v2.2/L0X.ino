bool initL0X(){
  if(owl.begin(0x30)){
    return true;
  }else{
    return false;
  } 
}

int16_t updateL0X(){
  //get measurement
  owl.rangingTest(&dis_measurement, false);

  //if data is clean return distance in mm
  if(dis_measurement.RangeStatus != 4){
    return dis_measurement.RangeMilliMeter;
  }else{
    return -1;
  }
}

