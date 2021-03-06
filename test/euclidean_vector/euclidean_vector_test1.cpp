#include "comp6771/euclidean_vector.hpp"

#include <catch2/catch.hpp>
#include <fmt/format.h>
#include <fmt/ostream.h>
#include <iostream>
#include <vector>

TEST_CASE("basic test") {
	// Please note - this test may not function, it's just here for stubbing purposes
	auto const a1 = comp6771::euclidean_vector(3, 3.0);
	auto const a2 = comp6771::euclidean_vector(3, 3.0);
	auto const a3 = comp6771::euclidean_vector(3, 3.0);

	CHECK(fmt::format("{}", a1 + a2 + a3) == "[9 9 9]");
}

TEST_CASE("Constructors") {
	SECTION("No-arg constructor") {
		auto ev = comp6771::euclidean_vector();
		CHECK(ev.dimensions() == 1);
		CHECK(ev[0] == 0.0);
	}

	SECTION("Single-arg constructor") {
		auto v1 = comp6771::euclidean_vector(0); // empty vector
		auto v2 = comp6771::euclidean_vector(1); // single dimension vector
		auto v3 = comp6771::euclidean_vector(5); // multi dimension vector

		// Check correct dimensions
		CHECK(v1.dimensions() == 0);
		CHECK(v2.dimensions() == 1);
		CHECK(v3.dimensions() == 5);

		// Check correct values
		CHECK(v2[0] == 0.0);

		CHECK(v3[0] == 0.0);
		CHECK(v3[1] == 0.0);
		CHECK(v3[2] == 0.0);
		CHECK(v3[3] == 0.0);
		CHECK(v3[4] == 0.0);
	}

	SECTION("int double constructor") {
		auto v1 = comp6771::euclidean_vector(0, 0.0); // empty vector
		auto v2 = comp6771::euclidean_vector(1, 1.1); // single dimension vector
		auto v3 = comp6771::euclidean_vector(5, 5.5); // multi dimension vector

		// Check correct dimensions
		CHECK(v1.dimensions() == 0);
		CHECK(v2.dimensions() == 1);
		CHECK(v3.dimensions() == 5);

		// Check correct values
		CHECK(v2[0] == 1.1);

		CHECK(v3[0] == 5.5);
		CHECK(v3[1] == 5.5);
		CHECK(v3[2] == 5.5);
		CHECK(v3[3] == 5.5);
		CHECK(v3[4] == 5.5);
	}

	SECTION("iterator constructor") {
		// Empty Vector
		auto empty = std::vector<double>();
		auto start1 = empty.begin();
		auto end1 = empty.end();
		auto v1 = comp6771::euclidean_vector(start1, end1);

		// Single Item Vector
		auto single = std::vector<double>();
		single.push_back(1.1);
		auto start2 = single.begin();
		auto end2 = single.end();
		auto v2 = comp6771::euclidean_vector(start2, end2);

		// Multi Item Vector
		auto multi = std::vector<double>();
		multi.push_back(1.1);
		multi.push_back(2.2);
		multi.push_back(3.3);
		multi.push_back(4.4);
		multi.push_back(5.5);
		auto start3 = multi.begin();
		auto end3 = multi.end();
		auto v3 = comp6771::euclidean_vector(start3, end3);

		// Check correct dimensions
		CHECK(v1.dimensions() == 0);
		CHECK(v2.dimensions() == 1);
		CHECK(v3.dimensions() == 5);

		// Check correct values
		CHECK(v2[0] == 1.1);

		CHECK(v3[0] == 1.1);
		CHECK(v3[1] == 2.2);
		CHECK(v3[2] == 3.3);
		CHECK(v3[3] == 4.4);
		CHECK(v3[4] == 5.5);
	}

	SECTION("Initializer list constructor") {
		// Empty List
		auto v1 = comp6771::euclidean_vector{}; // Actually just calls the default constructor, the
		                                        // more you know
		// Single Item List
		auto v2 = comp6771::euclidean_vector{1.1};
		// Mulit Item List
		auto v3 = comp6771::euclidean_vector{1.1, 2.2, 3.3, 4.4, 5.5};

		// Check correct dimensions
		CHECK(v1.dimensions() == 1);
		CHECK(v2.dimensions() == 1);
		CHECK(v3.dimensions() == 5);

		// Check correct values
		CHECK(v1[0] == 0.0);

		CHECK(v2[0] == 1.1);

		CHECK(v3[0] == 1.1);
		CHECK(v3[1] == 2.2);
		CHECK(v3[2] == 3.3);
		CHECK(v3[3] == 4.4);
		CHECK(v3[4] == 5.5);
	}

	SECTION("Copy constructor") {
		// Empty vector
		auto src1 = comp6771::euclidean_vector(0);
		// Single dim vector
		auto src2 = comp6771::euclidean_vector{1.1};
		// Multi dim vector
		auto src3 = comp6771::euclidean_vector{1.1, 2.2, 3.3, 4.4, 5.5};

		// Ensure the source vectors are correct
		REQUIRE(src1.dimensions() == 0);
		REQUIRE(src2.dimensions() == 1);
		REQUIRE(src3.dimensions() == 5);

		REQUIRE(src2[0] == 1.1);

		REQUIRE(src3[0] == 1.1);
		REQUIRE(src3[1] == 2.2);
		REQUIRE(src3[2] == 3.3);
		REQUIRE(src3[3] == 4.4);
		REQUIRE(src3[4] == 5.5);

		// NOLINTNEXTLINE(performance-unnecessary-copy-initialization)
		auto v1 = src1;
		auto v2 = src2;
		auto v3 = src3;

		// Check correct dimensions
		CHECK(v1.dimensions() == 0);
		CHECK(v2.dimensions() == 1);
		CHECK(v3.dimensions() == 5);

		// Check correct values
		CHECK(v2[0] == 1.1);

		CHECK(v3[0] == 1.1);
		CHECK(v3[1] == 2.2);
		CHECK(v3[2] == 3.3);
		CHECK(v3[3] == 4.4);
		CHECK(v3[4] == 5.5);
	}

	SECTION("Move constructor") {
		// Empty vector
		auto src1 = comp6771::euclidean_vector(0);
		// Single dim vector
		auto src2 = comp6771::euclidean_vector{1.1};
		// Multi dim vector
		auto src3 = comp6771::euclidean_vector{1.1, 2.2, 3.3, 4.4, 5.5};

		// Ensure the source vectors are correct
		REQUIRE(src1.dimensions() == 0);
		REQUIRE(src2.dimensions() == 1);
		REQUIRE(src3.dimensions() == 5);

		REQUIRE(src2[0] == 1.1);

		REQUIRE(src3[0] == 1.1);
		REQUIRE(src3[1] == 2.2);
		REQUIRE(src3[2] == 3.3);
		REQUIRE(src3[3] == 4.4);
		REQUIRE(src3[4] == 5.5);

		auto v1 = comp6771::euclidean_vector(std::move(src1));
		auto v2 = comp6771::euclidean_vector(std::move(src2));
		auto v3 = comp6771::euclidean_vector(std::move(src3));

		// Check correct dimensions
		CHECK(v1.dimensions() == 0);
		CHECK(v2.dimensions() == 1);
		CHECK(v3.dimensions() == 5);

		// Check correct values
		CHECK(v2[0] == 1.1);

		CHECK(v3[0] == 1.1);
		CHECK(v3[1] == 2.2);
		CHECK(v3[2] == 3.3);
		CHECK(v3[3] == 4.4);
		CHECK(v3[4] == 5.5);
	}
}

