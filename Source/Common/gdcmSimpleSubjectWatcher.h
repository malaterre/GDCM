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
#ifndef __gdcmSimpleSubjectWatcher_h
#define __gdcmSimpleSubjectWatcher_h

#include "gdcmSubject.h"
#include "gdcmCommand.h"
#include "gdcmSmartPointer.h"

namespace gdcm
{
class Event;
/**
 * \class SimpleSubjectWatcher
 *
 */
//-----------------------------------------------------------------------------
class GDCM_EXPORT SimpleSubjectWatcher
{
public:
  SimpleSubjectWatcher(Subject * s, const char *comment = "");
  ~SimpleSubjectWatcher();

protected:
  // Custom API used for internal Testing do not use !
  void TestAbortOn();
  void TestAbortOff();

  virtual void StartFilter();
  virtual void EndFilter();
  virtual void ShowProgress();
  virtual void ShowIteration();
  virtual void ShowAbort();

private:
  SmartPointer<gdcm::Subject> m_Subject;
  std::string m_Comment;

  typedef SimpleMemberCommand<SimpleSubjectWatcher> CommandType;
  SmartPointer<CommandType> m_StartFilterCommand;
  SmartPointer<CommandType> m_EndFilterCommand;
  SmartPointer<CommandType> m_ProgressFilterCommand;
  SmartPointer<CommandType> m_IterationFilterCommand;
  SmartPointer<CommandType> m_AbortFilterCommand;

  unsigned long m_StartTag;
  unsigned long m_EndTag;
  unsigned long m_ProgressTag;
  unsigned long m_IterationTag;
  unsigned long m_AbortTag;

  SimpleSubjectWatcher(const SimpleSubjectWatcher&);  // Not implemented.
  void operator=(const SimpleSubjectWatcher&);  // Not implemented.
};
} // end namespace gdcm
//-----------------------------------------------------------------------------
#endif //__gdcmSimpleSubjectWatcher_h
