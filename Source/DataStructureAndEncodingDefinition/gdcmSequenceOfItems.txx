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
#ifndef __gdcmSequenceOfItems_txx
#define __gdcmSequenceOfItems_txx

namespace gdcm
{

template <typename TDE>
VL SequenceOfItems::ComputeLength() const
{
  typename ItemVector::const_iterator it = Items.begin();
  VL length = 0;
  for(;it != Items.end(); ++it)
    {
    length += it->template GetLength<TDE>();
    }
  if( SequenceLengthField.IsUndefined() )
    {
    length += 8; // item end delimitor (tag + vl)
    }
  // For defined length SQ, make sure computation is correct (compare
  // to original length)
  //assert( SequenceLengthField.IsUndefined()
  //  || length == SequenceLengthField );
  return length;
}

} // end namespace gdcm

#endif // __gdcmSequenceOfItems_txx