TEST_CASE("Operations") {
	SECTION("Copy assignment") {
		// Empty vector
		auto src1 = comp6771::euclidean_vector(0);
		// Single dim vector
		auto src2 = comp6771::euclidean_vector{1.1};
		// Multi dim vector
		auto src3 = comp6771::euclidean_vector{1.1, 2.2, 3.3, 4.4, 5.5};

		// NOLINTNEXTLINE(performance-unnecessary-copy-initialization)
		auto v1 = src1;
		auto v2 = src2;
		auto v3 = src3;

		// Check correct dimensions
		CHECK(v1.dimensions() == 0);
		CHECK(v2.dimensions() == 1);
		CHECK(v3.dimensions() == 5);

		// Check correct values
		CHECK(v2[0] == 1.1);

		CHECK(v3[0] == 1.1);
		CHECK(v3[1] == 2.2);
		CHECK(v3[2] == 3.3);
		CHECK(v3[3] == 4.4);
		CHECK(v3[4] == 5.5);
	}

	SECTION("Move assignment") {
		// Empty vector
		auto src1 = comp6771::euclidean_vector(0);
		// Single dim vector
		auto src2 = comp6771::euclidean_vector{1.1};
		// Multi dim vector
		auto src3 = comp6771::euclidean_vector{1.1, 2.2, 3.3, 4.4, 5.5};

		// NOLINTNEXTLINE(performance-unnecessary-copy-initialization)
		auto v1 = std::move(src1);
		auto v2 = std::move(src2);
		auto v3 = std::move(src3);

		// Check correct dimensions
		CHECK(v1.dimensions() == 0);
		CHECK(v2.dimensions() == 1);
		CHECK(v3.dimensions() == 5);

		// Check correct values
		CHECK(v2[0] == 1.1);

		CHECK(v3[0] == 1.1);
		CHECK(v3[1] == 2.2);
		CHECK(v3[2] == 3.3);
		CHECK(v3[3] == 4.4);
		CHECK(v3[4] == 5.5);
	}

	SECTION("Subscript") {
		// Single dim vector
		auto v1 = comp6771::euclidean_vector{1.1};
		// Multi dim vector
		auto v2 = comp6771::euclidean_vector{1.1, 2.2, 3.3, 4.4, 5.5};

		// Ensure vectors created correctly
		REQUIRE(v1.dimensions() == 1);
		REQUIRE(v2.dimensions() == 5);

		// Need to check const and non const implementations
		// const
		CHECK(v1[0] == 1.1);
		CHECK(v2[0] == 1.1);
		CHECK(v2[1] == 2.2);
		CHECK(v2[2] == 3.3);
		CHECK(v2[3] == 4.4);
		CHECK(v2[4] == 5.5);

		// non-const
		CHECK(v2[4] == 5.5);
		v2[4] = v2[4] + 5;
		CHECK(v2[4] == 10.5);
	}

	SECTION("Unary plus") {
		// Empty vector
		auto src1 = comp6771::euclidean_vector(0);
		// Single dim vector
		auto src2 = comp6771::euclidean_vector{1.1};
		// Multi dim vector
		auto src3 = comp6771::euclidean_vector{1.1, 2.2, 3.3, 4.4, 5.5};

		// NOLINTNEXTLINE(performance-unnecessary-copy-initialization)
		auto v1 = +src1;
		auto v2 = +src2;
		auto v3 = +src3;

		// Check correct dimensions
		CHECK(v1.dimensions() == 0);
		CHECK(v2.dimensions() == 1);
		CHECK(v3.dimensions() == 5);

		// Check correct values
		CHECK(v2[0] == 1.1);

		CHECK(v3[0] == 1.1);
		CHECK(v3[1] == 2.2);
		CHECK(v3[2] == 3.3);
		CHECK(v3[3] == 4.4);
		CHECK(v3[4] == 5.5);
	}

	SECTION("Negation") {
		// Empty vector
		auto src1 = comp6771::euclidean_vector(0);
		// Single dim vector
		auto src2 = comp6771::euclidean_vector{1.1};
		// Multi dim vector
		auto src3 = comp6771::euclidean_vector{1.1, 2.2, 3.3, 4.4, 5.5};

		// NOLINTNEXTLINE(performance-unnecessary-copy-initialization)
		auto v1 = -src1;
		auto v2 = -src2;
		auto v3 = -src3;

		// Check correct dimensions
		CHECK(v1.dimensions() == 0);
		CHECK(v2.dimensions() == 1);
		CHECK(v3.dimensions() == 5);

		// Check correct values
		CHECK(v2[0] == -1.1);

		CHECK(v3[0] == -1.1);
		CHECK(v3[1] == -2.2);
		CHECK(v3[2] == -3.3);
		CHECK(v3[3] == -4.4);
		CHECK(v3[4] == -5.5);
	}

	SECTION("Vector type conversion") {
		// Empty vector
		auto v1 = comp6771::euclidean_vector(0);
		// Single dim vector
		auto v2 = comp6771::euclidean_vector{1.1};
		// Multi dim vector
		auto v3 = comp6771::euclidean_vector{1.1, 2.2, 3.3, 4.4, 5.5};

		// Ensure vectors created correctly
		REQUIRE(v1.dimensions() == 0);
		REQUIRE(v2.dimensions() == 1);
		REQUIRE(v3.dimensions() == 5);
		REQUIRE(v2[0] == 1.1);
		REQUIRE(v3[0] == 1.1);
		REQUIRE(v3[1] == 2.2);
		REQUIRE(v3[2] == 3.3);
		REQUIRE(v3[3] == 4.4);
		REQUIRE(v3[4] == 5.5);

		auto expected1 = std::vector<double>();
		auto expected2 = std::vector<double>{1.1};
		auto expected3 = std::vector<double>{1.1, 2.2, 3.3, 4.4, 5.5};

		CHECK(static_cast<std::vector<double>>(v1) == expected1);
		CHECK(static_cast<std::vector<double>>(v2) == expected2);
		CHECK(static_cast<std::vector<double>>(v3) == expected3);
	}

	SECTION("List type conversion") {
		// Empty vector
		auto v1 = comp6771::euclidean_vector(0);
		// Single dim vector
		auto v2 = comp6771::euclidean_vector{1.1};
		// Multi dim vector
		auto v3 = comp6771::euclidean_vector{1.1, 2.2, 3.3, 4.4, 5.5};

		// Ensure vectors created correctly
		REQUIRE(v1.dimensions() == 0);
		REQUIRE(v2.dimensions() == 1);
		REQUIRE(v3.dimensions() == 5);
		REQUIRE(v2[0] == 1.1);
		REQUIRE(v3[0] == 1.1);
		REQUIRE(v3[1] == 2.2);
		REQUIRE(v3[2] == 3.3);
		REQUIRE(v3[3] == 4.4);
		REQUIRE(v3[4] == 5.5);

		auto expected1 = std::list<double>();
		auto expected2 = std::list<double>{1.1};
		auto expected3 = std::list<double>{1.1, 2.2, 3.3, 4.4, 5.5};

		CHECK(static_cast<std::list<double>>(v1) == expected1);
		CHECK(static_cast<std::list<double>>(v2) == expected2);
		CHECK(static_cast<std::list<double>>(v3) == expected3);
	}
}

