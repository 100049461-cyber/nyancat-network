# Adding a useful test

Create `tests/your_component_test.cpp` with a `main` that exits nonzero on failure.
Add `nyan_add_test(your_component_test)` to [CMakeLists.txt](CMakeLists.txt).
Rerun `cmake --preset dev`, then build and run `ctest --preset dev`.
No testing framework is required. Use explicit failure checks so Release builds
do not lose tests through `NDEBUG`.

Choose evidence for the behavior you changed:

- Parser: use a hand-written wire transcript from the RFC, then split it at every
  byte boundary. Compare the reconstructed data and commands, not event grouping.
- Socket I/O: use real `socketpair` endpoints and independently specified bytes,
  including NUL and `0xff`; exercise EOF and an already-closed peer.
- Argument parsing: accepted and rejected command lines with expected outcomes.
- Integration: launch the real client and upstream server with timeouts; inspect
  output, exit status, and cleanup. A fake peer is useful for deliberately broken
  streams, but does not replace the upstream-server check.

Avoid tests that assert constants equal themselves, build expected packets using
the encoder being tested, or mock out the socket operation under test. Constants
and documentation-only tasks usually need a build or manual check, not new tests.

CI also runs [the server environment check](../scripts/check-server.py). It checks
the provided server setup, not the student client. Initially CTest reports
`No tests were found!!!`; that is expected until the first component tests land.

References: [CTest](https://cmake.org/cmake/help/latest/manual/ctest.1.html),
[socketpair](https://man7.org/linux/man-pages/man2/socketpair.2.html),
[Python subprocess](https://docs.python.org/3/library/subprocess.html).
