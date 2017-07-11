uint8_t uploadFingerpintTemplate(uint16_t id)
{
 uint8_t p = finger.loadModel(id);
  
  switch (p) {
    case FINGERPRINT_OK:
      Serial.print("template "); Serial.print(id); Serial.println(" loaded");
      break;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    default:
      Serial.print("Unknown error "); Serial.println(p);
      return p;
  }

  // OK success!

  p = finger.getModel();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.print("template "); Serial.print(id); Serial.println(" transferring");
      break;
   default:
      Serial.print("Unknown error "); Serial.println(p);
      return p;
  }
  
  uint8_t templateBuffer[256];
  memset(templateBuffer, 0xff, 256);  //zero out template buffer
  int index=0;
  uint32_t starttime = millis();
  while ((index < 256) && ((millis() - starttime) < 1000))
  {
    if (mySerial.available())
    {
      templateBuffer[index] = mySerial.read();
      st+=templateBuffer[index];
      index++;
    }
  }

  
  Serial.print(index); Serial.println(" bytes read");
  Serial.println(st);
  
  //dump entire templateBuffer.  This prints out 16 lines of 16 bytes
  /*for (int count= 0; count < 16; count++)
  {
    for (int i = 0; i < 16; i++)
    {
      Serial.print("0x");
      Serial.print(templateBuffer[count*16+i], HEX);
      Serial.print(", ");
    }
    Serial.println();
  }*/
}
