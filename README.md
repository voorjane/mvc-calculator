# Calculator made in QT using C and C++

- Base calculating logic made on C, UI made using QT and C++
- Graph plotting using qcustomplot
- Credit calculator

## How to use

Open this project in QT and build an application or use terminal: `make install`

## Makefile targets

- `make all` - tests for calculation logic
- `make install` - for building an application
- `make uninstall` - for deleting application
- `make gcov_report` - test coverage report in html format
- `make dvi` - documentation
- `make dist` - creates a .tar.gz archive of an application
- `make leaks/valgrind` - leaks check for calculation logic
- `make clang` - linter
