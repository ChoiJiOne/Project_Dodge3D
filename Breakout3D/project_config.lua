project (game_project) -- 게임 프로젝트입니다.
        kind "WindowedApp" -- 프로젝트의 종류를 설정합니다.
        language "C++" -- 프로젝트의 프로그래밍 언어를 설정합니다.
        cppdialect "C++17" -- C++의 표준을 설정합니다.

        flags { 
            "MultiProcessorCompile", -- 멀티 스레드 빌드를 활성화합니다.
        }

        includedirs {
            "%{game_directory}/Source",  -- 게임 소스 파일 경로를 추가합니다.
            "%{game_directory}/Include", -- 게임 헤더 파일 경로를 추가합니다.

            "%{engine_directory}/Include", -- 엔진의 헤더 파일 경로를 추가합니다.

            "%{glad_path}",              -- glad 라이브러리 헤더 경로를 추가합니다.
            "%{lua_include_path}",       -- Lua 라이브러리 헤더 경로를 추가합니다.
            "%{jsoncpp_include_path}",   -- jsoncpp 라이브러리 헤더 경로를 추가합니다.
            "%{miniaudio_include_path}", -- miniaudio 라이브러리 헤더 경로를 추가합니다.
            "%{stb_include_path}",       -- stb 라이브러리 헤더 경로를 추가합니다.
        }
    
        files {
            "%{game_directory}/**", -- 게임 파일 경로를 추가합니다.
        }

        links {
            "GameEngine", -- 게임 엔진 라이브러리를 추가합니다.
        }

        disablewarnings { 
            "4996", -- C4996 경로를 비활성화합니다.
        }
        
        debugargs {
            "shader=%{shader_path}",
            "resource=%{resource_path}",
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