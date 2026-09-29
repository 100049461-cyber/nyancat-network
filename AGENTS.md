# Working on this project

This is a club learning project. Implement the requested issue; leave other
exercises for their owners. Use GNU++23, CMake, and the Linux Codespace.
Read CONTRIBUTING.md and docs/design.md before changing an interface.

Do not write tautological tests that merely repeat the implementation, assert a
fixture's assigned value, or reproduce its logic in expected results. Tests must
check independently defined behavior and catch a plausible defect or regression.
Choose unit, integration, or E2E coverage according to the failure being tested;
do not mock away that behavior. Skip new tests when they add no meaningful evidence.

Run `cmake --preset dev`, `cmake --build --preset dev`, and `ctest --preset dev`
for relevant C++ changes. The initial scaffold has no client tests yet; successful
compilation alone does not mean the client works.
