#include <iostream>



struct Header {

  char idLength;
  char colorMapType;
  char dataTypeCode;
  short colorMapOrigin;
  short colorMapLength;
  char colorMapDepth;
  short xOrigin;
  short yOrigin;
  short width;
  short height;
  char bitsPerPixel;
  char imageDescriptor;

};



struct Pixel {
  unsigned char blue;
  unsigned char green;
  unsigned char red;

};

class Image {

public:
  Header header;
  vector<pixel> pixels;

  Image();
  void read(const string& in_name);
  void write(const string& out_name);
};
