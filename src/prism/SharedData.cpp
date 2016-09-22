/*
 * SharedData.cpp
 * v1
 *
 *  Created on: Aug 13, 2016
 *      Author: iainhemstock
 */
// todo comment each method in this class
#include <prism/SharedData>

namespace prism {

/**
 *
 */
SharedData::SharedData()
: m_refCount(0), m_shareable(true)
{}

/**
 *
 */
SharedData::SharedData(const SharedData & copy)
: m_refCount(0), m_shareable(true)
{}

/**
 *
 */
SharedData::~SharedData()
{}

/**
 *
 */
void SharedData::decRef()
{ --m_refCount; }

/**
 *
 */
void SharedData::incRef()
{ ++m_refCount; }

/**
 *
 */
const bool SharedData::isShareable() const
{ return m_shareable; }

/**
 *
 */
const bool SharedData::isShared() const
{ return m_refCount > 1; }

/**
 *
 */
const int SharedData::refCount() const
{ return m_refCount; }

/**
 *
 */
void SharedData::setUnshareable()
{ m_shareable = false; }

/**
 *
 */
SharedData & SharedData::operator=(const SharedData & rhs)
{ return *this; }

}


