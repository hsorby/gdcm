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
#include "gdcmDataElement.h"

#include "gdcmByteValue.h"
#include "gdcmAttribute.h"
#include "gdcmSequenceOfFragments.h"
#include "gdcmSequenceOfItems.h"
#include "gdcmImplicitDataElement.h"

namespace gdcm
{
  void DataElement::SetVLToUndefined() { 
    assert( VRField == VR::SQ || VRField == VR::INVALID );
    SequenceOfItems *sqi = GetSequenceOfItems();
    //SequenceOfItems *sqi = dynamic_cast<SequenceOfItems*>(&GetValue());
    if( sqi )
      {
      sqi->SetLengthToUndefined();
      }
    ValueLengthField.SetToUndefined();
  }

  SequenceOfItems* DataElement::GetSequenceOfItems() {
    SequenceOfItems *sqi = dynamic_cast<SequenceOfItems*>(ValueField.GetPointer());
    if(!sqi)
      {
      // Was the element loaded as a byte value ? Let's check:
      assert( IsEmpty() );
      }
    return sqi;
  }
  const SequenceOfItems* DataElement::GetSequenceOfItems() const {
    const SequenceOfItems *sqi = dynamic_cast<SequenceOfItems*>(ValueField.GetPointer());
    if(!sqi)
      {
      // Was the element loaded as a byte value ? Let's check:
      assert( IsEmpty() );
      }
    return sqi;
  }
  const SequenceOfFragments* DataElement::GetSequenceOfFragments() const {
    const SequenceOfFragments *sqf = dynamic_cast<SequenceOfFragments*>(ValueField.GetPointer());
    return sqf;
  }

  /*
   *  Two cases are handled:
   *  - Simple ones:
   *     Explicit file with VR::SQ (defined or undefined length)
   *     Implicit file with undefined length (clearly a SQ)
   *  - If not in the previous case then we are in the second case: complex one (hidden SQ)
   *     Implicit file with defined length SQ
   *     Explicit file with SQ declared as UN + undefined length
   */
  SmartPointer<SequenceOfItems> DataElement::GetValueAsSQ() const
    {
    if( IsEmpty() /*|| GetByteValue()*/ || GetSequenceOfFragments() )
      {
      return 0;
      }
    SequenceOfItems *sq = dynamic_cast<SequenceOfItems*>(ValueField.GetPointer());
    if( sq ) // all set !
      {
      //assert( GetVR() == VR::SQ );
      SmartPointer<SequenceOfItems> sqi = sq;
      return sqi;
      }

    const Tag itemStart(0xfffe, 0xe000);
      {
        {
        if( GetVR() == VR::INVALID )
          {
          const ByteValue *bv = GetByteValue();
          assert( bv );
          SequenceOfItems *sqi = new SequenceOfItems;
          sqi->SetLength( bv->GetLength() );
          std::string s( bv->GetPointer(), bv->GetLength() );
          try
            {
            std::stringstream ss;
            ss.str( s );
            sqi->Read<ImplicitDataElement,SwapperNoOp>( ss );
            }
          catch(Exception &ex)
            {
            const Tag itemPMSStart(0xfeff, 0x00e0);
            const Tag itemPMSStart2(0x3f3f, 0x3f00);

            // same player ...
            std::stringstream ss;
            ss.str( s );
            Tag item;
            item.Read<SwapperNoOp>(ss);
            assert( item == itemPMSStart );
            ss.seekg(-4,std::ios::cur);
            sqi->Read<ExplicitDataElement,SwapperDoOp>( ss );
            }
          return sqi;
          }
        else
          {
          assert( GetVR() == VR::UN ); // cp 246, IVRLE SQ
          const ByteValue *bv = GetByteValue();
          assert( bv );
          SequenceOfItems *sqi = new SequenceOfItems;
          sqi->SetLength( bv->GetLength() );
          std::stringstream ss;
          ss.str( std::string( bv->GetPointer(), bv->GetLength() ) );
          sqi->Read<ImplicitDataElement,SwapperNoOp>( ss );
          return sqi;
          }
        }
      }
    //    catch( ParseException &pex )
    //      {
    //      gdcmDebugMacro( pex.what() );
    //      }
    //    catch( Exception &ex )
    //      {
    //      gdcmDebugMacro( ex.what() );
    //      }
    //    catch( ... )
    //      {
    //      gdcmWarningMacro( "Unknown exception" );
    //      }

    return 0;
    }

} // end namespace gdcm

