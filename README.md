# Confetti Engine

## Usage

## Setup

The project follows the (Nest)[https://github.com/Brocolarbre/Nest/] structure.
To build the project :
- Open a terminal in the **root folder** of the project
- Run the following command :
  - Windows : `.\scripts\windows\set_workspace.bat`
  - Linux : `./scripts/linux/set_workspace.sh`
- Open the project workspace
- Build the project
 
### Static and dynamic linkage

Any project that uses the the static version of the library shoud define the `LIBRARY_STATIC` macro.
To manually export the library as a shared library, the project should define the `LIBRARY_EXPORT` macro.
Using the library as a static library requires to link the external dependencies of the library (as only a dynamic library or an executable can store static dependencies).
The dependencies are listed below, the library is guaranteed to work with the specified library versions. Replacing a library with another version may or may not work.

### External dependencies

**Library** has the following external dependencies :
- Library name (Library version)

**Application** has the following external dependencies :
- Library name (Library version)