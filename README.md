# ProjectA
- 3D 총알 피하기(Dodge3D) 게임 개발 프로젝트입니다.
<br><br>


## Table of Contents
- [Requirements](#requirements)
- [How to get repository clone?](#how-to-get-repository-clone)
- [How to Generate Visual Studio Solution?](#how-to-generate-visual-studio-solution)
- [How to Build Solution?](#how-to-build-solution)
- [How to Run Client?](#how-to-run-client)
- [License](#license)
<br><br>


## Requirements
- Windows 10/11 Home/Pro
- [Git](https://git-scm.com/)
- [Visual Studio 2019 or 2022](https://visualstudio.microsoft.com/ko/)
- [CMake 3.27 or later](https://cmake.org/download/)
- [Python 3.0 or later](https://www.python.org/downloads/)
<br><br>


## How to get repository clone?

`CMD` 혹은 `PowerShell`에서 다음 명령어를 수행하시면 리포지토리의 복사본을 얻을 수 있습니다.

```PowerShell
git clone https://github.com/ChoiJiOne/ProjectA --single-branch -b develop
```
<br><br>


## How to Generate Visual Studio Solution?

`CMD` 혹은 `PowerShell`에서 다음 명령어를 수행하시면 프로젝트의 Visual Studio 솔루션을 얻을 수 있습니다. 디렉토리 기준은 리포지토리의 복사본이 존재하는 폴더 기준입니다.

### Visual Studio 2019 
```
cd ProjectA
GenerateProjectFiles_vs2019.bat
```

### Visual Studio 2022
```
cd ProjectA
GenerateProjectFiles_vs2022.bat
```

> 단, 위의 스크립트 모두 `CMD` 혹은 `PowerShell`에서 실행하지 않고 그냥 실행해도 동작합니다.

<br><br>


## How to Build Solution?

이 프로젝트는 Visual Studio를 실행하지 않은 상태에서 빌드할 수 있는 기능을 지원합니다. 빌드 스크립트가 지원하는 빌드 모드는 `Debug`, `Release`, `RelWithDebInfo`, `MinSizeRel`으로, 각각의 특징은 다음과 같습니다.

| mode | description |
|:---:|:---|
| Debug | 빌드 과정에서 최적화를 수행하지 않고, 디버그 정보 파일(.pdb)을 생성합니다. |
| Release | 빌드 과정에서 최적화를 수행하고, 디버그 정보 파일(.pdb)을 생성하지 않습니다. |
| RelWithDebInfo | 빌드 과정에서 최적화를 수행하고, 디버그 정보 파일을 생성합니다. |
| MinSizeRel  | 빌드 과정에서 최적화를 수행하고, 최소 크기로 최적화하며 디버그 정보 파일을 생성하지 않습니다. |

따라서, `CMD` 혹은 `PowerShell`에서 다음 명령어를 수행하시면 각 모드에 따라 빌드를 수행할 수 있습니다.

### Debug
```
Build_Debug.bat
```

### Release
```
Build_Release.bat
```

### RelWithDebInfo
```
Build_RelWithDebInfo.bat
```

## MinSizeRel
```
Build_MinSizeRel.bat
```

> 단, 위의 스크립트 모두 `CMD` 혹은 `PowerShell`에서 실행하지 않고 그냥 실행해도 동작합니다.

<br><br>


## How to Run Client?

이 프로젝트는 Visual Studio를 실행하지 않은 상태에서 클라이언트를 실행할 수 있는 기능을 지원합니다. 클라이언트 실행 스크립트가 지원하는 모드는 `Debug`, `Release`, `RelWithDebInfo`, `MinSizeRel`으로 빌드 모드와 동일합니다. 따라서, `CMD` 혹은 `PowerShell`에서 다음 명령어를 수행하시면 각 모드에 따라 클라이언트를 실행할 수 있습니다.

> 단, 솔루션이 빌드되어 있어야 동작합니다. 빌드는 [여기](#how-to-build-solution)를 참조하세요.

### Debug
```
RunClient_Debug.bat
```

### Release
```
RunClient_Release.bat
```

### RelWithDebInfo
```
RunClient_RelWithDebInfo.bat
```

## MinSizeRel
```
RunClient_MinSizeRel.bat
```

> 단, 위의 스크립트 모두 `CMD` 혹은 `PowerShell`에서 실행하지 않고 그냥 실행해도 동작합니다.

<br><br>


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