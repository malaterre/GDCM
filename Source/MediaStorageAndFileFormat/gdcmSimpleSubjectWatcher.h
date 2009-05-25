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
#include "gdcmAnonymizeEvent.h"

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
  virtual void ShowAnonymization(Subject *caller, const Event &evt);
  virtual void ShowAbort();

private:
  SmartPointer<gdcm::Subject> m_Subject;
  std::string m_Comment;

  typedef SimpleMemberCommand<SimpleSubjectWatcher> SimpleCommandType;
  SmartPointer<SimpleCommandType> m_StartFilterCommand;
  SmartPointer<SimpleCommandType> m_EndFilterCommand;
  SmartPointer<SimpleCommandType> m_ProgressFilterCommand;
  SmartPointer<SimpleCommandType> m_IterationFilterCommand;
  SmartPointer<SimpleCommandType> m_AbortFilterCommand;

  typedef MemberCommand<SimpleSubjectWatcher> CommandType;
  SmartPointer<CommandType> m_AnonymizeFilterCommand;

  unsigned long m_StartTag;
  unsigned long m_EndTag;
  unsigned long m_ProgressTag;
  unsigned long m_IterationTag;
  unsigned long m_AbortTag;
  unsigned long m_AnonymizeTag;

  bool m_TestAbort;

  SimpleSubjectWatcher(const SimpleSubjectWatcher&);  // Not implemented.
  void operator=(const SimpleSubjectWatcher&);  // Not implemented.
};
} // end namespace gdcm
//-----------------------------------------------------------------------------
#endif //__gdcmSimpleSubjectWatcher_h
