/*
 * iterator_tags.h
 * v1
 *
 *  Created on: Sep 25, 2016
 *      Author: iainhemstock
 */

#ifndef PRISM_ITERATOR_TAGS_H_
#define PRISM_ITERATOR_TAGS_H_

namespace prism {

/****************************************************************************************************************
 * Tags to describe what kind of iterator a particular iterator type is. They are used in the container algorithms
 * to determine which is the best algorithm to use for that particular type of iterator.
 ****************************************************************************************************************/
struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag : public input_iterator_tag {};
struct bidirectional_iterator_tag : public forward_iterator_tag {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};

} // end namespace prism



#endif /* PRISM_ITERATOR_TAGS_H_ */
