String waitResponse() {
  String response;
  while(!sim800_serial.available()){}
  while(sim800_serial.available()){
    response += sim800_serial.readString();
  }
//  Serial.println(response); //for debug only
  return response;
}
