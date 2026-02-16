# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/en/1.0.0/)
and this project adheres to [Semantic Versioning](http://semver.org/spec/v2.0.0.html).

## [Unreleased]

## [1.5.0] - 2026-02-16

### Fixed

- **Critical: Line-segment intersection calculation** - Fixed incorrect absolute value handling in parametric line intersection detection in `FuzzyComposition::rebuild()` and `FuzzyOutput::rebuild()`. The previous implementation destroyed sign information needed for proper intersection calculation, causing incorrect composition shapes.

- **Critical: Trapezoid centroid calculation** - Corrected the Center of Area (COA) defuzzification for asymmetric trapezoids in `FuzzyComposition::calculate()`. Now uses the proper geometric formula `x = x1 + L * (2*h2 + h1) / (3*(h1 + h2))` instead of always using the midpoint, resulting in significantly more accurate defuzzification results.

- **Singleton edge case handling** - Fixed edge case in `FuzzyComposition::calculate()` where singletons with zero pertinence at the first point were not properly handled, potentially causing incorrect COA calculations.

- **Floating point equality comparisons** - Replaced all direct floating point equality checks (`==`, `!=`) with epsilon-based comparisons (`EPSILON_VALUE`) throughout `FuzzyComposition.cpp`. This eliminates false negatives caused by floating point rounding errors in point matching, loop termination conditions, and shape detection.

- **Boundary condition consistency** - Standardized intersection boundary checks to use exclusive bounds (`<`, `>`) consistently across both `FuzzyComposition` and `FuzzyOutput` classes, eliminating inconsistent behavior for edge cases.

### Changed

- Updated test expectations in `FuzzyTest.cpp` to reflect the corrected defuzzification values resulting from the trapezoid centroid fix. All 26 tests now pass with the improved accuracy.

### Added

- **Cross-platform build support** - Enhanced Makefile with automatic Google Test library detection for both macOS (Homebrew on Intel and Apple Silicon) and Ubuntu/Debian systems.

- **Separate build and test commands** - Added `make build-tests` to compile tests without running them, and improved `make test` to build and execute all tests with formatted output.

- **C++17 standard support** - Updated test compilation to use C++17 standard for compatibility with Google Test 1.17.0+.

- **Help command** - Added `make help` target to display all available build commands and their descriptions.

### Improved

- **README.md** - Completely rewritten with professional language, clearer explanations, better organization, and comprehensive examples. Fixed grammar and spelling errors throughout. Added detailed installation instructions for multiple platforms and improved API documentation.

### Technical Notes

These bug fixes improve the mathematical accuracy of fuzzy inference results. Systems using asymmetric trapezoidal membership functions will see the most significant improvements in defuzzification accuracy. The fixes address intermittent incorrect results that were particularly noticeable with certain membership function configurations.

## [1.4.1] - 2021-07-06

- Improve fuzzy set calculations

## [1.1.0] - 2019-02-22

### Added

- library.properties file to submit for Arduino Library Defaults.

### Changed

- A complete code review, code formatting, translating and commenting .
- A Bug at FuzzyOutput was found, in the way of calculate builds the points of FuzzyComposition.
- Some methods was renamed and others created (for helps in tests).
- A complete check in tests to ensure library accuracy.

### Removed

- None.

## [1.0.10] - 2017-08-21

### Added

- CHANGELOG.md file to document this project.

### Changed

- The way that FuzzyOutput truncate trapezoidal functions, improve the accuracy.
- File headers with author references.

### Removed

- None.
