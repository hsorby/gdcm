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
#include "gdcmFile.h"


namespace gdcm
{

std::istream &File::Read(std::istream &is) 
{
  assert(0);
  return is;
}

std::ostream const &File::Write(std::ostream &os) const
{
  assert(0);
  return os;
}

} // end namespace gdcm

