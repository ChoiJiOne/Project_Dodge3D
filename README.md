# DodgeBall
- `DodgeBall` is a project for developing a simple dodge ball game without using a game engine.

## Support Platform
- Windows 10/11 Home/Pro

## Dependencies
- [Git](https://git-scm.com/)
- [Visual Studio 2019 or 2022](https://visualstudio.microsoft.com/ko/)
- [CMake 3.27 or later](https://cmake.org/)
- [NSIS](https://nsis.sourceforge.io/Download)

## How to get repository clone?

You can obtain a copy of the repository using the following command.

```
git clone https://github.com/ChoiJiOne/DodgeBall.git
```

## How to generate Visual Studio solution?

To generate and run a Visual Studio solution, execute either `GenerateProjectFiles_vs2019.bat` or `GenerateProjectFiles_vs2022.bat`.
To only generate or update the Visual Studio solution, run either `HotReload_vs2019.bat` or `HotReload_vs2022.bat`.

> Make sure to execute the script that matches the installed version of Visual Studio.

## How to build solution?

This project supports building without running Visual Studio. The build script supports the following build modes: `Debug`, `Release`, `RelWithDebInfo`, and `MinSizeRel`, each with the following characteristics.

| mode | description |
|:---:|:---|
| Debug | No optimization is performed during the build process, and a debug information file (.pdb) is generated. |
| Release | Optimization is performed during the build process, and no debug information file (.pdb) is generated. |
| RelWithDebInfo | Optimization is performed during the build process, and a debug information file (.pdb) is generated. |
| MinSizeRel | Optimization is performed during the build process, with a focus on minimizing size, and no debug information file (.pdb) is generated. |

Therefore, you can perform the build for each mode by executing the following batch script.
- `Debug`
  ```
  Build_Debug.bat
  ```
- `Release`
  ```
  Build_Release.bat
  ```
- `RelWithDebInfo`
  ```
  Build_RelWithDebInfo.bat
  ```
- `MinSizeRel`
  ```
  Build_MinSizeRel.bat
  ```

## How to package project?

This project supports generating an exe file that allows the project to be installed on the user's machine. To use this feature, NSIS (Nullsoft Scriptable Install System) must be installed, and its installation path must be registered in the environment variables. The packaging script supports the same modes as the build modes: Debug, Release, RelWithDebInfo, and MinSizeRel. Therefore, by running the following commands in CMD or PowerShell, you can obtain the package file for each mode.

> However, the solution must be built for this to work. Please refer to [this section](#how-to-build-solution) for the build process.

> You will not be able to use this feature if the NSIS path is not registered in the environment variables.

- `Debug`
  ```
  Package_Debug.bat
  ```
- `Release`
  ```
  Package_Release.bat
  ```
- `RelWithDebInfo`
  ```
  Package_RelWithDebInfo.bat
  ```
- `MinSizeRel`
  ```
  Package_MinSizeRel.bat
  ```

## License

```
Copyright (c) 2024 Choi Ji One

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```