TEST_CASE("Compound operations") {
	SECTION("Compound addition") {
		// Empty vector
		auto v1 = comp6771::euclidean_vector(0);
		// Single dim vector
		auto v2 = comp6771::euclidean_vector{1.1};
		// Multi dim vector
		auto v3 = comp6771::euclidean_vector{1.1, 2.2, 3.3, 4.4, 5.5};

		// Ensure vectors created correctly
		REQUIRE(v1.dimensions() == 0);
		REQUIRE(v2.dimensions() == 1);
		REQUIRE(v3.dimensions() == 5);
		REQUIRE(v2[0] == 1.1);
		REQUIRE(v3[0] == 1.1);
		REQUIRE(v3[1] == 2.2);
		REQUIRE(v3[2] == 3.3);
		REQUIRE(v3[3] == 4.4);
		REQUIRE(v3[4] == 5.5);

		// Adding 2 empty
		v1 += v1;

		CHECK(v1.dimensions() == 0);

		// Adding 2 single item vectors
		auto newv2 = comp6771::euclidean_vector{10.0};
		v2 += newv2;

		CHECK(v2.dimensions() == 1);
		CHECK(v2[0] == 11.1);

		// Adding 2 multi item vectors
		auto newv3 = comp6771::euclidean_vector(5, 10);
		v3 += newv3;

		CHECK(v3.dimensions() == 5);
		CHECK(v3[0] == 11.1);
		CHECK(v3[1] == 12.2);
		CHECK(v3[2] == 13.3);
		CHECK(v3[3] == 14.4);
		CHECK(v3[4] == 15.5);

		// Addition to self
		auto expected = comp6771::euclidean_vector{22.2, 24.4, 26.6, 28.8, 31.0};
		REQUIRE(expected.dimensions() == 5);
		CHECK((v3 += v3) == expected);

		// Adding 2 vectors of mismatched dimensions
		CHECK_THROWS_WITH(v3 += v2, "Dimensions of LHS(5) and RHS(1) do not match");
	}

	SECTION("Compound subtraction") {
		// Single dim vector
		auto v2 = comp6771::euclidean_vector{1.1};
		// Multi dim vector
		auto v3 = comp6771::euclidean_vector{1.1, 2.2, 3.3, 4.4, 5.5};

		// Ensure vectors created correctly
		REQUIRE(v2.dimensions() == 1);
		REQUIRE(v3.dimensions() == 5);
		REQUIRE(v2[0] == 1.1);
		REQUIRE(v3[0] == 1.1);
		REQUIRE(v3[1] == 2.2);
		REQUIRE(v3[2] == 3.3);
		REQUIRE(v3[3] == 4.4);
		REQUIRE(v3[4] == 5.5);

		// Subtracting 2 single item vectors
		auto newv2 = comp6771::euclidean_vector{10.0};
		v2 -= newv2;

		CHECK(v2.dimensions() == 1);
		CHECK(v2[0] == -8.9);

		// Subtracting 2 multi item vectors
		auto newv3 = comp6771::euclidean_vector(5, 10);
		v3 -= newv3;

		CHECK(v3.dimensions() == 5);
		CHECK(v3[0] == -8.9);
		CHECK(v3[1] == -7.8);
		CHECK(v3[2] == -6.7);
		CHECK(v3[3] == -5.6);
		CHECK(v3[4] == -4.5);

		// Subtraction from self returns 0
		auto zero_vec = comp6771::euclidean_vector{0, 0, 0, 0, 0};
		REQUIRE(zero_vec.dimensions() == 5);
		CHECK((v3 -= v3) == zero_vec);

		// Subtracting 2 vectors of mismatched dimensions
		CHECK_THROWS_WITH(v3 -= v2, "Dimensions of LHS(5) and RHS(1) do not match");
	}

	SECTION("Compound multiplication") {
		// Empty vector
		auto v1 = comp6771::euclidean_vector(0);
		// Single dim vector
		auto v2 = comp6771::euclidean_vector{1.1};
		// Multi dim vector
		auto v3 = comp6771::euclidean_vector{1.1, 2.2, 3.3, 4.4, 5.5};

		// Ensure vectors created correctly
		REQUIRE(v1.dimensions() == 0);
		REQUIRE(v2.dimensions() == 1);
		REQUIRE(v3.dimensions() == 5);
		REQUIRE(v2[0] == 1.1);
		REQUIRE(v3[0] == 1.1);
		REQUIRE(v3[1] == 2.2);
		REQUIRE(v3[2] == 3.3);
		REQUIRE(v3[3] == 4.4);
		REQUIRE(v3[4] == 5.5);

		v1 *= 0;
		CHECK(v1.dimensions() == 0);

		v2 *= 2;
		CHECK(v2.dimensions() == 1);
		CHECK(v2[0] == 2.2);

		v3 *= -2;
		CHECK(v3.dimensions() == 5);
		CHECK(v3[0] == -2.2);
		CHECK(v3[1] == -4.4);
		CHECK(v3[2] == -6.6);
		CHECK(v3[3] == -8.8);
		CHECK(v3[4] == -11);
	}

	SECTION("Compound Division") {
		// Empty vector
		auto v1 = comp6771::euclidean_vector(0);
		// Single dim vector
		auto v2 = comp6771::euclidean_vector{1.1};
		// Multi dim vector
		auto v3 = comp6771::euclidean_vector{1.1, 2.2, 3.3, 4.4, 5.5};

		// Ensure vectors created correctly
		REQUIRE(v1.dimensions() == 0);
		REQUIRE(v2.dimensions() == 1);
		REQUIRE(v3.dimensions() == 5);
		REQUIRE(v2[0] == 1.1);
		REQUIRE(v3[0] == 1.1);
		REQUIRE(v3[1] == 2.2);
		REQUIRE(v3[2] == 3.3);
		REQUIRE(v3[3] == 4.4);
		REQUIRE(v3[4] == 5.5);

		v1 /= 1;
		CHECK(v1.dimensions() == 0);

		v2 /= 2;
		CHECK(v2.dimensions() == 1);
		CHECK(v2[0] == 0.55);

		v3 /= -2;
		CHECK(v3.dimensions() == 5);
		CHECK(v3[0] == -0.55);
		CHECK(v3[1] == -1.1);
		CHECK(v3[2] == -1.65);
		CHECK(v3[3] == -2.2);
		CHECK(v3[4] == -2.75);

		// Subtracting 2 vectors of mismatched dimensions
		CHECK_THROWS_WITH(v3 /= 0, "Invalid vector division by 0");
	}
}

