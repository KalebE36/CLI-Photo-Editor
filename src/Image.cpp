#include <iostream>
#include "Image.h"




Image::Image() {

}

void Image::read(const string& in_name) {
  ifstream stream(in_name, ios_base::binary);

  if(!stream.is_open()) {
    cout << "file did not open" << endl;
  }

  stream.read(&header.idLength, sizeof(header.idLength));
  stream.read(&header.colorMapType, sizeof(header.colorMapType));
  stream.read(&header.dataTypeCode, sizeof(header.dataTypeCode));
  stream.read((char*)&header.colorMapOrigin, sizeof(header.colorMapOrigin));
  stream.read((char*)&header.colorMapLength, sizeof(header.colorMapLength));
  stream.read(&header.colorMapDepth, sizeof(header.colorMapDepth));
  stream.read((char*)&header.xOrigin, sizeof(header.xOrigin));
  stream.read((char*)&header.yOrigin, sizeof(header.yOrigin));
  stream.read((char*)&header.width, sizeof(header.width));
  stream.read((char*)&header.height, sizeof(header.height));
  stream.read(&header.bitsPerPixel, sizeof(header.bitsPerPixel));
  stream.read(&header.imageDescriptor, sizeof(header.imageDescriptor));

  int imageSize = (int)(header.width * header.height);

  for (int i = 0; i < imageSize; i++) {
       Pixel pixel;

       stream.read((char*)& pixel.blue, sizeof(pixel.blue));
       stream.read((char*)& pixel.green, sizeof(pixel.green));
       stream.read((char*)& pixel.red, sizeof(pixel.red));

       pixels.push_back(pixel);
   }

}

void Image::write(const string& outName) {
    ofstream stream(outName, ios_base::binary);

    stream.write(&header.idLength, sizeof(header.idLength));
    stream.write(&header.colorMapType, sizeof(header.colorMapType));
    stream.write(&header.dataTypeCode,sizeof(header.dataTypeCode));
    stream.write((char*)&header.colorMapOrigin,sizeof(header.colorMapOrigin));
    stream.write((char*)&header.colorMapLength,sizeof(header.colorMapLength));
    stream.write(&header.colorMapDepth, sizeof(header.colorMapDepth));
    stream.write((char*)&header.xOrigin, sizeof(header.xOrigin));
    stream.write((char*)&header.yOrigin, sizeof(header.yOrigin));
    stream.write((char*)&header.width, sizeof(header.width));
    stream.write((char*)&header.height, sizeof(header.height));
    stream.write(&header.bitsPerPixel, sizeof(header.bitsPerPixel) );
    stream.write(&header.imageDescriptor, sizeof(header.imageDescriptor));

    for (int i = 0; i < pixels.size(); i++) {
        Pixel pixel = pixels[i];

        stream.write((char*)& pixel.blue, sizeof(pixel.blue));
        stream.write((char*)& pixel.green, sizeof(pixel.green));
        stream.write((char*)& pixel.red, sizeof(pixel.red));
    }


}
