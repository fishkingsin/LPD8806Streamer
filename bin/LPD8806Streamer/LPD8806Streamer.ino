#include <SPI.h>
// conect LPD8806 DI to pin 11(MOSI) 
// conect LPD8806 CI to pin 13(SCLK)
//separate power connect GND together
//5V to LPD8806
void setup() {
  int c;
  Serial.begin(115200); // 32u4 ignores BPS, runs full speed
  // SPI is run at 2 MHz. LPD8806 can run much faster,
  // but unshielded wiring is susceptible to interference.
  // Feel free to experiment with other divider ratios.
  SPI.begin();
  SPI.setClockDivider(SPI_CLOCK_DIV8);
  SPDR = 0; // Dummy byte out to “prime” the SPI status register

  for(;;) { // loop() is avoided for max throughput
    while((c = Serial.read ()) < 0); // Wait for next serial byte in
      while(!(SPSR & (1<<SPIF))); // Wait for prior byte out
      SPDR =c;           // Issue new byte
  }
}

void loop() { 
} // Do nothing

