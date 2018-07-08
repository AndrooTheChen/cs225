#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include <string>

using namespace cs225;


void rotate(std::string inputFile, std::string outputFile) {
  // Part 2
  PNG * inFile = new PNG();

  inFile->readFromFile(inputFile);
  unsigned width = inFile->width();
  unsigned height = inFile->height();

  PNG * output = new PNG(width, height);

  unsigned int newX, newY;
  for(unsigned int y = 0; y < height; y++) {
    for(unsigned int x = 0; x < width; x++) {
      HSLAPixel * currInPixel = inFile->getPixel(x, y);
      
      newX = width - x - 1;
      newY = height - y - 1;

      HSLAPixel * currOutPixel = output->getPixel(newX, newY);
      currOutPixel->h = currInPixel->h;
      currOutPixel->s = currInPixel->s;
      currOutPixel->l = currInPixel->l;
    }
  }

  output->writeToFile(outputFile);
  delete inFile;
  delete output;
}

PNG myArt(unsigned int width, unsigned int height) {
  PNG png(width, height);
  // Part 3

  return png;
}
