void setupModule() {
  sim800_serial.listen();
  sim800_serial.println("AT+SAPBR=3,1,\"Contype\",\"GPRS\"");
  waitResponse();
  sim800_serial.println("AT+CSTT=\""+APN+"\",\"\",\"\"");
  waitResponse();
  sim800_serial.println("AT+SAPBR=1,1");
  waitResponse();
  sim800_serial.println("AT+SAPBR=2,1");
  waitResponse();
  sim800_serial.flush();
}


