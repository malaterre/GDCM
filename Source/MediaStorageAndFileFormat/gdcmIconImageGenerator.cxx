/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library

  Copyright (c) 2006-2011 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "gdcmIconImageGenerator.h"
#include "gdcmIconImage.h"
#include "gdcmAttribute.h"
#include "gdcmPrivateTag.h"
#include "gdcmImage.h"
#include "gdcmJPEGCodec.h"
#include "gdcmRescaler.h"

#include <list>
#include <limits>
#include <queue>
#include <algorithm>

namespace gdcm
{
class IconImageGeneratorInternals
{
public:
  IconImageGeneratorInternals()
    {
    dims[0] = dims[1] = 0;
    Min = 0;
    Max = 0;
    UseMinMax = false;
    }
  unsigned int dims[2];
  double Min;
  double Max;
  bool UseMinMax;
};

IconImageGenerator::IconImageGenerator():P(new Pixmap),I(new IconImage),Internals(new IconImageGeneratorInternals)
{
}

IconImageGenerator::~IconImageGenerator()
{
  delete Internals;
}

void IconImageGenerator::SetOutputDimensions(const unsigned int dims[2])
{
  Internals->dims[0] = dims[0];
  Internals->dims[1] = dims[1];
}

namespace quantization
{
// retrieved from:
// http://en.literateprograms.org/Special:Downloadcode/Median_cut_algorithm_(C_Plus_Plus)

/* Copyright (c) 2011 the authors listed at the following URL, and/or
the authors of referenced articles or incorporated external code:
http://en.literateprograms.org/Median_cut_algorithm_(C_Plus_Plus)?action=history&offset=20080309133934

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

Retrieved from: http://en.literateprograms.org/Median_cut_algorithm_(C_Plus_Plus)?oldid=12754
*/

  const int NUM_DIMENSIONS = 3;

  struct Point
    {
    unsigned char x[NUM_DIMENSIONS];
    };

  class Block
    {
    Point minCorner, maxCorner;
    Point* points;
    int pointsLength;
  public:
    Block(Point* points, int pointsLength);
    Point * getPoints();
    int numPoints() const;
    int longestSideIndex() const;
    int longestSideLength() const;
    bool operator<(const Block& rhs) const;
    void shrink();
    };

  template <int index>
    class CoordinatePointComparator
      {
    public:
      bool operator()(Point left, Point right)
        {
        return left.x[index] < right.x[index];
        }
      };

  //std::list<Point> medianCut(Point* image, int numPoints, unsigned int desiredSize);

  Block::Block(Point* pts, int ptslen)
    {
    this->points = pts;
    this->pointsLength = ptslen;
    for(int i=0; i < NUM_DIMENSIONS; i++)
      {
      minCorner.x[i] = std::numeric_limits<unsigned char>::min();
      maxCorner.x[i] = std::numeric_limits<unsigned char>::max();
      }
    }

  Point * Block::getPoints()
    {
    return points;
    }

  int Block::numPoints() const
    {
    return pointsLength;
    }

  int Block::longestSideIndex() const
    {
    int m = maxCorner.x[0] - minCorner.x[0];
    int maxIndex = 0;
    for(int i=1; i < NUM_DIMENSIONS; i++)
      {
      int diff = maxCorner.x[i] - minCorner.x[i];
      if (diff > m)
        {
        m = diff;
        maxIndex = i;
        }
      }
    return maxIndex;
    }

  int Block::longestSideLength() const
    {
    int i = longestSideIndex();
    return maxCorner.x[i] - minCorner.x[i];
    }

  bool Block::operator<(const Block& rhs) const
    {
    return this->longestSideLength() < rhs.longestSideLength();
    }

  void Block::shrink()
    {
    int i,j;
    for(j=0; j<NUM_DIMENSIONS; j++)
      {
      minCorner.x[j] = maxCorner.x[j] = points[0].x[j];
      }
    for(i=1; i < pointsLength; i++)
      {
      for(j=0; j<NUM_DIMENSIONS; j++)
        {
        minCorner.x[j] = std::min(minCorner.x[j], points[i].x[j]);
        maxCorner.x[j] = std::max(maxCorner.x[j], points[i].x[j]);
        }
      }
    }

