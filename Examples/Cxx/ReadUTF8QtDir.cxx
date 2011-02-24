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

static void scanFolder(const char dirname[] )
{
  gdcm::Directory dir;
  unsigned int nfiles = dir.Load( dirname, true );
  gdcm::Directory::FilenamesType filenames = dir.GetFilenames();

  for( unsigned int i = 0; i < nfiles; ++i )
    {
    gdcm::Reader reader;
    const char *ba_str = filenames[i].c_str();
    reader.SetFileName( ba_str );
    if( reader.CanRead() == true )
      {
      std::cout << ba_str << std::endl;
      }
    }
}

static void scanFolderQt(QDir const &dir, QStringList& files)
{
  QFileInfoList children = dir.entryInfoList(QDir::AllEntries|QDir::NoDotAndDotDot);
  std::cout << "Found #: " << children.count() << std::endl;
  for ( int i=0; i<children.count(); i++ ) {
    QFileInfo file = children.at(i);
    if ( file.isDir() == true ) {
      scanFolderQt(QDir(file.absoluteFilePath()), files);
      continue;
    }
    gdcm::Reader reader;
    QByteArray ba = file.absoluteFilePath().toUtf8();
    const char *ba_str = ba.constData();
    std::cout << "istream: " << ba_str << std::endl;
    std::ifstream is( ba_str );
    if( is.is_open() )
      {
      std::cout << "istream: " << ba_str << std::endl;
      }
    reader.SetFileName(file.absoluteFilePath().toUtf8().constData());
    if ( reader.CanRead() == true ) {
      files.append(file.absoluteFilePath());
      std::cout << ba.constData() << std::endl;
    }
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

  QDir dir( dirname );
  QStringList files;
  scanFolderQt( dir, files);

  return 0;
}
