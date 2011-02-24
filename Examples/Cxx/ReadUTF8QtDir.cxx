/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library

  Copyright (c) 2006-2011 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
/*
 * http://doc.qt.nokia.com/latest/qdir.html#navigation-and-directory-operations
 */

#include "gdcmReader.h"
#include "gdcmDirectory.h"

#include <QDir>
#include <QString>

#include <string>

static void TestBothFuncs(const char *info , const char *ba_str)
{
  std::ifstream is( ba_str );
  if( is.is_open() )
    {
    std::cout << info << " is_open: " << ba_str << std::endl;
    }
  gdcm::Reader reader;
  reader.SetFileName( ba_str );
  if( reader.CanRead() == true )
    {
    std::cout << info << " CanRead:" << ba_str << std::endl;
    }
}

static void scanFolder(const char dirname[])
{
  gdcm::Directory dir;
  unsigned int nfiles = dir.Load( dirname, true );
  const gdcm::Directory::FilenamesType &filenames = dir.GetFilenames();

  for( unsigned int i = 0; i < nfiles; ++i )
    {
    const char *ba_str = filenames[i].c_str();
    TestBothFuncs("GDCM",ba_str);
    }
}

static void scanFolderQt(QDir const &dir, QStringList& files)
{
  QFileInfoList children = dir.entryInfoList(QDir::AllEntries|QDir::NoDotAndDotDot);
  //std::cerr << "D: Found #: " << children.count() << std::endl;
  for ( int i=0; i<children.count(); i++ ) {
    QFileInfo file = children.at(i);
    if ( file.isDir() == true ) {
      scanFolderQt(QDir(file.absoluteFilePath()), files);
      continue;
    }
    //std::cerr << "D: QString: " << file.absoluteFilePath().toStdString() << std::endl;
    // QString
    std::string str = file.absoluteFilePath().toStdString();
    const char *ba_str1 = str.c_str();
    TestBothFuncs("QString", ba_str1);
    // Now try explicit UTF-8
    QByteArray bautf8 = file.absoluteFilePath().toUtf8();
    const char *ba_str2 = bautf8.constData();
    //std::cout << "D: UTF-8 istream: " << ba_str << std::endl;
    TestBothFuncs("UTF8", ba_str2);
    }
}

int main(int argc, char *argv[])
{
  if( argc < 2 )
    {
    std::cerr << argv[0] << " dir " << std::endl;
    return 1;
    }

  const char *dirname = argv[1];
  scanFolder( dirname );

  QDir dir( QString::fromUtf8(dirname) );
  QStringList files;
  scanFolderQt( dir, files);

  return 0;
}
