#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include <string>

using namespace cs225;


void rotate(std::string inputFile, std::string outputFile) {
  // Part 2
  PNG * inFile = NULL;

  inFile->readFromFile(inputFile);
  unsigned width = inFile->width();
  unsigned height = inFile->height();

  PNG * outFile = new PNG(width, height);

  int newX, newY;
  for(int x = 0; x < width; x++) {
    for(int y = 0; y < height; y++) {
      HSLAPixel * currInPixel = &(inFile->getPixel(x, y));
      
      newX = width - x;
      newY = height - y;

      HSLAPixel * currOutPixel = &(outFile->getPixel(newX, newY));
    }
  }

  outFile->writeToFile(outputFile);

}

PNG myArt(unsigned int width, unsigned int height) {
  PNG png(width, height);
  // Part 3

  return png;
}
