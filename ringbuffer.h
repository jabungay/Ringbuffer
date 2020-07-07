/*
 * ringbuffer.h - Create ring buffers of any size and type
 *
 * Created 20200707
 *
 * Copyright (c) Jonathan Bungay 2020
 *
 */

#ifndef _RINGBUFFER_H
#define _RINGBUFFER_H

template <class T>
class Ringbuffer
{
private:
  T *pData;             // Ptr to data array
  unsigned int uBufLen; // Length of the ring buffer
  unsigned int uR;      // Current read index
  unsigned int uW;      // Current write index
  bool bOverflowed;     // Is the buffer currently overflowed (read ptr > write ptr)
  bool bEverOverflowed; // Has the buffer ever overflowed
public:
  Ringbuffer(int len);
  ~Ringbuffer();

  bool read(T* data);  // Write data to param ptr
  bool write(T* data);

  bool bDataAvailable() { return !(uR == uW);     } // If read and write pointers are equal, there is no data in the buffer
  bool isOverflowed()   { return bOverflowed;     }
  bool everOverflowed() { return bEverOverflowed; }


};

// Class constructor
template<class T>
Ringbuffer<T>::Ringbuffer(int len) : uBufLen(len), uR(0), uW(0), bOverflowed(false), bEverOverflowed(false)
{
  pData = new T[len];
}


template<class T>
bool Ringbuffer<T>::read(T* data)
{
  if (!bDataAvailable()) { return false; }

  *data = pData[uR];
  uR++;

  if (uR > uW)
  {
    bOverflowed = true;
    bEverOverflowed = true;
    return false;
  }

  return true;
}

template<class T>
bool Ringbuffer<T>::write(T *data)  // Pass by reference to not take up excessive memory
{
  pData[uW] = *data;
  uW++;

  if (uR < uW && bOverflowed) { bOverflowed == false; } // Clear overflow flag if overflow gets fixed

  return true;
}

// Class destructor
template<class T>
Ringbuffer<T>::~Ringbuffer()
{
  delete[] pData;
}

#endif // _RINGBUFFER_H