TEST_CASE("Member Functions") {
	SECTION("at") {
		// Need to test const and non-const paths
		//(tests can be identical to subscript then i guess)
		// Single dim vector
		auto v1 = comp6771::euclidean_vector{1.1};
		// Multi dim vector
		auto v2 = comp6771::euclidean_vector{1.1, 2.2, 3.3, 4.4, 5.5};

		// Ensure vectors created correctly
		REQUIRE(v1.dimensions() == 1);
		REQUIRE(v2.dimensions() == 5);

		// Need to check const and non const implementations
		// const
		CHECK(v1.at(0) == 1.1);
		CHECK(v2.at(0) == 1.1);
		CHECK(v2.at(1) == 2.2);
		CHECK(v2.at(2) == 3.3);
		CHECK(v2.at(3) == 4.4);
		CHECK(v2.at(4) == 5.5);

		// non-const
		CHECK(v2.at(4) == 5.5);
		v2.at(4) = v2.at(4) + 5;
		CHECK(v2.at(4) == 10.5);
	}

	SECTION("dimensions") {
		// Empty vector
		auto v1 = comp6771::euclidean_vector(0);
		// Single dim vector
		auto v2 = comp6771::euclidean_vector{1.1};
		// Multi dim vector
		auto v3 = comp6771::euclidean_vector{1.1, 2.2, 3.3, 4.4, 5.5};

		// Ensure vectors created correctly
		CHECK(v1.dimensions() == 0);
		CHECK(v2.dimensions() == 1);
		CHECK(v3.dimensions() == 5);
	}
}

