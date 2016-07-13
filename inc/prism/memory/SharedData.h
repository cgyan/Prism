/*
 * SharedData.h
 * v0.1
 *
 *  Created on: Jul 10, 2013
 *      Author: iainhemstock
 */

#ifndef PRISM_SHAREDDATA_H_
#define PRISM_SHAREDDATA_H_

// todo comment each method in this class

namespace prism {

class SharedData {
private:
	int m_refCount;
	bool m_shareable;

public:
	/**
	 *
	 */
	SharedData() : m_refCount(0), m_shareable(true) {}

	/**
	 *
	 */
	SharedData(const SharedData & copy) : m_refCount(0), m_shareable(true) {}

	/**
	 *
	 */
	SharedData & operator=(const SharedData & rhs) { return *this; }

	/**
	 *
	 */
	virtual ~SharedData() {}

	/**
	 *
	 */
	void incRef() { ++m_refCount; }

	/**
	 *
	 */
	void decRef() { if (--m_refCount == 0) delete this; } // deletes the SharedData subclass

	/**
	 *
	 */
	const int refCount() const { return m_refCount; }

	/**
	 *
	 */
	void setUnshareable() { m_shareable = false; }

	/**
	 *
	 */
	const bool isShareable() const { return m_shareable; }

	/**
	 *
	 */
	const bool isShared() const { return m_refCount > 1; }
};

}


#endif /* PRISM_SHAREDDATA_H_ */
