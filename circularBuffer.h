#pragma once
#ifndef _CIRCULARBUFFER_H
#define _CIRCULARBUFFER_H

#include <cstdlib>

/**
 * @brief One of the two possible writing modes to a \ref circularBuffer.
*/
typedef enum _CIRCULARBUFFER_OPMODE {
	CBUF_OVERWRITE = 0, /*! Once the buffer is full, the most stale data is deleted to make way for the newest data.*/
	CBUF_FILL	  = 1  /*! Once the buffer is full, it will not allow further writing to the buffer until data is removed.*/
}circularBufferWriteMode;

/**
 * @brief Circular buffer class containing the data buffer itself in addition to metadata about it.
 * @tparam T Typename T is used to set the data type of the elements of the data buffer.
*/
template <typename T>
class circularBuffer {
private:
	T* buffer; /*! Data buffer*/
	unsigned long capacity; /*! Buffer's total capacity.*/
	unsigned long length; /*! Current number of valid data points in the buffer.*/
	circularBufferWriteMode writeMode; /*! Writing mode of the buffer. The possible modes listed in \ref circularBufferWriteMode.*/
	unsigned long rdPtr; /*! Current relative location of the read pointer in the buffer relative to the buffer start address.*/
	unsigned long rdPtrTemp; /*! Backup of current relative location of the read pointer for reset.*/
	unsigned long rdCounter; /*! Number of datapoints that have been read.*/
	unsigned long wrPtr; /*! Current relative location of the write pointer in the buffer relative to the buffer start address.*/

	void incrementPtr(unsigned long& ptr)
	{
		if (capacity - (ptr) > 1) {
			ptr++;
		}
		else {
			ptr = 0;
		}
	}

public:
	/**
	 * @brief Constructor to initialize the circular buffer object.
	 * @param bufferCapacity Total capacity/number of elements of the buffer.
	 * @param bufferWriteMode Write mode of the buffer. Possible modes listed in \ref circularBufferWriteMode.
	*/
	circularBuffer(unsigned long bufferCapacity, circularBufferWriteMode bufferWriteMode)
	{
		buffer		= (T*) malloc(sizeof(T) * bufferCapacity);
		capacity	= bufferCapacity;
		length		= 0;
		writeMode	= bufferWriteMode;
		rdPtr		= 0;
		rdPtrTemp	= 0;
		rdCounter	= 0;
		wrPtr		= 0;
	}

	/**
	 * @brief Returns the total number of elements/capacity of the circular buffer.
	 * @return Total capacity of the circular buffer
	*/
	inline unsigned long getCapacity()
	{
		return capacity;
	}
	
	/**
	 * @brief Returns the number of elements/length of data currently being stored in the circular buffer.
	 * @return Current length of data/number of elements in the buffer.
	*/
	inline unsigned long getLength()
	{
		return length;
	}

	/**
	 * @brief Returns 1 if the buffer is empty.
	 * @return Returns 1 if the buffer is empty, 0 otherwise.
	*/
	inline bool isEmpty() {
		return (length == 0) ? 1 : 0;
	}

	/**
	 * @brief Inserts a data item into the buffer if it isn't at capacity. If it is, it can overwrite data if the buffer was initialized with \ref CBUF_OVERWRITE write mode.
	 * @param dataPtr Pointer to the data that should be copied into the circular buffer.
	 * @return Returns 1 if successul, and 0 if not.
	*/
	int insertData(const T* dataPtr)
	{
		if (length == capacity) {
			if (writeMode == CBUF_FILL) {
				return 0;
			}
			incrementPtr(rdPtrTemp);
			if (rdCounter == 0) {
				rdPtr = rdPtrTemp;
			}
		}
		else {
			length++;
		}
		buffer[wrPtr] = *dataPtr;
		incrementPtr(wrPtr);
		return 1;
	}

	/**
	 * @brief Copies a data point from the buffer and increments the internal read pointer without deleting the data.
	 * It starts by copying the oldest data in the buffer at returns 1. In subsequent calls, it will copy more recent data until all data is copied.
	 * Then, it will reset the internal read pointer to the oldest data point and return 0.
	 * @param dataPtr Pointer to the location to which you want the data point to be copied.
	 * @return Returns 1 if more data can be copied. Returns 0 if no more data can be uniquely copied. Returns -1 if the buffer is empty.
	*/
	int readData(T* dataPtr)
	{
		if (isEmpty()) {
			return -1;
		}
		*dataPtr = buffer[rdPtr];
		if (++rdCounter == length) {
			resetRead();
			return 0;
		}
		else {
			incrementPtr(rdPtr);
			return 1;
		}
	}

	/**
	 * @brief Resets the internal read pointer back to the oldest data point and internal read counter.
	*/
	inline void resetRead()
	{
		rdPtr = rdPtrTemp;
		rdCounter = 0;
	}

	/**
	 * @brief Copies a data point from the buffer and removes it from the buffer. Also increments the internal read pointer.
	 * It starts by copying the oldest data in the buffer at returns 1. In subsequent calls, it will copy more recent data until all data is copied. At this point, it returns 0.
	 * @param dataPtr Pointer to the location to which you want the data point to be copied.
	 * @return Returns 1 if more data can be copied and then deleted. Returns 0 if all data has been copied and deleted. Returns -1 if the buffer is empty. Returns -2 if a no-delete read operation is in progress.
	*/
	int readRemoveData(T* dataPtr)
	{
		if (isEmpty()) {
			return -1;
		}
		else if (rdPtr != rdPtrTemp) {
			return -2;
		}
		*dataPtr == buffer[rdPtr];
		incrementPtr(rdPtr);
		rdPtrTemp = rdPtr;
		if (--length == 0) {
			return 0;
		}
		return 1;
	}

	~circularBuffer()
	{
		free((void*)buffer);
	}
};

#endif // !_CIRCULARBUFFER_H