TEST_CASE("2 Vectors Friend Functions") {
	SECTION("Equal") {
		// Empty vector
		auto v1 = comp6771::euclidean_vector(0);
		// Single dim vector
		auto v2 = comp6771::euclidean_vector{1.1};
		// Multi dim vector
		auto v3 = comp6771::euclidean_vector{1.1, 2.2, 3.3, 4.4, 5.5};

		// Ensure vectors created correctly
		REQUIRE(v1.dimensions() == 0);
		REQUIRE(v2.dimensions() == 1);
		REQUIRE(v3.dimensions() == 5);
		REQUIRE(v2[0] == 1.1);
		REQUIRE(v3[0] == 1.1);
		REQUIRE(v3[1] == 2.2);
		REQUIRE(v3[2] == 3.3);
		REQUIRE(v3[3] == 4.4);
		REQUIRE(v3[4] == 5.5);

		// Check reflexivity
		CHECK(v1 == v1);
		CHECK(v2 == v2);
		CHECK(v3 == v3);

		// Check symmetry
		auto v3_2 = comp6771::euclidean_vector{1.1, 2.2, 3.3, 4.4, 5.5};
		CHECK(v3 == v3_2);
		CHECK(v3_2 == v3);

		// Check transitivity
		auto v3_3 = comp6771::euclidean_vector{1.1, 2.2, 3.3, 4.4, 5.5};
		CHECK(v3 == v3_2);
		CHECK(v3_2 == v3_3);
		CHECK(v3 == v3_3);

		// Check false case (same dimension different values)
		auto not_v3 = comp6771::euclidean_vector(5, 0);
		REQUIRE(not_v3.dimensions() == 5);
		CHECK_FALSE(v3 == not_v3);

		// Check vectors of mismatched dimensions
		CHECK_FALSE(v3 == v2);
	}

	SECTION("Not Equal") {
		// Empty vector
		auto v1 = comp6771::euclidean_vector(0);
		// Single dim vector
		auto v2 = comp6771::euclidean_vector{1.1};
		// Multi dim vector
		auto v3 = comp6771::euclidean_vector{1.1, 2.2, 3.3, 4.4, 5.5};

		// Ensure vectors created correctly
		REQUIRE(v1.dimensions() == 0);
		REQUIRE(v2.dimensions() == 1);
		REQUIRE(v3.dimensions() == 5);
		REQUIRE(v2[0] == 1.1);
		REQUIRE(v3[0] == 1.1);
		REQUIRE(v3[1] == 2.2);
		REQUIRE(v3[2] == 3.3);
		REQUIRE(v3[3] == 4.4);
		REQUIRE(v3[4] == 5.5);

		// Check non-reflexivity
		CHECK_FALSE(v1 != v1);
		CHECK_FALSE(v2 != v2);
		CHECK_FALSE(v3 != v3);

		// Check symmetry
		auto v3_2 = comp6771::euclidean_vector{0, 0, 0, 0, 0};
		CHECK(v3 != v3_2);
		CHECK(v3_2 != v3);

		// Check non - transitivity
		auto v3_3 = comp6771::euclidean_vector{1.1, 2.2, 3.3, 4.4, 5.5};
		CHECK(v3 != v3_2);
		CHECK(v3_2 != v3_3);
		CHECK_FALSE(v3 != v3_3);

		// Check vectors of mismatched dimensions
		CHECK(v3 != v2);
	}

	SECTION("Addition") {
		// Empty vector
		auto v1 = comp6771::euclidean_vector(0);
		// Single dim vector
		auto v2 = comp6771::euclidean_vector{1.1};
		// Multi dim vector
		auto v3 = comp6771::euclidean_vector{1.1, 2.2, 3.3, 4.4, 5.5};

		// Ensure vectors created correctly
		REQUIRE(v1.dimensions() == 0);
		REQUIRE(v2.dimensions() == 1);
		REQUIRE(v3.dimensions() == 5);
		REQUIRE(v2[0] == 1.1);
		REQUIRE(v3[0] == 1.1);
		REQUIRE(v3[1] == 2.2);
		REQUIRE(v3[2] == 3.3);
		REQUIRE(v3[3] == 4.4);
		REQUIRE(v3[4] == 5.5);

		CHECK((v1 + v1) == v1);

		auto expected = comp6771::euclidean_vector{11.1};
		CHECK((v2 + comp6771::euclidean_vector{10}) == expected);

		expected = comp6771::euclidean_vector{11.1, 12.2, 13.3, 14.4, 15.5};
		CHECK((v3 + comp6771::euclidean_vector(5, 10)) == expected);

		expected = comp6771::euclidean_vector{-8.9, -7.8, -6.7, -5.6, -4.5};
		CHECK((v3 + comp6771::euclidean_vector(5, -10)) == expected);

		CHECK_THROWS_WITH(v2 + v3, "Dimensions of LHS(1) and RHS(5) do not match");
	}

	SECTION("Subtraction") {
		// Empty vector
		auto v1 = comp6771::euclidean_vector(0);
		// Single dim vector
		auto v2 = comp6771::euclidean_vector{1.1};
		// Multi dim vector
		auto v3 = comp6771::euclidean_vector{1.1, 2.2, 3.3, 4.4, 5.5};

		// Ensure vectors created correctly
		REQUIRE(v1.dimensions() == 0);
		REQUIRE(v2.dimensions() == 1);
		REQUIRE(v3.dimensions() == 5);
		REQUIRE(v2[0] == 1.1);
		REQUIRE(v3[0] == 1.1);
		REQUIRE(v3[1] == 2.2);
		REQUIRE(v3[2] == 3.3);
		REQUIRE(v3[3] == 4.4);
		REQUIRE(v3[4] == 5.5);

		CHECK((v1 - v1) == v1);

		auto expected = comp6771::euclidean_vector{-8.9};
		CHECK((v2 - comp6771::euclidean_vector{10}) == expected);

		expected = comp6771::euclidean_vector{-8.9, -7.8, -6.7, -5.6, -4.5};
		CHECK((v3 - comp6771::euclidean_vector(5, 10)) == expected);

		expected = comp6771::euclidean_vector{11.1, 12.2, 13.3, 14.4, 15.5};
		CHECK((v3 - comp6771::euclidean_vector(5, -10)) == expected);

		CHECK_THROWS_WITH(v2 + v3, "Dimensions of LHS(1) and RHS(5) do not match");
	}
}

