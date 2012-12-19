#include <SPI.h>
/*
original : http://allthingseverywhere.com/blog/?p=633
Copyright (C) <2012> <James Kong>

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
void setup() {
  int c;
  //boost up the sppeed
  // dont knoe the consequence
  // everything under testing
  //Caution !!!!
  Serial.begin(230400); // 32u4 ignores BPS, runs full speed
  // SPI is run at 2 MHz. LPD8806 can run much faster,
  // but unshielded wiring is susceptible to interference.
  // Feel free to experiment with other divider ratios.
  SPI.begin();
  SPI.setClockDivider(SPI_CLOCK_DIV8);
  SPDR = 0; // Dummy byte out to “prime” the SPI status register

  for(;;) { // loop() is avoided for max throughput
    while((c = Serial.read ()) < 0); // Wait for next serial byte in
      while(!(SPSR & (1<<SPIF))); // Wait for prior byte out
      SPDR =c;           // Issue new bytew
  }
}

void loop() { 
} // Do nothing

