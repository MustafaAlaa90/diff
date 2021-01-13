/*--------------------------------------------------------------------------------
Copyright (C) 2021 - Mustafa Ala
---------------------------------------------------------------------------------*/

#include "CFile.h"
#include <cassert>

namespace SCL
{

// ----------------------------------------------------------------------------
CFile::CFile()
  : m_fileMode ( FileMode::fmInvalidMode )
  , m_fileName()
  , m_fileSize ( 0 )
  , m_fileType ( FindFileType::fftAny )
{

}

// ----------------------------------------------------------------------------
CFile::~CFile()
{
  if ( IsValid() )
  {
    Close();
    clear();
  }
}

// ----------------------------------------------------------------------------
bool CFile::IsValid() const
{
  return is_open();
}

// ----------------------------------------------------------------------------
bool CFile::Open( const std::string& fileNameURL, const FileMode& fileMode )
{

  //fileNameURL is not the absolute path ?

  // 1. File mode must be specified
  assert ( !fileNameURL.empty() && "File name must be specified!" );
  // 2. No file must be open
  assert ( !IsValid() && "Opened file must first be closed before opening another one!" );

  bool bRetVal = false;
  clear();

  switch ( fileMode )
  {
  case fmRead:
    open( fileNameURL, std::ios::in );
    break;
  case fmWrite:
    open( fileNameURL, std::ios::out | std::ios::binary );
    break;
  case fmAppend:
    open( fileNameURL, std::ios::out | std::ios::app | std::ios::binary );
    break;
  case fmInvalidMode:
  default:
    break;
  }

  if ( IsValid() )
  {
    m_fileName = fileNameURL;
    m_fileMode = fileMode;

    bRetVal = true;
  }

  return bRetVal;
}


// ----------------------------------------------------------------------------
bool CFile::Close()
{
  close();
  return !IsValid();
}

// ----------------------------------------------------------------------------
unsigned long int CFile::Write( const void* pBuffer, const unsigned long int ui32Size )
{
  // 1. The file must be opened
  assert( IsValid() && "You must have a file open for writing !" );
  // 2. The file must be open in write mode
  assert( ( m_fileMode == fmWrite || m_fileMode == fmAppend ) && "The file must be in write mode !" );
  // 3. The buffer must be valid
  assert( 0 != pBuffer && "A valid buffer pointer must be specified !" );

  unsigned long int ui32written = 0 ;

  if ( IsValid() && ( m_fileMode == fmWrite || m_fileMode == fmAppend ) && 0 != pBuffer )
  {
    // Write the buffer to file
    write( ( const char* )( pBuffer ), ui32Size );

    if ( good() )
    {
      ui32written = ui32Size;

    }
  }

  return ui32written;
}

// ----------------------------------------------------------------------------
unsigned long int CFile::GetFileSize() const
{
  unsigned long int fileSize;

  if ( 0 != m_fileSize )
  {
    fileSize = m_fileSize;
  }
  else if ( IsValid() )
  {

    std::streampos fSize = 0;
    CFile tmpFile;
    tmpFile.open( m_fileName, std::ios::in | std::ios::binary ); //opening the same file opened could potentially lead to data race
    tmpFile.seekg ( 0 , std::ios::end );
    fSize = tmpFile.tellg();
    tmpFile.close();

    //static_assert(sizeof(std::streamsize) <= sizeof(unsigned long int), "Type mismatch due to size!"); // TODO size is bigger than unsigned long int

    fileSize = fSize;
  }

  return fileSize;

}

// ----------------------------------------------------------------------------
void CFile::Flush()
{
  flush(); //Writes uncommitted changes to the underlying output sequence
}

// ----------------------------------------------------------------------------
const std::string& CFile::GetFileName() const
{
  return m_fileName;
}
// ----------------------------------------------------------------------------
unsigned long int CFile::Read( void* pBuffer, const unsigned long int ui32Size )
{
  // 1. The file must be opened
  assert( IsValid() && "You must have a file open for writing !" );
  // 2. The file must be open in write mode
  assert( m_fileMode == fmRead && "The file must be in read mode !" );
  // 3. The buffer must be valid
  assert( 0 != pBuffer && "A valid buffer pointer must be specified !" );

  unsigned long int ui32sizeRead = 0 ;

  if ( IsValid() && ( m_fileMode == fmRead ) && 0 != pBuffer )
  {
    // Write the buffer to file
    read( reinterpret_cast<char*> ( pBuffer ), ui32Size );
    if ( good() )
    {
      ui32sizeRead = ui32Size;

    }
  }

  return ui32sizeRead;
}

// ----------------------------------------------------------------------------
bool CFile::Seek( const long int i32Position, const FileSeekStart& fssMode )
{

  // 1. The file must be opened
  assert( IsValid() && "A file must be opened !" );

  bool bRetVal = false;

  std::ios_base::seekdir dir;

  switch ( fssMode )
  {
  case fssFileStart:
    dir = beg;
    break;
  case fssFileEnd:
    dir = end;
    break;
  case fssCurrent:
  default:
    dir = cur;
    break;
  }

  switch ( m_fileMode )
  {
  case fmRead:
    seekg ( i32Position , dir );
    break;
  case fmWrite:
  case fmAppend:
    seekp ( i32Position , dir );
    break;
  case fmInvalidMode:
  default:
    break;
  }

  bRetVal = good();

  return bRetVal;
}
} // SCL
