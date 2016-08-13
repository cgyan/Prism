/*
 * SharedData.h
 * v1
 *
 *  Created on: Jul 10, 2013
 *      Author: iainhemstock
 */

#ifndef PRISM_SHAREDDATA_H_
#define PRISM_SHAREDDATA_H_

namespace prism {

class SharedData {
private:
	int m_refCount;
	bool m_shareable;

public:
	SharedData();
	SharedData(const SharedData & copy);
	virtual ~SharedData() = 0;

	void 			decRef();
	void 			incRef();
	const bool 		isShareable() const;
	const bool 		isShared() const;
	const int 		refCount() const;
	void 			setUnshareable();
	SharedData & 	operator=(const SharedData & rhs);
};

}


#endif /* PRISM_SHAREDDATA_H_ */
