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
#include "gdcmSimpleSubjectWatcher.h"
#include "gdcmEvent.h"

namespace gdcm
{

SimpleSubjectWatcher::SimpleSubjectWatcher(Subject *s, const char *comment):m_Subject(s),m_Comment(comment)
{
  // Create a series of commands
  m_StartFilterCommand =      CommandType::New();
  m_EndFilterCommand =        CommandType::New();
  m_ProgressFilterCommand =   CommandType::New();
  m_IterationFilterCommand =  CommandType::New();
  m_AbortFilterCommand =      CommandType::New();

  // Assign the callbacks
  m_StartFilterCommand->SetCallbackFunction(this,
                                        &SimpleSubjectWatcher::StartFilter);
  m_EndFilterCommand->SetCallbackFunction(this,
                                        &SimpleSubjectWatcher::EndFilter);
  m_ProgressFilterCommand->SetCallbackFunction(this,
                                        &SimpleSubjectWatcher::ShowProgress);
  m_IterationFilterCommand->SetCallbackFunction(this,
                                        &SimpleSubjectWatcher::ShowIteration);
  m_AbortFilterCommand->SetCallbackFunction(this,
                                        &SimpleSubjectWatcher::ShowAbort);


  // Add the commands as observers
  m_StartTag = m_Subject->AddObserver(StartEvent(), m_StartFilterCommand);
  m_EndTag = m_Subject->AddObserver(EndEvent(), m_EndFilterCommand);
  m_ProgressTag
    = m_Subject->AddObserver(ProgressEvent(), m_ProgressFilterCommand);
  m_IterationTag
    = m_Subject->AddObserver(IterationEvent(), m_IterationFilterCommand);
  m_AbortTag
    = m_Subject->AddObserver(AbortEvent(), m_AbortFilterCommand);

}

SimpleSubjectWatcher::~SimpleSubjectWatcher()
{
}

void SimpleSubjectWatcher::StartFilter()
{
  std::cout << "Start" << std::endl;
}
void SimpleSubjectWatcher::EndFilter()
{
  std::cout << "End" << std::endl;
}
void SimpleSubjectWatcher::ShowProgress()
{
}
void SimpleSubjectWatcher::ShowIteration()
{
}
void SimpleSubjectWatcher::ShowAbort()
{
}

void SimpleSubjectWatcher::TestAbortOn()
{
}
void SimpleSubjectWatcher::TestAbortOff()
{
}


} // end namespace gdcm
