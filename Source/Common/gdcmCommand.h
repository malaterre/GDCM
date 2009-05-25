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
#ifndef __gdcmCommand_h
#define __gdcmCommand_h

#include "gdcmSubject.h"

namespace gdcm
{
class Event;
/**
 * \class Command
 * \brief superclass for callback/observer methods
 *
 */
//-----------------------------------------------------------------------------
class GDCM_EXPORT Command : public Subject
{
public :
  /// Abstract method that defines the action to be taken by the command.
  virtual void Execute(Subject *caller, const Event & event ) = 0;

  /** Abstract method that defines the action to be taken by the command.
   * This variant is expected to be used when requests comes from a 
   * const Object */
  virtual void Execute(const Subject *caller, const Event & event ) = 0;

protected:
  Command();
  ~Command();

private:
  Command(const Command&);  // Not implemented.
  void operator=(const Command&);  // Not implemented.
};

/** \class SimpleMemberCommand
 *  \brief Command subclass that calls a pointer to a member function
 *
 *  SimpleMemberCommand calls a pointer to a member function with no 
 *  arguments.   
 */
template <typename T>
class SimpleMemberCommand : public Command
{ 
public:
  /** A method callback. */
  typedef  void (T::*TMemberFunctionPointer)(); 
  
  /** Standard class typedefs. */
  typedef SimpleMemberCommand   Self;
  //typedef SmartPointer<Self>    Pointer;
  
  /** Run-time type information (and related methods). */
  //itkTypeMacro(SimpleMemberCommand,Command);

  /** Method for creation through the object factory. */
  static SmartPointer<SimpleMemberCommand> New()
    {
    return new SimpleMemberCommand;
    }

  /** Specify the callback function. */
  void SetCallbackFunction(T* object,  
                           TMemberFunctionPointer memberFunction)
    {
    m_This = object;
    m_MemberFunction = memberFunction;
    }
  
  /** Invoke the callback function. */
  virtual void Execute(Subject *,const Event & ) 
    { 
    if( m_MemberFunction ) 
      {
      ((*m_This).*(m_MemberFunction))();
      }
    }
  virtual void Execute(const Subject *,const Event & ) 
    { 
    if( m_MemberFunction ) 
      {
      ((*m_This).*(m_MemberFunction))();
      }
    }
  
protected:
  T* m_This;
  TMemberFunctionPointer m_MemberFunction;
  SimpleMemberCommand():m_MemberFunction(0) {}
  virtual ~SimpleMemberCommand() {}

private:
  SimpleMemberCommand(const Self&); //purposely not implemented
  void operator=(const Self&); //purposely not implemented
};

} // end namespace gdcm
//-----------------------------------------------------------------------------
#endif //__gdcmCommand_h
