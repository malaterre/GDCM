int TestWriter2(int argc, char *argv[])
{
  const char *filename = argv[1];
  const char *outfilename = argv[2];

  Reader reader;
  reader.SetFileName( filename );
  if ( !reader.Read() )
    {
    std::cerr << "Failed to read: " << filename << std::endl;
    return 1;
    }

  
  Writer writer;
  writer.SetFileName( outfilename );
  writer.SetFile( reader.GetFile() );
  if( !writer.Write() )
    {
    std::cerr << "Failed to write: " << outfilename << std::endl;
    return 1;
    }
}
