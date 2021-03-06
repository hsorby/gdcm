/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2009 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "gdcmImageToImageFilter.h"
#include "gdcmImage.h"

namespace gdcm
{

ImageToImageFilter::ImageToImageFilter()
{
  Input = new Image;
  Output = new Image;
}

Image &ImageToImageFilter::GetInput()
{
  return dynamic_cast<Image&>(*Input);
}

const Image &ImageToImageFilter::GetOutput() const
{
  return dynamic_cast<const Image&>(*Output);
}


} // end namespace gdcm