  std::list<Point> medianCut(DataElement const &PixelData, int numPoints, unsigned int desiredSize,
    std::vector<unsigned char> & outputimage )
    {
    //Point* points = (Point*)malloc(sizeof(Point) * numPoints);
    Point* Points = new Point[numPoints];
    const ByteValue *bv = PixelData.GetByteValue();
    const char *inbuffer = bv->GetPointer();
    size_t bvlen = bv->GetLength(); (void)bvlen;
    assert( bvlen == (size_t) numPoints * 3 ); // only 8bits RGB please
    for(int i = 0; i < numPoints; i++)
      {
      memcpy(&Points[i], inbuffer + 3 * i, 3);
      }
    Point* image = Points;

    std::priority_queue<Block> blockQueue;

    Block initialBlock(image, numPoints);
    initialBlock.shrink();

    blockQueue.push(initialBlock);
    while (blockQueue.size() < desiredSize && blockQueue.top().numPoints() > 1)
      {
      Block longestBlock = blockQueue.top();

      blockQueue.pop();
      Point * begin  = longestBlock.getPoints();
      Point * median = longestBlock.getPoints() + (longestBlock.numPoints()+1)/2;
      Point * end    = longestBlock.getPoints() + longestBlock.numPoints();
      switch(longestBlock.longestSideIndex())
        {
      case 0: std::nth_element(begin, median, end, CoordinatePointComparator<0>()); break;
      case 1: std::nth_element(begin, median, end, CoordinatePointComparator<1>()); break;
      case 2: std::nth_element(begin, median, end, CoordinatePointComparator<2>()); break;
        }

      Block block1(begin, median-begin), block2(median, end-median);
      block1.shrink();
      block2.shrink();

      blockQueue.push(block1);
      blockQueue.push(block2);
      }

    std::list<Point> result;
    //int s = blockQueue.size();
    outputimage.resize( numPoints );
    //const ByteValue *bv = PixelData.GetByteValue();
    //const char *inbuffer = bv->GetPointer();

    while(!blockQueue.empty())
      {
      Block block = blockQueue.top();
      blockQueue.pop();
      Point * points = block.getPoints();

      int sum[NUM_DIMENSIONS] = {0};
      for(int i=0; i < block.numPoints(); i++)
        {
        for(int j=0; j < NUM_DIMENSIONS; j++)
          {
          sum[j] += points[i].x[j];
          }
        }

      Point averagePoint;
      for(int j=0; j < NUM_DIMENSIONS; j++)
        {
        averagePoint.x[j] = sum[j] / block.numPoints();
        }

      result.push_back(averagePoint);

      //int index = std::distance(s.begin(), it.first);
      int index = result.size();
      assert( index <= 256 );

      for(int i = 0; i < numPoints; i++)
        {
        const char *currentcolor = inbuffer + 3 * i;
        for(int j = 0; j < block.numPoints(); j++)
          {
          assert( currentcolor < inbuffer + bvlen );
          assert( currentcolor + 3 <= inbuffer + bvlen );
          if( std::equal( currentcolor, currentcolor + 3, points[j].x ) )
            {
            //assert( outputimage[i] == 0 );
            assert( index > 0 );
            outputimage[i] = index - 1;
            }
          }
        }
      }

    delete[] Points;
    return result;
    }

} // end namespace quantization

// Create LUT with a maximum number of color equal to \param maxcolor
void BuildLUT( Bitmap & bitmap, unsigned int maxcolor )
{
  using namespace quantization;
  const unsigned int *dims = bitmap.GetDimensions();
  unsigned int numPoints = dims[0]*dims[1];

  std::vector<unsigned char> indeximage;
  std::list<Point> palette =
    medianCut(bitmap.GetDataElement(), numPoints, maxcolor, indeximage);

  int ncolors = palette.size();
  LookupTable & lut = bitmap.GetLUT();
  lut.Clear();
  lut.Allocate( 8 );
  std::vector< unsigned char > buffer[3];
  for( int i = 0; i < 3; ++i )
    buffer[i].reserve( ncolors );

  std::list<Point>::const_iterator it = palette.begin();
  for( ; it != palette.end(); ++it )
    {
    Point const & p = *it;
    for( int i = 0; i < 3; ++i )
      buffer[i].push_back( p.x[i] );
    }

  for( int i = 0; i < 3; ++i )
    {
    lut.InitializeLUT( LookupTable::LookupTableType(i), ncolors, 0, 8 );
    lut.SetLUT( LookupTable::LookupTableType(i), &buffer[i][0], ncolors );
    }

  bitmap.GetDataElement().SetByteValue( (char*)&indeximage[0], indeximage.size() );
  assert( lut.Initialized() );
}

void IconImageGenerator::SetPixelMinMax(double min, double max)
{
  Internals->Min = min;
  Internals->Max = max;
  Internals->UseMinMax = true;
}

bool IconImageGenerator::Generate()
{
/*
PS 3.3-2009
F.7 ICON IMAGE KEY DEFINITION
a. Only monochrome and palette color images shall be used. Samples per Pixel
(0028,0002) shall have a Value of 1, Photometric Interpretation (0028,0004) shall
have a Value of either MONOCHROME 1, MONOCHROME 2 or PALETTE COLOR,
Planar Configuration (0028,0006) shall not be present
Note: True color icon images are not supported. This is due to the fact that the reduced size of the
Icon Image makes the quality of a palette color image (with 256 colors) sufficient in most cases.
This simplifies the handling of Icon Images by File-set Readers and File-set Updaters.
b. If an FSR/FSU supports Icons (i.e. does not ignore them) then it shall support at least
a maximum size of 64 by 64 Icons. An FSC may write Icons of any size. Icons larger
than 64 by 64 may be ignored by FSRs and FSUs unless specialized by Application
Profiles
c. Pixel samples have a Value of either 1 or 8 for Bits Allocated (0028,0100) and Bits
Stored (0028,0101). High Bit (0028,0102) shall have a Value of one less than the
Value used in Bit Stored
d. Pixel Representation (0028,0103) shall used an unsigned integer representation
(Value 0000H)
e. Pixel Aspect Ratio (0028,0034) shall have a Value of 1:1
f. If a Palette Color lookup Table is used, an 8 Bit Allocated (0028,0100) shall be used
*/
  I->Clear();
  I->SetNumberOfDimensions(2);
  I->SetDimension(0, Internals->dims[0] );
  I->SetDimension(1, Internals->dims[1] );

  PixelFormat oripf = P->GetPixelFormat();

  if( P->GetPhotometricInterpretation() != PhotometricInterpretation::MONOCHROME1
    && P->GetPhotometricInterpretation() != PhotometricInterpretation::MONOCHROME2
    && P->GetPhotometricInterpretation() != PhotometricInterpretation::PALETTE_COLOR
    && P->GetPhotometricInterpretation() != PhotometricInterpretation::RGB )
    {
    gdcmErrorMacro( "PhotometricInterpretation is not supported: "
      << P->GetPhotometricInterpretation() );
    return false;
    }

  if( P->GetPhotometricInterpretation() == PhotometricInterpretation::RGB )
    {
    I->SetPhotometricInterpretation( PhotometricInterpretation::PALETTE_COLOR );
    }
  else
    {
    I->SetPhotometricInterpretation( P->GetPhotometricInterpretation() );
    }

  assert( I->GetPlanarConfiguration() == 0 );

  std::vector< char > vbuffer;
  vbuffer.resize( P->GetBufferLength() );
  char *buffer = &vbuffer[0];
  bool b = P->GetBuffer(buffer);
  if( !b ) return false;

  // Important: After call to GetBuffer() in case we have a 12bits stored image
  I->SetPixelFormat( P->GetPixelFormat() );

  DataElement& pixeldata = I->GetDataElement();
  std::vector< char > vbuffer2;
  vbuffer2.resize( I->GetBufferLength() );

  uint8_t ps = I->GetPixelFormat().GetPixelSize();

  char *iconb = &vbuffer2[0];
  char *imgb = &vbuffer[0];

  const unsigned int *imgdims = P->GetDimensions();
  const unsigned int stepi = imgdims[0] / Internals->dims[0];
  const unsigned int stepj = imgdims[1] / Internals->dims[1];
  // Let's cherry-pick pixel from the input image. The nice thing about this approach
  // is that this also works for palletized image.
  // In the future it would be nice to also support averaging a group of pixel, instead
  // of always picking the top-left pixel from the block.
  for(unsigned int i = 0; i < Internals->dims[1]; ++i )
    for(unsigned int j = 0; j < Internals->dims[0]; ++j )
      {
      assert( (i * Internals->dims[0] + j) * ps < I->GetBufferLength() );
      assert( (i * imgdims[0] * stepj + j * stepi) * ps < P->GetBufferLength() );
      memcpy(iconb + (i * Internals->dims[0] + j) * ps,
        imgb + (i * imgdims[0] * stepj + j * stepi) * ps, ps );
      }
  // Apply LUT
  if( P->GetPhotometricInterpretation() == PhotometricInterpretation::PALETTE_COLOR )
    {
    std::istringstream is( std::string(&vbuffer2[0], vbuffer2.size() ) );
    std::stringstream ss;
    P->GetLUT().Decode( is, ss );

    if( I->GetPixelFormat().GetBitsAllocated() == 16 )
      {
      assert( I->GetPixelFormat().GetPixelRepresentation() == 0 );
      std::string s = ss.str();
      gdcm::Rescaler r;
      r.SetPixelFormat( I->GetPixelFormat() );
      //r.SetPixelFormat( PixelFormat::UINT16 );

      // FIXME: This is not accurate. We should either:
      // - Read the value from window/level to get better min,max value
      // - iterate over all possible value to find the min,max as we are looping
      // over all values anyway
      const double min = 0; // oripf.GetMin();
      const double max = 65536 - 1; //oripf.GetMax();
      r.SetSlope( 255. / (max - min + 0) ); // UINT8_MAX
      const double step = min * r.GetSlope();
      r.SetIntercept( 0 - step );

      // paranoid self check:
      assert( r.GetIntercept() + r.GetSlope() * min == 0. );
      assert( r.GetIntercept() + r.GetSlope() * max == 255. );

      r.SetTargetPixelType( PixelFormat::UINT8 );
      r.SetUseTargetPixelType(true);

      std::vector<char> v8;
      v8.resize( Internals->dims[0] * Internals->dims[1] * 3 );
      if( !r.Rescale(&v8[0],&s[0],s.size()) )
        {
        assert( 0 ); // should not happen in real life
        gdcmErrorMacro( "Problem in the rescaler" );
        return false;
        }
#if 1
      LookupTable &lut = I->GetLUT();
      lut.Allocate();

      // re-encode:
      std::stringstream ss2;
      ss2.str( std::string( &v8[0], v8.size() ) );

      std::ostringstream os;
      //I->GetLUT().Encode( ss2, os );

      //std::string s2 = os.str();
      std::string s2 = ss2.str();
      // As per standard, we only support 8bits icon
      I->SetPixelFormat( PixelFormat::UINT8 );
      pixeldata.SetByteValue( &s2[0], s2.size() );

      BuildLUT( *I, 256 );
#else
      I->SetPixelFormat( PixelFormat::UINT8 );
      pixeldata.SetByteValue( &v8[0], v8.size() );
#endif
      }
    else
      {
      assert( I->GetPixelFormat() == PixelFormat::UINT8 );
      LookupTable &lut = I->GetLUT();
      lut.Allocate();

      std::ostringstream os;
      //I->GetLUT().Encode( ss, os );

      //std::string s = os.str();
      std::string s = ss.str();
      // As per standard, we only support 8bits icon
      I->SetPixelFormat( PixelFormat::UINT8 );
      pixeldata.SetByteValue( &s[0], s.size() );

      BuildLUT(*I, 256 );
      }
    }
  else if( P->GetPhotometricInterpretation() == PhotometricInterpretation::RGB )
    {
    std::istringstream is( std::string(&vbuffer2[0], vbuffer2.size() ) );
    if( I->GetPixelFormat() == PixelFormat::UINT8 )
      {
      //LookupTable &lut = I->GetLUT();
      //lut.Allocate();

      std::ostringstream os;
      //P->BuildLUT( 256 );
      //I->SetLUT( P->GetLUT() );
      //I->GetLUT().Encode( is, os );

      //std::string s = os.str();
      std::string s = is.str();
      // As per standard, we only support 8bits icon
      I->SetPixelFormat( PixelFormat::UINT8 );
      pixeldata.SetByteValue( &s[0], s.size() );

      BuildLUT(*I, 256 );
      }
    else
      {
      assert( I->GetPixelFormat() == PixelFormat::UINT16 );
      assert( I->GetPixelFormat().GetPixelRepresentation() == 0 );
      std::string s = is.str();
      gdcm::Rescaler r;
      r.SetPixelFormat( I->GetPixelFormat() );
      //r.SetPixelFormat( PixelFormat::UINT16 );

      // FIXME: This is not accurate. We should either:
      // - Read the value from window/level to get better min,max value
      // - iterate over all possible value to find the min,max as we are looping
      // over all values anyway
      const double min = 0; // oripf.GetMin();
      const double max = 65536 - 1; //oripf.GetMax();
      r.SetSlope( 255. / (max - min + 0) ); // UINT8_MAX
      const double step = min * r.GetSlope();
      r.SetIntercept( 0 - step );

      // paranoid self check:
      assert( r.GetIntercept() + r.GetSlope() * min == 0. );
      assert( r.GetIntercept() + r.GetSlope() * max == 255. );

      r.SetTargetPixelType( PixelFormat::UINT8 );
      r.SetUseTargetPixelType(true);

      std::vector<char> v8;
      v8.resize( Internals->dims[0] * Internals->dims[1] * 3 );
      if( !r.Rescale(&v8[0],&s[0],s.size()) )
        {
        assert( 0 ); // should not happen in real life
        gdcmErrorMacro( "Problem in the rescaler" );
        return false;
        }


      LookupTable &lut = I->GetLUT();
      lut.Allocate();

      std::ostringstream os;
      //I->GetLUT().Encode( is, os );

      //std::string s = os.str();
      //std::string s = is.str();
      // FIXME: impossible as per standard:
      I->SetPixelFormat( PixelFormat::UINT8 );
      pixeldata.SetByteValue( &v8[0], v8.size() );

      BuildLUT(*I, 256 );
      }
    }
  else
    {
    // MONOCHROME1 / MONOCHROME2 ...
    char *buffer2 = &vbuffer2[0];
    pixeldata.SetByteValue( buffer2, vbuffer2.size() );

    gdcm::Rescaler r;
    r.SetPixelFormat( I->GetPixelFormat() );

    // FIXME: This is not accurate. We should either:
    // - Read the value from window/level to get better min,max value
    // - iterate over all possible value to find the min,max as we are looping
    // over all values anyway
    double min = oripf.GetMin();
    double max = oripf.GetMax();
    if( Internals->UseMinMax )
      {
      min = Internals->Min;
      max = Internals->Max;
      }
    r.SetSlope( 255. / (max - min + 0) ); // UINT8_MAX
    const double step = min * r.GetSlope();
    r.SetIntercept( 0 - step );

    // paranoid self check:
    assert( r.GetIntercept() + r.GetSlope() * min == 0. );
    assert( r.GetIntercept() + r.GetSlope() * max == 255. );

    r.SetTargetPixelType( PixelFormat::UINT8 );
    r.SetUseTargetPixelType(true);

    std::vector<char> v8;
    v8.resize( Internals->dims[0] * Internals->dims[1] );
    if( !r.Rescale(&v8[0],&vbuffer2[0],vbuffer2.size()) )
      {
      assert( 0 ); // should not happen in real life
      gdcmErrorMacro( "Problem in the rescaler" );
      return false;
      }

    // As per standard, we only support 8bits icon
    I->SetPixelFormat( PixelFormat::UINT8 );
    pixeldata.SetByteValue( &v8[0], v8.size() );
    }

  // \postcondition
  assert( I->GetPixelFormat().GetBitsAllocated() == 8 );
  assert( I->GetPixelFormat().GetBitsStored() == 8 );
  assert( I->GetPixelFormat().GetHighBit() == 7 );
  assert( I->GetPixelFormat().GetPixelRepresentation() == 0 );

  return true;
}

} // end namespace gdcm
