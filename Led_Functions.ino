void ledFlash(int frequency){
  if (millis() - lastBlink > frequency) {
      lastBlink = millis();
      
      ledState = !ledState;
      digitalWrite(LED_BUILTIN, ledState ? LOW : HIGH);
    }
}