/*
 * VectorTest.cpp
 * v1
 *
 *  Created on: Dec 1, 2016
 *      Author: iainhemstock
 *
 *  The tests in this file are broken up into nine categories:
 *  	Constructors/destructor/assignment
 *  	Iterators
 *  	Capacity
 *  	Element Access
 *  	Modifiers
 *  	Queries
 *  	Conversions
 *  	Allocator
 *  	Non Member Functions
 */

#include <gtest/gtest.h>
//#include <prism/h/development/Vector.h>

//todo: remove this
#include <iostream>
using namespace std;
//using namespace prism::beta;
// -------------------

namespace prism {
namespace test {

class VectorTest : public ::testing::Test {
public:

};

TEST_F(VectorTest, DefaultVectorIsEmpty) {
	EXPECT_TRUE(false);
}
//=============================================================================================
// Constructors/destructor/assignment
//=============================================================================================
/*
 * Test: Vector()
 */
TEST_F(VectorTest, default_ctor) {
  EXPECT_TRUE(false);

}

/*
 * Test: Vector(size,value=T())
 */
TEST_F(VectorTest, ctor_size_value) {
  EXPECT_TRUE(false);
}

/*
 * Test: Vector(Iter from, Iter to)
 */
TEST_F(VectorTest, ctor_range) {
  EXPECT_TRUE(false);
}

/*
 * Test: Vector(std::initializer_list<T> il)
 */
TEST_F(VectorTest, ctor_ilList) {
  EXPECT_TRUE(false);
}

/*
 * Test: Vector(Vector const &)
 */
TEST_F(VectorTest, ctor_copy) {
  EXPECT_TRUE(false);
}

/*
 * Test: Vector(Vector&&)
 */
TEST_F(VectorTest, ctor_move) {
  EXPECT_TRUE(false);
}

/*
 * Test: operator=(Vector const&)
 */
TEST_F(VectorTest, copy_assignment) {
  EXPECT_TRUE(false);
}

/*
 * Test: operator=(Vector&&)
 */
TEST_F(VectorTest, move_assignment) {
  EXPECT_TRUE(false);
}
//=============================================================================================
// Iterators
//=============================================================================================
/**
 * Test: Vector::begin()
 */
TEST_F(VectorTest, begin) {
	EXPECT_TRUE(false);
}

/**
 * Test: Vector::begin() const
 */
TEST_F(VectorTest, begin_const) {
	EXPECT_TRUE(false);
}

/**
 * Test: Vector::cbegin() const
 */
TEST_F(VectorTest, cbegin) {
	EXPECT_TRUE(false);
}

/**
 * Test: Vector::cend() const
 */
TEST_F(VectorTest, cend) {
	EXPECT_TRUE(false);
}

/**
 * Test: Vector::crbegin() const
 */
TEST_F(VectorTest, crbegin) {
	EXPECT_TRUE(false);
}

/**
 * Test: Vector::crend() const
 */
TEST_F(VectorTest, crend) {
	EXPECT_TRUE(false);
}

/**
 * Test: Vector::end()
 */
TEST_F(VectorTest, end) {
	EXPECT_TRUE(false);
}

/**
 * Test: Vector::end() const
 */
TEST_F(VectorTest, end_const) {
	EXPECT_TRUE(false);
}

/**
 * Test: Vector::rbegin()
 */
TEST_F(VectorTest, rbegin) {
	EXPECT_TRUE(false);
}

/**
 * Test: Vector::rbegin() const
 */
TEST_F(VectorTest, rbegin_const) {
	EXPECT_TRUE(false);
}

/**
 * Test: Vector::rend()
 */
TEST_F(VectorTest, rend) {
	EXPECT_TRUE(false);
}

/**
 * Test: Vector::rend() const
 */
TEST_F(VectorTest, rend_const) {
	EXPECT_TRUE(false);
}
//=============================================================================================
// Capacity
//=============================================================================================
/**
 * Test: Vector::capacity()
 */
TEST_F(VectorTest, capacity) {
	EXPECT_TRUE(false);
}

/**
 * Test: Vector::empty()
 */
TEST_F(VectorTest, empty) {
	EXPECT_TRUE(false);
}

/**
 * Test: Vector::reserve()
 */
TEST_F(VectorTest, reserve) {
	EXPECT_TRUE(false);
}

/**
 * Test: Vector::resize()
 */
TEST_F(VectorTest, resize) {
	EXPECT_TRUE(false);
}

/**
 * Test: Vector::size()
 */
TEST_F(VectorTest, size) {
	EXPECT_TRUE(false);
}

/**
 * Test: Vector::squeeze()
 */
TEST_F(VectorTest, squeeze) {
	EXPECT_TRUE(false);
}
//=============================================================================================
// Element access
//=============================================================================================
/**
 * Test: Vector::at()
 */
TEST_F(VectorTest, at) {
	EXPECT_TRUE(false);
}

/**
 * Test: Vector::at() const
 */
TEST_F(VectorTest, at_const) {
	EXPECT_TRUE(false);
}

/**
 * Test: Vector::back()
 */
TEST_F(VectorTest, back) {
	EXPECT_TRUE(false);
}

/**
 * Test: Vector::back() const
 */
TEST_F(VectorTest, back_const) {
	EXPECT_TRUE(false);
}

/**
 * Test: Vector::data()
 */
TEST_F(VectorTest, data) {
	EXPECT_TRUE(false);
}

/**
 * Test: Vector::data() const
 */
TEST_F(VectorTest, data_const) {
	EXPECT_TRUE(false);
}

/**
 * Test: Vector::cdata()
 */
TEST_F(VectorTest, cdata) {
	EXPECT_TRUE(false);
}

/**
 * Test: Vector::first()
 */
TEST_F(VectorTest, first) {
	EXPECT_TRUE(false);
}

/**
 * Test: Vector::first() const
 */
TEST_F(VectorTest, first_const) {
	EXPECT_TRUE(false);
}

/**
 * Test: Vector::front()
 */
TEST_F(VectorTest, front) {
	EXPECT_TRUE(false);
}

/**
 * Test: Vector::front() const
 */
TEST_F(VectorTest, front_const) {
	EXPECT_TRUE(false);
}

/**
 * Test: Vector::last()
 */
TEST_F(VectorTest, last) {
	EXPECT_TRUE(false);
}

/**
 * Test: Vector::last() const
 */
TEST_F(VectorTest, last_const) {
	EXPECT_TRUE(false);
}

/**
 * Test: Vector::mid()
 */
TEST_F(VectorTest, mid) {
	EXPECT_TRUE(false);
}

/**
 * Test: Vector::operator[]()
 */
TEST_F(VectorTest, operator_subscript) {
	EXPECT_TRUE(false);
}

/**
 * Test: Vector::operator[]() const
 */
TEST_F(VectorTest, operator_subscript_const) {
	EXPECT_TRUE(false);
}
//=============================================================================================
// Modifiers
//=============================================================================================
/**
 * Test: Vector::append(const T&)
 */
TEST_F(VectorTest, append_by_copy) {
	EXPECT_TRUE(false);
}

/**
 * Test: Vector::append(T&&)
 */
TEST_F(VectorTest, append_by_move) {
	EXPECT_TRUE(false);
}

/**
 * Test: Vector::clear()
 */
TEST_F(VectorTest, clear) {
	EXPECT_TRUE(false);
}

/**
 * Test: Vector::erase(Iter pos)
 */
TEST_F(VectorTest, erase_pos) {
	EXPECT_TRUE(false);
}

/**
 * Test: Vector::erase(Iter first, Iter last)
 */
TEST_F(VectorTest, erase_range) {
	EXPECT_TRUE(false);
}

/**
 * Test: Vector::fill()
 */
TEST_F(VectorTest, fill) {
	EXPECT_TRUE(false);
}

/**
 * Test: Vector::insert(const int, const T&)
 */
TEST_F(VectorTest, insert_value_at_index_by_copy) {
	EXPECT_TRUE(false);
}

/**
 * Test: Vector::insert(const int, T&&)
 */
TEST_F(VectorTest, insert_value_at_index_by_move) {
	EXPECT_TRUE(false);
}

/**
 * Test: Vector::insert(const int, const int, T&)
 */
TEST_F(VectorTest, insert_num_values_at_index_by_copy) {
	EXPECT_TRUE(false);
}

/**
 * Test: Vector::insert(Iter pos, T&)
 */
TEST_F(VectorTest, insert_value_at_pos_by_copy) {
	EXPECT_TRUE(false);
}

/**
 * Test: Vector::insert(Iter pos, T&&)
 */
TEST_F(VectorTest, insert_value_at_pos_by_move) {
	EXPECT_TRUE(false);
}

/**
 * Test: Vector::insert(Iter pos, const int, T&)
 */
TEST_F(VectorTest, insert_num_values_at_pos_by_copy) {
	EXPECT_TRUE(false);
}

/**
 * Test: Vector::insert(Iter pos, init_list)
 */
TEST_F(VectorTest, insert_init_list_values_at_pos) {
	EXPECT_TRUE(false);
}

/**
 * Test: Vector::insert(Iter pos, Iter first, Iter last)
 */
TEST_F(VectorTest, insert_range_at_pos) {
	EXPECT_TRUE(false);
}

/**
 * Test: Vector::pop_back()
 */
TEST_F(VectorTest, pop_back) {
	EXPECT_TRUE(false);
}

/**
 * Test: Vector::pop_front()
 */
TEST_F(VectorTest, pop_front) {
	EXPECT_TRUE(false);
}

/**
 * Test: Vector::prepend(const T&)
 */
TEST_F(VectorTest, prepend_by_copy) {
	EXPECT_TRUE(false);
}

/**
 * Test: Vector::prepend(T&&)
 */
TEST_F(VectorTest, prepend_by_move) {
	EXPECT_TRUE(false);
}

/**
 * Test: Vector::push_back(const T&)
 */
TEST_F(VectorTest, push_back_by_copy) {
	EXPECT_TRUE(false);
}

/**
 * Test: Vector::push_back(T&&)
 */
TEST_F(VectorTest, push_back_by_move) {
	EXPECT_TRUE(false);
}

/**
 * Test: Vector::push_front(const T&)
 */
TEST_F(VectorTest, push_front_by_copy) {
	EXPECT_TRUE(false);
}

/**
 * Test: Vector::push_front(T&&)
 */
TEST_F(VectorTest, push_front_by_move) {
	EXPECT_TRUE(false);
}

/**
 * Test: Vector::operator<<(const T&)
 */
TEST_F(VectorTest, operator_shift_left___append_value_by_copy) {
	EXPECT_TRUE(false);
}

/**
 * Test: Vector::operator+=(const T&)
 */
TEST_F(VectorTest, operator_plus_equals___append_value_by_copy) {
	EXPECT_TRUE(false);
}

/**
 * Test: Vector::operator<<(const Vector&)
 */
TEST_F(VectorTest, operator_shift_left___append_vector_by_copy) {
	EXPECT_TRUE(false);
}

/**
 * Test: Vector::operator+(const Vector&)
 */
TEST_F(VectorTest, operator_plus___append_vector_by_copy) {
	EXPECT_TRUE(false);
}

/**
 * Test: Vector::operator+=(const Vector&)
 */
TEST_F(VectorTest, operator_plus_equals___append_vector_by_copy) {
	EXPECT_TRUE(false);
}

/**
 * Test: Vector::remove(const int)
 */
TEST_F(VectorTest, remove_value_at_index) {
	EXPECT_TRUE(false);
}

/**
 * Test: Vector::remove(const int, const int)
 */
TEST_F(VectorTest, remove_num_values_at_index) {
	EXPECT_TRUE(false);
}

/**
 * Test: Vector::removeAll(const T&)
 */
TEST_F(VectorTest, remove_all_occurrences_of_value) {
	EXPECT_TRUE(false);
}

/**
 * Test: Vector::removeFirst()
 */
TEST_F(VectorTest, remove_first) {
	EXPECT_TRUE(false);
}

/**
 * Test: Vector::removeIf(Pred)
 */
TEST_F(VectorTest, remove_if_pred_true) {
	EXPECT_TRUE(false);
}

/**
 * Test: Vector::removeLast()
 */
TEST_F(VectorTest, remove_last) {
	EXPECT_TRUE(false);
}

/**
 * Test: Vector::replace(const int, const T&)
 */
TEST_F(VectorTest, replace_value_at_index_by_copy) {
	EXPECT_TRUE(false);
}

/**
 * Test: Vector::replace(const int, T&&)
 */
TEST_F(VectorTest, replace_value_at_index_by_move) {
	EXPECT_TRUE(false);
}

/**
 * Test: Vector::swap(Vector& rhs)
 */
TEST_F(VectorTest, swap_with_other_vector) {
	EXPECT_TRUE(false);
}

/**
 * Test: Vector::takeAt(index)
 */
TEST_F(VectorTest, take_at_index) {
	EXPECT_TRUE(false);
}

/**
 * Test: Vector::takeFirst()
 */
TEST_F(VectorTest, take_first) {
	EXPECT_TRUE(false);
}

/**
 * Test: Vector::takeLast()
 */
TEST_F(VectorTest, take_last) {
	EXPECT_TRUE(false);
}
//=============================================================================================
// Queries
//=============================================================================================
/**
 * Test: Vector::contains()
 */
TEST_F(VectorTest, contains_value) {
	EXPECT_TRUE(false);
}

/**
 * Test: Vector::count()
 */
TEST_F(VectorTest, count_occurrences_of_value) {
	EXPECT_TRUE(false);
}

/**
 * Test: Vector::endsWith()
 */
TEST_F(VectorTest, ends_with_value) {
	EXPECT_TRUE(false);
}

/**
 * Test: Vector::indexOf()
 */
TEST_F(VectorTest, index_of_value) {
	EXPECT_TRUE(false);
}

/**
 * Test: Vector::lastIndexOf()
 */
TEST_F(VectorTest, last_index_of_value) {
	EXPECT_TRUE(false);
}

/**
 * Test: Vector::startsWith()
 */
TEST_F(VectorTest, starts_with_value) {
	EXPECT_TRUE(false);
}
//=============================================================================================
// Conversions
//=============================================================================================
/**
 * Test: Vector::toList()
 */
TEST_F(VectorTest, convert_to_prism_list) {
	EXPECT_TRUE(false);
}

/**
 * Test: Vector::toStdVector()
 */
TEST_F(VectorTest, convert_to_std_vector) {
	EXPECT_TRUE(false);
}
//=============================================================================================
// Allocator
//=============================================================================================
/**
 * Test: Vector::allocator()
 */
TEST_F(VectorTest, get_allocator) {
	EXPECT_TRUE(false);
}
//=============================================================================================
// Non member functions
//=============================================================================================
/**
 * Test: operator==(const Vector&, const Vector&)
 */
TEST_F(VectorTest, operator_equivalence_of_two_vectors) {
	EXPECT_TRUE(false);
}

/**
 * Test: operator!=(const Vector&, const Vector&)
 */
TEST_F(VectorTest, operator_non_equivalence_of_two_vectors) {
	EXPECT_TRUE(false);
}

/**
 * Test: operator<(const Vector&, const Vector&)
 */
TEST_F(VectorTest, operator_less_than____vector_less_than_another) {
	EXPECT_TRUE(false);
}

/**
 * Test: operator<=(const Vector&, const Vector&)
 */
TEST_F(VectorTest, operator_less_than_or_equal____vector_less_than_or_equal_to_another) {
	EXPECT_TRUE(false);
}

/**
 * Test: operator>(const Vector&, const Vector&)
 */
TEST_F(VectorTest, operator_greater_than____vector_greater_than_another) {
	EXPECT_TRUE(false);
}

/**
 * Test: operator>=(const Vector&, const Vector&)
 */
TEST_F(VectorTest, operator_greater_than_or_equal____vector_greater_than_or_equal_to_another) {
	EXPECT_TRUE(false);
}

/**
 * Test: operator<<(std:ostream&, const Vector&)
 */
TEST_F(VectorTest, operator_stream_vector_to_output) {
	EXPECT_TRUE(false);
}

/**
 * Test: swap(Vector& a, Vector& b)
 */
TEST_F(VectorTest, swap_vectors) {
	EXPECT_TRUE(false);
}

} // end namespace test
} // end namespace prism














