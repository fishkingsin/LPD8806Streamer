
import processing.serial.*;
import codeanticode.gsvideo.*;
/*
original : http://allthingseverywhere.com/blog/?p=633
Copyright (C) <2012> <James Kong>

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
GSCapture video;
int pixelCols = 8;
int pixelRows = 8;
int pixelWidth;
int pixelHeight;

float r;
float g;
float b;

static final int
nLEDs = 64, 
latchLen = (nLEDs + 63) / 64;
color[] led = new color[nLEDs];
byte[] serialBuf = new byte[3 * (nLEDs + latchLen)];
Serial port;
//gamma = new byte[256];
 byte gamma[]  = {
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,
    1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  2,  2,  2,  2,
    2,  2,  2,  2,  2,  3,  3,  3,  3,  3,  3,  3,  3,  4,  4,  4,
    4,  4,  4,  4,  5,  5,  5,  5,  5,  6,  6,  6,  6,  6,  7,  7,
    7,  7,  7,  8,  8,  8,  8,  9,  9,  9,  9, 10, 10, 10, 10, 11,
   11, 11, 12, 12, 12, 13, 13, 13, 13, 14, 14, 14, 15, 15, 16, 16,
   16, 17, 17, 17, 18, 18, 18, 19, 19, 20, 20, 21, 21, 21, 22, 22,
   23, 23, 24, 24, 24, 25, 25, 26, 26, 27, 27, 28, 28, 29, 29, 30,
   30, 31, 32, 32, 33, 33, 34, 34, 35, 35, 36, 37, 37, 38, 38, 39,
   40, 40, 41, 41, 42, 43, 43, 44, 45, 45, 46, 47, 47, 48, 49, 50,
   50, 51, 52, 52, 53, 54, 55, 55, 56, 57, 58, 58, 59, 60, 61, 62,
   62, 63, 64, 65, 66, 67, 67, 68, 69, 70, 71, 72, 73, 74, 74, 75,
   76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91,
   92, 93, 94, 95, 96, 97, 98, 99,100,101,102,104,105,106,107,108,
  109,110,111,113,114,115,116,117,118,120,121,122,123,125,126,127
};

int inde3x = (3 * (nLEDs + latchLen))-1;

void setup() {


  video= new GSCapture(this, 640, 480);  
  video.start();


  size(640, 480);
  pixelWidth = 640 / pixelCols;
  pixelHeight = 480 / pixelRows;
  // The “gamma” table actually does three things: applies gamma
  // correction to input colors to produce a more perceptually linear
  // output range, reduces 8-bit inputs to 7-bit outputs, and sets the
  // high bit as required by the LPD8806 LED data protocol.
  for (int i=0; i<256; i++) {
    gamma[i] = (byte)(0x80 | (int)(pow(((float)i / 255.0), 2.5) * 127.0 + 0.5));
  }

  // Assumes Arduino is first/only serial device. Change to suit:
  println(Serial.list());
  port = new Serial(this, Serial.list()[0], 115200);
  // colorMode(HSB, 10); // Easy rainbows
  //colorMode(HSB, 10);
}

void draw() {
  /////////////video stuff//////////////////

  //
  if (video.available())
  {
    video.read();
    video.loadPixels();
  }
  int count = 0;
  for (int x = 0; x < video.width; x += pixelWidth)
  {
    for (int y = 0; y < video.height; y += pixelHeight)
    {
      int index = x + y * 640;
//      r = red(video.pixels[index]);
//      g = green(video.pixels[index]);
//      b = blue(video.pixels[index]);

      // send the 9 color values like this in serial

      noStroke();
      fill(video.pixels[index]);
      rect(x, y, pixelWidth, pixelHeight);
      //output = r + "," + g+ ","+ b + "n";
      //port.write(output);
      //delay(100);
       led[count++] =video.pixels[index];//color( r, g, b);
//       println(count);
    }
  }

  //////////////////////////////
  //
  int i, j;
  //
  //
  //
  // // Fill the led color array with something interesting:
//  for (i=0; i < nLEDs; i++)
//  {
//    led[i] = color((frameCount + i) % r, g, b);
//  }
  // Convert data from led color array to LPD8806-ready format:
  for (i=j=0; i< nLEDs  ;i++) {
    serialBuf[j++] = gamma[(led[i] >> 8) & 0xff];
    serialBuf[j++] = gamma[(led[i] >> 16) & 0xff];
    serialBuf[j++] = gamma[ led[i] & 0xff];

  }
  // Arrays are zero-initialized in Processing/Java,
  // so no need to set up the latch data; it’s already there.
  port.write(serialBuf); // Issue LPD8806 data to Arduino

  // You *might* need to comment out the above line and use
  // the following code instead. Long writes fail for some
  // unknown reason. RXTX lib? Processing? Java? OS? Hardware?
  // for(i=0; i ; j = i + 255)
  //{
  // if(j > serialBuf.length) j = serialBuf.length;
  // port.write(Arrays.copyOfRange(serialBuf,i,j));
  // }
}