TEST_CASE("Other Friend Functions") {
	SECTION("Multiply") {
		// Empty vector
		auto v1 = comp6771::euclidean_vector(0);
		// Single dim vector
		auto v2 = comp6771::euclidean_vector{1.1};
		// Multi dim vector
		auto v3 = comp6771::euclidean_vector{1.1, 2.2, 3.3, 4.4, 5.5};

		// Ensure vectors created correctly
		REQUIRE(v1.dimensions() == 0);
		REQUIRE(v2.dimensions() == 1);
		REQUIRE(v3.dimensions() == 5);
		REQUIRE(v2[0] == 1.1);
		REQUIRE(v3[0] == 1.1);
		REQUIRE(v3[1] == 2.2);
		REQUIRE(v3[2] == 3.3);
		REQUIRE(v3[3] == 4.4);
		REQUIRE(v3[4] == 5.5);

		CHECK(v1 * 1 == v1);

		CHECK(v2 * 2 == comp6771::euclidean_vector{2.2});

		CHECK(v3 * -1 == comp6771::euclidean_vector{-1.1, -2.2, -3.3, -4.4, -5.5});
		CHECK(v3 * 0 == comp6771::euclidean_vector(5, 0));
	}

	SECTION("Divide") {
		// Empty vector
		auto v1 = comp6771::euclidean_vector(0);
		// Single dim vector
		auto v2 = comp6771::euclidean_vector{1.1};
		// Multi dim vector
		auto v3 = comp6771::euclidean_vector{1.1, 2.2, 3.3, 4.4, 5.5};

		// Ensure vectors created correctly
		REQUIRE(v1.dimensions() == 0);
		REQUIRE(v2.dimensions() == 1);
		REQUIRE(v3.dimensions() == 5);
		REQUIRE(v2[0] == 1.1);
		REQUIRE(v3[0] == 1.1);
		REQUIRE(v3[1] == 2.2);
		REQUIRE(v3[2] == 3.3);
		REQUIRE(v3[3] == 4.4);
		REQUIRE(v3[4] == 5.5);

		CHECK(v1 / 1 == v1);

		CHECK(v2 / 2 == comp6771::euclidean_vector{0.55});

		CHECK(v3 / -1 == comp6771::euclidean_vector{-1.1, -2.2, -3.3, -4.4, -5.5});
		CHECK(v3 / 2 == comp6771::euclidean_vector{0.55, 1.1, 1.65, 2.2, 2.75});

		CHECK_THROWS_WITH(v3 / 0, "Invalid vector division by 0");
	}

	SECTION("Output Stream") {
		// Empty vector
		auto v1 = comp6771::euclidean_vector(0);
		// Single dim vector
		auto v2 = comp6771::euclidean_vector{-1.1};
		// Multi dim vector
		auto v3 = comp6771::euclidean_vector{1.1, 2.2, 3.3, 4.4, 5.5};

		// Ensure vectors created correctly
		REQUIRE(v1.dimensions() == 0);
		REQUIRE(v2.dimensions() == 1);
		REQUIRE(v3.dimensions() == 5);
		REQUIRE(v2[0] == -1.1);
		REQUIRE(v3[0] == 1.1);
		REQUIRE(v3[1] == 2.2);
		REQUIRE(v3[2] == 3.3);
		REQUIRE(v3[3] == 4.4);
		REQUIRE(v3[4] == 5.5);

		CHECK(fmt::format("{}", v1) == "[]");
		CHECK(fmt::format("{}", v2) == "[-1.1]");
		CHECK(fmt::format("{}", v3) == "[1.1 2.2 3.3 4.4 5.5]");
	}
}

