# Repo Guidelines

This project is a small C++/OpenGL game. There are no automated tests, but
any changes to the source should compile successfully.

## Contributing

* Build the project with `make termak3d` to verify that it compiles.
* Do **not** commit newly generated binaries. Use `make clean` before
  committing if you built `termak3d`.
* Keep existing assets (`.map`, `.cor`, `Termak3D.PIE`) unchanged unless a
  change is specifically required.

Programmatic check: `make termak3d` must succeed.
