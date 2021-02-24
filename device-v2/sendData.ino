String sendData (String url){
  sim800_serial.listen();
  sim800_serial.println("AT+SAPBR=1,1");
  waitResponse();
  sim800_serial.println("AT+HTTPINIT");
  waitResponse();
  sim800_serial.println("AT+HTTPPARA=\"CID\",1");
  waitResponse();
//  Serial.println("GET: "+url);
  sim800_serial.println("AT+HTTPPARA=\"URL\",\""+url+"\"");
  waitResponse();
  sim800_serial.println("AT+HTTPACTION=0");
  
  String loading = waitResponse();
  while(loading.indexOf("AT+HTTPACTION=0")>=0){
    loading = waitResponse();
  }
  
  sim800_serial.println("AT+HTTPREAD");
  
  String resp = waitResponse();
  int idx = resp.indexOf("\n",resp.indexOf("\n")+1);
  resp = resp.substring(idx+1,resp.indexOf("OK")-1);
  
  sim800_serial.println("AT+HTTPTERM");
  waitResponse();
  sim800_serial.flush();
//  Serial.println(resp);
  return resp;
}  