TEST_CASE("Utility functions") {
	SECTION("Euclidean norm") {
		// Empty vector
		auto v1 = comp6771::euclidean_vector(0);
		// Single dim vector
		auto v2 = comp6771::euclidean_vector{1.1};
		// Multi dim vector
		auto v3 = comp6771::euclidean_vector{1.1, 2.2, 3.3, 4.4, 5.5};
		auto v4 = comp6771::euclidean_vector{0};

		// Ensure vectors created correctly
		REQUIRE(v1.dimensions() == 0);
		REQUIRE(v2.dimensions() == 1);
		REQUIRE(v3.dimensions() == 5);
		REQUIRE(v2[0] == 1.1);
		REQUIRE(v3[0] == 1.1);
		REQUIRE(v3[1] == 2.2);
		REQUIRE(v3[2] == 3.3);
		REQUIRE(v3[3] == 4.4);
		REQUIRE(v3[4] == 5.5);

		CHECK_THROWS_WITH(comp6771::euclidean_norm(v1),
		                  "euclidean_vector with no dimensions does not have a norm");

		auto res2 = comp6771::euclidean_norm(v2);
		CHECK(res2 == 1.1);

		auto res3 = comp6771::euclidean_norm(v3);
		CHECK(res3 == sqrt(1.1 * 1.1 + 2.2 * 2.2 + 3.3 * 3.3 + 4.4 * 4.4 + 5.5 * 5.5));

		auto res4 = comp6771::euclidean_norm(v4);
		CHECK(res4 == 0);
	}

	SECTION("Unit vector") {
		// Empty vector
		auto v1 = comp6771::euclidean_vector(0);
		// Single dim vector
		auto v2 = comp6771::euclidean_vector{1.1};
		// Multi dim vector
		auto v3 = comp6771::euclidean_vector{1.1, 2.2, 3.3, 4.4, 5.5};

		auto v4 = comp6771::euclidean_vector{0};

		// Ensure vectors created correctly
		REQUIRE(v1.dimensions() == 0);
		REQUIRE(v2.dimensions() == 1);
		REQUIRE(v3.dimensions() == 5);
		REQUIRE(v2[0] == 1.1);
		REQUIRE(v3[0] == 1.1);
		REQUIRE(v3[1] == 2.2);
		REQUIRE(v3[2] == 3.3);
		REQUIRE(v3[3] == 4.4);
		REQUIRE(v3[4] == 5.5);

		CHECK_THROWS_WITH(comp6771::unit(v1),
		                  "euclidean_vector with no dimensions does not have a unit vector");

		auto res2 = comp6771::unit(v2);
		CHECK(res2 == comp6771::euclidean_vector{1});

		auto ev_norm = comp6771::euclidean_norm(v3);
		auto res3 = comp6771::unit(v3);
		CHECK(res3
		      == comp6771::euclidean_vector{1.1 / ev_norm,
		                                    2.2 / ev_norm,
		                                    3.3 / ev_norm,
		                                    4.4 / ev_norm,
		                                    5.5 / ev_norm});

		CHECK_THROWS_WITH(comp6771::unit(v4),
		                  "euclidean_vector with zero euclidean normal does not have a unit vector");
	}

	SECTION("Dot product") {
		// Single dim vector
		auto v1 = comp6771::euclidean_vector{1.1};
		// Multi dim vector
		auto v2 = comp6771::euclidean_vector{1.1, 2.2, 3.3, 4.4, 5.5};

		auto v3 = comp6771::euclidean_vector{2};
		auto v4 = comp6771::euclidean_vector(5, 2);

		// Ensure vectors created correctly
		REQUIRE(v1.dimensions() == 1);
		REQUIRE(v2.dimensions() == 5);
		REQUIRE(v3.dimensions() == 1);
		REQUIRE(v4.dimensions() == 5);
		REQUIRE(v1[0] == 1.1);
		REQUIRE(v2[0] == 1.1);
		REQUIRE(v2[1] == 2.2);
		REQUIRE(v2[2] == 3.3);
		REQUIRE(v2[3] == 4.4);
		REQUIRE(v2[4] == 5.5);

		CHECK(comp6771::dot(v1, v1) == 1.1 * 1.1);
		CHECK(comp6771::dot(v1, v3) == 1.1 * 2);
		CHECK(comp6771::dot(v2, v4) == (1.1 * 2) + (2.2 * 2) + (3.3 * 2) + (4.4 * 2) + (5.5 * 2));

		CHECK_THROWS_WITH(comp6771::dot(v1, v2), "Dimensions of LHS(1) and RHS(5) do not match");
	}
}