project "GameEngine"    -- 게임 엔진 프로젝트입니다.
    kind "StaticLib"    -- 프로젝트의 종류를 설정합니다.
    language "C++"      -- 프로젝트의 프로그래밍 언어를 설정합니다.
    cppdialect "C++17"  -- C++의 표준을 설정합니다.

    flags { 
        "MultiProcessorCompile",  -- 멀티 스레드 빌드를 활성화합니다.
    }

    includedirs {
        "%{engine_directory}/Include", -- 엔진의 헤더 파일 경로를 추가합니다.
        "%{engine_directory}/Source",  -- 엔진의 소스 파일 경로를 추가합니다.

        "%{glad_path}",              -- glad 라이브러리 헤더 경로를 추가합니다.
        "%{jsoncpp_include_path}",   -- jsoncpp 라이브러리 헤더 경로를 추가합니다.
        "%{lua_include_path}",       -- Lua 라이브러리 헤더 경로를 추가합니다.
        "%{miniaudio_include_path}", -- miniaudio 라이브러리 헤더 경로를 추가합니다.
        "%{stb_include_path}",       -- stb 라이브러리 헤더 경로를 추가합니다.
    }
    
    files {
        "%{engine_directory}/*",
        "%{engine_directory}/Include/**",   -- 엔진 헤더 폴더 하위의 파일들을 추가합니다.
        "%{engine_directory}/Script/**",    -- 엔진 스크립트 폴더 하위의 파일들을 추가합니다.
        "%{engine_directory}/Shader/**",    -- 엔진 셰이더 폴더 하위의 파일들을 추가합니다.
        "%{engine_directory}/Source/**",    -- 엔진 소스 폴더 하위의 파일들을 추가합니다.
    }

    links {
        "Dbghelp.lib", -- 디버깅을 위한 라이브러리를 추가합니다.
        "opengl32.lib",
        "glad",
        "jsoncpp",
        "miniaudio",
        "stb",
        "%{thirdparty_directory}/Lua/lib/lua54.lib",
    }
    
    disablewarnings { 
        "4996", -- C4996 경고를 비활성화합니다.
    }

    filter "configurations:Debug" -- 프로젝트의 Debug 모드 설정을 수행합니다.
        defines { "DEBUG" }
        runtime  "Debug"
        optimize "Off"
        symbols "On"

    filter "configurations:Release" -- 프로젝트의 Release 설정을 수행합니다.
        defines { "NDEBUG", "RELEASE" }
        runtime "Release"
        optimize "On"
        symbols "On"

    filter "configurations:Shipping" -- 프로젝트의 Shipping 설정을 수행합니다.
        defines { "NDEBUG", "SHIPPING" }
        runtime "Release"
        optimize "Full"
        symbols "Off"