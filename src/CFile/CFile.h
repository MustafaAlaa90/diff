/*--------------------------------------------------------------------------------
Copyright (C) 2021 - Mustafa Ala
---------------------------------------------------------------------------------*/

#ifndef CFILE_H_
#define CFILE_H_


#include <iostream>
#include <fstream>



/*! \brief Specifies the file open mode
 *
 * This enumeration specifies how to open a file
 * using the CFile::Open method.
 *
 */
typedef enum
{
  //! No file mode
  fmInvalidMode  = 0x00,
  //! Open file for reading
  fmRead      = 0x01,
  //! Open file for writing
  fmWrite      = 0x02,
  //! Open for appending
  fmAppend  = 0x06
} FileMode;

typedef enum
{
  //Any file
  fftAny = 0x00,
  // File
  fftFile = 0x01,
  // Directory
  fftDirectory = 0x02
} FindFileType;

/*! \brief Specifies how to seek for the CFile::Seek method
 *
 * This enum specifies the way to seek in the CFile::Seek method.
 *
 */
typedef enum
{
  //! Seek from file start
  fssFileStart = 0,
  //! Seek from file end
  fssFileEnd = 2,
  //! Seek from the current position
  fssCurrent = 1
} FileSeekStart;

class CFile : public std::fstream
{
public:
  // Construction / Destruction
  /*! \brief Creates an empty CFile class
   *
   * This method constructs an empty CFile class.
   *
   */
  CFile();

  /*! \brief Destroys the CFile class
   *
   * This method destructs the CFile class and closes a possibly
   * open file.
   *
   */
  virtual ~CFile();

  /*! \brief Opens the specified file using the specified mode.
   *
   * This method opens the specified file in the specified mode.
   *
   * \param lpszFile specifies a relative file name.
   * \param openFlags specifies the mode in which the file must be opened.
   *
   * \return The function returns true if successful or false if it
   *      failed.
   *
   * \pre The instance must not already have a file open.
   *
   */
  //bool Open(const std::string& fileNameURL, const unsigned long int openFlags);

  /*! \brief Opens the specified file using the specified mode.
   *
   * This method opens the specified file in the specified mode.
   *
   * \param lpszFile specifies a relative file name.
   * \param fileMode specifies the mode in which the file must be opened.
   *
   * \return The function returns true if successful or false if it
   *      failed.
   *
   * \pre The instance must not already have a file open.
   *
   */
  bool Open( const std::string& fileNameURL, const FileMode& fileMode );

  /**
   * 'Open' methods to use when file name is already known
   */
  //bool Open(const unsigned long int openFlags);
  //bool Open(const FileMode& fileMode);

  /*! \brief Closes an opened file.
   *
   * Calling this method on a CFile object causes it to close the file
   * it has opened. Closing the file causes the file buffers to be flushed
   * and the file to be unlocked.
   *
   * \return The return value is true if the method succeeds.
   */
  bool Close();

  /*! \brief Writes the specified number of bytes from the file.
   *
   * This method copies the given memory block into the file buffers of the
   * operating system for storage. You can safely modify the given buffer
   * after this call returns.
   *
   * \param pBuffer is the pointer, which is to write.
   * \param ui32Size specifies the number of bytes to write.
   *
   * \return The return value is the number of bytes written or -1
   *    if the function fails.
   *
   * \pre pBuffer must point to a valid (non-null) memory location and
   *    the CFile instance must have an open file for writing (fmWrite or fmAppend)
   *
   */
  unsigned long int Write( const void* pBuffer, const unsigned long int ui32Size );

  /*!  \brief Returns the size of the file.
   *
   * The returned file size is determined from the operating system.
   *
   * \return The return value is the size of the file.
   *
   * \pre The CFile instance must have an open file.
   *
   */
  unsigned long int GetFileSize() const;

  /*! \brief Flushes the buffers associated with this class
   *
   * If the underlying operating system buffers file I/O, then this function
   * can be used to force committing these buffers.
   *
   */
  void Flush();

  /*! \brief Returns true if a file is opened
   *
   * This method checks if the instance manages a file and returns
   * true if it has an opened file.
   *
   * \return The return value is true if the CFile instance has an
   * open file, or false if it hasn't.
   *
   */
  bool IsValid() const;

  /*! \brief Returns name of the file
    *
    * This method returns name of the file opened
    *
    * \return The return value is reference to file name.
    *
    */
  const std::string& GetFileName() const;

  /*! \brief Reads the specified number of bytes from the file.
   *
   * You must allocate a memory buffer to read the file data into. This memory
   * buffer is given as the first parameter
   *
   * \param pBuffer is the pointer, where to read the data into.
   * \param ui32Size specifies the number of bytes to read.
   *
   * \return The return value is the number of bytes read or -1
   *    if the function fails.
   *
   * \pre pBuffer must point to a valid (non-null) memory location and
   *    the CFile instance must have an open file for reading.
   */
  unsigned long int Read( void* pBuffer, const unsigned long int ui32Size );

  /*! \brief Sets the file pointer to a certain byte within the file
   *
   * This function sets the file pointer to the specified byte.
   *
   * \param i32Position specifies the position to move to / by
   * \param fssMode specifies the seek mode
   *
   * \return The return value is true if successful.
   */
  bool Seek( const long int i32Position, const FileSeekStart& fssMode = ::fssCurrent );

private:

  //! \internal Open flags of the file
  FileMode  m_fileMode;
  //! \internal Name of the file
  std::string m_fileName;
  unsigned long int m_fileSize;
  FindFileType m_fileType;
};

#endif /* CFILE_H_ */
