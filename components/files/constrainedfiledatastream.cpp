/*
  OpenMW - The completely unofficial reimplementation of Morrowind
  Copyright (C) 2008-2010  Nicolay Korslund
  Email: < korslund@gmail.com >
  WWW: http://openmw.sourceforge.net/

  This file (bsa_file.cpp) is part of the OpenMW package.

  OpenMW is distributed as free software: you can redistribute it
  and/or modify it under the terms of the GNU General Public License
  version 3, as published by the Free Software Foundation.

  This program is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  General Public License for more details.

  You should have received a copy of the GNU General Public License
  version 3 along with this program. If not, see
  http://www.gnu.org/licenses/ .

 */

#include "constrainedfiledatastream.hpp"

#include <stdexcept>
#include <cassert>

#define FORCE_POSIX

#include <fcntl.h>
#if defined (_MSC_VER)
#include <io.h>
#endif

namespace {

class LowLevelFile
{
public:

	LowLevelFile ();
	~LowLevelFile ();

	void open (char const * filename);
	void close ();

	size_t size ();

	void seek (size_t Position);
	size_t tell ();

	size_t read (void * data, size_t size);

private:
	int mHandle;
};

class ConstrainedDataStream : public Ogre::DataStream {
public:

	static const size_t sBufferSize = 4096; // somewhat arbitrary though 64KB buffers didn't seem to improve performance any
	static const size_t sBufferThreshold = 1024; // reads larger than this bypass buffering as cost of memcpy outweighs cost of system call

    ConstrainedDataStream(const Ogre::String &fname, size_t start, size_t length)
	{
		mFile.open (fname.c_str ());
		mSize  = length != 0xFFFFFFFF ? length : mFile.size () - start;

		mPos    = 0;
		mOrigin = start;
		mExtent = start + mSize;

		mBufferOrigin = 0;
		mBufferExtent = 0;
	}
		

	size_t read(void* buf, size_t count)
	{
		assert (mPos <= mSize);

		uint8_t * out = reinterpret_cast <uint8_t *> (buf);

		size_t posBeg = mOrigin + mPos;
		size_t posEnd = posBeg + count;

		if (posEnd > mExtent)
			posEnd = mExtent;

		size_t posCur = posBeg;

		while (posCur != posEnd)
		{
			size_t readLeft = posEnd - posCur;

			if (posCur < mBufferOrigin || posCur >= mBufferExtent)
			{
				if (readLeft >= sBufferThreshold || (posCur == mOrigin && posEnd == mExtent))
				{
					assert (mFile.tell () == mBufferExtent);

					if (posCur != mBufferExtent)
						mFile.seek (posCur);

					posCur += mFile.read (out, readLeft);

					mBufferOrigin = mBufferExtent = posCur;

					mPos = posCur - mOrigin;

					return posCur - posBeg;
				}
				else
				{
					size_t newBufferOrigin;

					if ((posCur < mBufferOrigin) && (mBufferOrigin - posCur < sBufferSize))
						newBufferOrigin = std::max (mOrigin, mBufferOrigin > sBufferSize ? mBufferOrigin - sBufferSize : 0);
					else
						newBufferOrigin = posCur;

					fill (newBufferOrigin);
				}
			}

			size_t xfer = std::min (readLeft, mBufferExtent - posCur);

			memcpy (out, mBuffer + (posCur - mBufferOrigin), xfer);

			posCur += xfer;
			out += xfer;
		}

		count = posEnd - posBeg;
		mPos += count;
		return count;
	}

    void skip(long count)
    {
		assert (mPos <= mSize);

        if((count >= 0 && (size_t)count <= mSize-mPos) ||
           (count < 0 && (size_t)-count <= mPos))
			mPos += count;
    }

    void seek(size_t pos)
    {
		assert (mPos <= mSize);

        if (pos < mSize)
			mPos = pos;
    }

    virtual size_t tell() const
    {
		assert (mPos <= mSize);

		return mPos;
	}

    virtual bool eof() const
    {
		assert (mPos <= mSize);

		return mPos == mSize;
	}

    virtual void close()
    {
		mFile.close();
	}

private:

	void fill (size_t newOrigin)
	{
		assert (mFile.tell () == mBufferExtent);

		size_t newExtent = newOrigin + sBufferSize;

		if (newExtent > mExtent)
			newExtent = mExtent;

		size_t oldExtent = mBufferExtent;

		if (newOrigin != oldExtent)
			mFile.seek (newOrigin);

		mBufferOrigin = mBufferExtent = newOrigin;

		size_t amountRequested = newExtent - newOrigin;

		size_t amountRead = mFile.read (mBuffer, amountRequested);

		if (amountRead != amountRequested)
			throw std::runtime_error ("An unexpected condition occurred while reading from a file.");

		mBufferExtent = newExtent;
	}

	LowLevelFile mFile;

	size_t mOrigin;
	size_t mExtent;
	size_t mPos;

	uint8_t mBuffer [sBufferSize];
	size_t mBufferOrigin;
	size_t mBufferExtent;
};

} // end of unnamed namespace

Ogre::DataStreamPtr openConstrainedFileDataStream (char const * filename, size_t offset, size_t length)
{
	return Ogre::DataStreamPtr(new ConstrainedDataStream(filename, offset, length));
}

/*
 *
 *	Implementation of LowLevelFile methods
 *
 */

LowLevelFile::LowLevelFile ()
{
	mHandle = -1;
}

LowLevelFile::~LowLevelFile ()
{
	if (mHandle != -1)
		_close (mHandle);
}

void LowLevelFile::open (char const * filename)
{
	assert (mHandle == -1);

#ifdef _MSC_VER
	static const int openFlags = O_RDONLY | O_BINARY;
#else
	static const int openFlags = O_RDONLY;
#endif

	mHandle = _open (filename, openFlags, 0);

	if (mHandle == -1)
	{
		std::ostringstream os;
		os << "Failed to open '" << filename << "' for reading.";
		throw std::runtime_error (os.str ());
	}
}

void LowLevelFile::close ()
{
	assert (mHandle != -1);

	_close (mHandle);

	mHandle = -1;
}

size_t LowLevelFile::size ()
{
	assert (mHandle != -1);

	size_t oldPosition = _tell (mHandle);

	if (oldPosition == size_t (-1))
		throw std::runtime_error ("A query operation on a file failed.");

	size_t Size = _lseek (mHandle, 0, SEEK_END);

	if (Size == size_t (-1))
		throw std::runtime_error ("A query operation on a file failed.");

	if (_lseek (mHandle, oldPosition, SEEK_SET) == -1)
		throw std::runtime_error ("A query operation on a file failed.");

	return Size;
}

void LowLevelFile::seek (size_t Position)
{
	assert (mHandle != -1);

	if (_lseek (mHandle, Position, SEEK_SET) == -1)
		throw std::runtime_error ("A seek operation on a file failed.");
}

size_t LowLevelFile::tell ()
{
	assert (mHandle != -1);

	size_t Position = _tell (mHandle);

	if (Position == size_t (-1))
		throw std::runtime_error ("A query operation on a file failed.");

	return Position;
}

size_t LowLevelFile::read (void * data, size_t size)
{
	assert (mHandle != -1);

	int amount = _read (mHandle, data, size);

	if (amount == -1)
		throw std::runtime_error ("A read operation on a file failed.");

	return amount;
}
