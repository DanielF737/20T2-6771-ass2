// We don't own this macro; don't prefix it with `COMP6771_`.
#include "comp6771/euclidean_vector.hpp"
#define CATCH_CONFIG_MAIN // NOLINT(readability-identifier-naming)
#include "catch2/catch.hpp"

// This file is designed to act as the program entry point. Everything is defined in catch.hpp, so
// we don't need to worry about doing anything other than indicating our interest to use it via the
// CATCH_CONFIG_MAIN macro.

TEST_CASE("Constructors") {
	SECTION("No-arg constructor") {
		auto ev = comp6771::euclidean_vector();
	}
}