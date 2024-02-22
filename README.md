# ProjectA - Dodge3D
- 3D 총알 피하기(Dodge3D) 게임 개발 프로젝트입니다.
<br><br>


## Table of Contents
- [ProjectA](#projecta)
  - [Table of Contents](#table-of-contents)
  - [Requirements](#requirements)
  - [How to get repository clone?](#how-to-get-repository-clone)
  - [How to Generate Visual Studio Solution?](#how-to-generate-visual-studio-solution)
    - [Visual Studio 2019](#visual-studio-2019)
    - [Visual Studio 2022](#visual-studio-2022)
  - [How to Build Solution?](#how-to-build-solution)
    - [Debug](#debug)
    - [Release](#release)
    - [RelWithDebInfo](#relwithdebinfo)
    - [MinSizeRel](#minsizerel)
  - [How to Run Dodge3D?](#how-to-run-dodge3d)
    - [Debug](#debug-1)
    - [Release](#release-1)
    - [RelWithDebInfo](#relwithdebinfo-1)
    - [MinSizeRel](#minsizerel-1)
  - [How to Package Project?](#how-to-package-project)
    - [Debug](#debug-2)
    - [Release](#release-2)
    - [RelWithDebInfo](#relwithdebinfo-2)
    - [MinSizeRel](#minsizerel-2)
  - [How to Play Game?](#how-to-play-game)
  - [License](#license)


## Requirements
- Windows 10/11 Home/Pro
- [Git](https://git-scm.com/)
- [Visual Studio 2019 or 2022](https://visualstudio.microsoft.com/ko/)
- [CMake 3.27 or later](https://cmake.org/download/)
<br><br>


## How to get repository clone?

`CMD` 혹은 `PowerShell`에서 다음 명령어를 수행하시면 리포지토리의 복사본을 얻을 수 있습니다.

```PowerShell
git clone https://github.com/ChoiJiOne/ProjectA_Dodge3D --single-branch -b develop
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
| RelWithDebInfo | 빌드 과정에서 최적화를 수행하고, 디버그 정보 파일(.pdb)을 생성합니다. |
| MinSizeRel  | 빌드 과정에서 최적화를 수행하고, 최소 크기로 최적화하며 디버그 정보 파일(.pdb)을 생성하지 않습니다. |

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

### MinSizeRel
```
Build_MinSizeRel.bat
```

> 단, 위의 스크립트 모두 `CMD` 혹은 `PowerShell`에서 실행하지 않고 그냥 실행해도 동작합니다.

<br><br>


## How to Run Dodge3D?

이 프로젝트는 Visual Studio를 실행하지 않은 상태에서 게임을 실행할 수 있는 기능을 지원합니다. 게임 실행 스크립트가 지원하는 모드는 `Debug`, `Release`, `RelWithDebInfo`, `MinSizeRel`으로 빌드 모드와 동일합니다. 따라서, `CMD` 혹은 `PowerShell`에서 다음 명령어를 수행하시면 각 모드에 따라 클라이언트를 실행할 수 있습니다.

> 단, 솔루션이 빌드되어 있어야 동작합니다. 빌드는 [여기](#how-to-build-solution)를 참조하세요.

### Debug
```
RunDodge3D_Debug.bat
```

### Release
```
RunDodge3D_Release.bat
```

### RelWithDebInfo
```
RunDodge3D_RelWithDebInfo.bat
```

### MinSizeRel
```
RunDodge3D_MinSizeRel.bat
```

> 단, 위의 스크립트 모두 `CMD` 혹은 `PowerShell`에서 실행하지 않고 그냥 실행해도 동작합니다.

<br><br>


## How to Package Project?

이 프로젝트는 사용자 머신에 프로젝트가 설치 가능하도록 하는 exe 파일을 생성할 수 있는 기능을 지원합니다. 이때, [NSIS (nullsoft scriptable install system)](https://nsis.sourceforge.io/Main_Page)가 설치되어 있고, 설치 경로가 환경변수에 등록되어 있어야 사용할 수 있습니다. 이 패키징 스크립트가 지원하는 모드는 `Debug`, `Release`, `RelWithDebInfo`, `MinSizeRel`으로 빌드 모드와 동일합니다. 따라서, `CMD` 혹은 `PowerShell`에서 다음 명령어를 수행하시면 각 모드에 맞는 패키지 파일을 얻을 수 있습니다.

> 단, 솔루션이 빌드되어 있어야 동작합니다. 빌드는 [여기](#how-to-build-solution)를 참조하세요.

> NSIS의 경로가 환경변수에 등록되어 있지 않으면 이 기능을 사용하실 수 없습니다. 

### Debug
```
Package_Debug.bat
```

### Release
```
Package_Release.bat
```

### RelWithDebInfo
```
Package_RelWithDebInfo.bat
```

### MinSizeRel
```
Package_MinSizeRel.bat
```

> 단, 위의 스크립트 모두 `CMD` 혹은 `PowerShell`에서 실행하지 않고 그냥 실행해도 동작합니다.

<br><br>


## How to Play Game?

이 프로젝트의 게임을 플레이 하기 위해서는 [여기](https://github.com/ChoiJiOne/ProjectA_Dodge3D/releases/tag/release)에서 `Dodge3D-win64.exe`를 다운로드 받은 후에 msi 파일을 실행해서 설치를 진행합니다. 그 다음 설치한 폴더에 있는 `Dodge3D.exe`를 실행하면 게임을 실행할 수 있습니다. 게임을 시작하면 버튼은 마우스 우클릭으로 할 수 있고, 방향키로 조작 가능합니다. ESC 키를 누르면 게임을 일시중지 시킬 수 있습니다.

> 관리자 권한으로 실행해야 플레이 기록을 저장할 수 있습니다.

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
