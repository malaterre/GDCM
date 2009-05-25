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
#include "gdcmAnonymizeEvent.h"

namespace gdcm
{

SimpleSubjectWatcher::SimpleSubjectWatcher(Subject *s, const char *comment):m_Subject(s),m_Comment(comment)
{
  // Create a series of commands
  m_StartFilterCommand =      SimpleCommandType::New();
  m_EndFilterCommand =        SimpleCommandType::New();
  m_ProgressFilterCommand =   SimpleCommandType::New();
  m_IterationFilterCommand =  SimpleCommandType::New();
  m_AbortFilterCommand =      SimpleCommandType::New();

  m_AnonymizeFilterCommand =      CommandType::New();

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
  m_AnonymizeFilterCommand->SetCallbackFunction(this,
                                        &SimpleSubjectWatcher::ShowAnonymization);


  // Add the commands as observers
  m_StartTag = m_Subject->AddObserver(StartEvent(), m_StartFilterCommand);
  m_EndTag = m_Subject->AddObserver(EndEvent(), m_EndFilterCommand);
  m_ProgressTag
    = m_Subject->AddObserver(ProgressEvent(), m_ProgressFilterCommand);
  m_IterationTag
    = m_Subject->AddObserver(IterationEvent(), m_IterationFilterCommand);
  m_AbortTag
    = m_Subject->AddObserver(AbortEvent(), m_AbortFilterCommand);
  m_AnonymizeTag
    = m_Subject->AddObserver(AnonymizeEvent(), m_AnonymizeFilterCommand);

  m_TestAbort = false;
}

SimpleSubjectWatcher::~SimpleSubjectWatcher()
{
//  // Remove any observers we have on the old process object
//  if (m_Process)
//    {
//    if (m_StartFilterCommand)
//      {
//      m_Process->RemoveObserver(m_StartTag);
//      }
//    if (m_EndFilterCommand)
//      {
//      m_Process->RemoveObserver(m_EndTag);
//      }
//    if (m_ProgressFilterCommand)
//      {
//      m_Process->RemoveObserver(m_ProgressTag);
//      }
//    if (m_IterationFilterCommand)
//      {
//      m_Process->RemoveObserver(m_IterationTag);
//      }
//    if (m_AbortFilterCommand)
//      {
//      m_Process->RemoveObserver(m_AbortTag);
//      }
//    }
//  
//  // Initialize state
//  m_TimeProbe = watch.m_TimeProbe;
//  m_Process = watch.m_Process;
//  m_Steps = watch.m_Steps;
//  m_Comment = watch.m_Comment;
//  m_TestAbort = watch.m_TestAbort;
//  m_Quiet = watch.m_Quiet;
//
//  m_StartTag = 0;
//  m_EndTag = 0;
//  m_ProgressTag = 0;
//  m_IterationTag = 0;
//  m_AbortTag = 0;
//  
//  // Create a series of commands
//  if (m_Process)
//    {
//    m_StartFilterCommand =      CommandType::New();
//    m_EndFilterCommand =        CommandType::New();
//    m_ProgressFilterCommand =   CommandType::New();
//    m_IterationFilterCommand =  CommandType::New();
//    m_AbortFilterCommand =      CommandType::New();
//    
//    // Assign the callbacks
//    m_StartFilterCommand->SetCallbackFunction(this,
//                                        &SimpleFilterWatcher::StartFilter);
//    m_EndFilterCommand->SetCallbackFunction(this,
//                                        &SimpleFilterWatcher::EndFilter);
//    m_ProgressFilterCommand->SetCallbackFunction(this,
//                                        &SimpleFilterWatcher::ShowProgress);
//    m_IterationFilterCommand->SetCallbackFunction(this,
//                                        &SimpleFilterWatcher::ShowIteration);
//    m_AbortFilterCommand->SetCallbackFunction(this,
//                                        &SimpleFilterWatcher::ShowAbort);
//
//
//    // Add the commands as observers
//    m_StartTag = m_Process->AddObserver(StartEvent(), m_StartFilterCommand);
//    m_EndTag = m_Process->AddObserver(EndEvent(), m_EndFilterCommand);
//    m_ProgressTag
//      = m_Process->AddObserver(ProgressEvent(), m_ProgressFilterCommand);
//    m_IterationTag
//      = m_Process->AddObserver(IterationEvent(), m_IterationFilterCommand);
//    m_AbortTag = m_Process->AddObserver(AbortEvent(), m_AbortFilterCommand);
//    }
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
  std::cout << "Progress" << std::endl;
}
void SimpleSubjectWatcher::ShowIteration()
{
  std::cout << "Iteration" << std::endl;
}
void SimpleSubjectWatcher::ShowAbort()
{
  std::cout << "Abort" << std::endl;
}
void SimpleSubjectWatcher::ShowAnonymization(Subject *caller, const Event &evt)
{
  const AnonymizeEvent &ae = dynamic_cast<const AnonymizeEvent&>(evt);
  std::cout << "AnonymizeEvent: " << ae.GetTag() << std::endl;
}

void SimpleSubjectWatcher::TestAbortOn()
{
  m_TestAbort = true;
}
void SimpleSubjectWatcher::TestAbortOff()
{
  m_TestAbort = false;
}


} // end namespace gdcm
