project "glad"          -- glad 프로젝트입니다.
    kind "StaticLib"    -- 프로젝트의 종류를 설정합니다.
    language "C"        -- 프로그래밍 언어를 설정합니다.

    flags { 
        "MultiProcessorCompile" -- 멀티 스레드 빌드를 활성화합니다.
    }

    includedirs {
        "%{thirdparty_directory}/glad/include", -- include 경로를 추가합니다.
    }

    files {
        "%{thirdparty_directory}/glad/include/**",  -- include 경로 하위의 파일들을 추가합니다.
        "%{thirdparty_directory}/glad/src/**",      -- src 경로 하위의 파일들을 추가합니다.
    }

    disablewarnings { 
        "4996", -- C4996 경고를 비활성화합니다.
    }

    filter "configurations:Debug" -- 프로젝트의 Debug 모드 설정을 수행합니다.
        defines { "DEBUG", }
        runtime  "Debug"
        optimize "Off"
        symbols "On"

    filter "configurations:Release" -- 프로젝트의 Release 설정을 수행합니다.
        defines { "NDEBUG", "RELEASE", }
        runtime "Release"
        optimize "On"
        symbols "On"

    filter "configurations:Shipping"  -- 프로젝트의 Shipping 설정을 수행합니다.
        defines { "NDEBUG", "SHIPPING", }
        runtime "Release"
        optimize "Full"
        symbols "Off"

project "jsoncpp"       -- jsoncpp 프로젝트입니다.
    kind "StaticLib"    -- 프로젝트의 종류를 설정합니다.
    language "C++"      -- 프로그래밍 언어를 설정합니다.
    cppdialect "C++17"  -- C++의 표준을 설정합니다.

    flags { 
        "MultiProcessorCompile" -- 멀티 스레드 빌드를 활성화합니다.
    }

    includedirs {
        "%{thirdparty_directory}/jsoncpp/include", -- include 경로를 추가합니다.
    }

    files {
        "%{thirdparty_directory}/jsoncpp/include/**", -- include 경로 하위의 파일들을 추가합니다.
        "%{thirdparty_directory}/jsoncpp/src/**",     -- src 경로 하위의 파일들을 추가합니다.
    }

    disablewarnings { 
        "4996", -- C4996 경고를 비활성화합니다.
    }

    filter "configurations:Debug" -- 프로젝트의 Debug 모드 설정을 수행합니다.
        defines { "DEBUG", }
        runtime  "Debug"
        optimize "Off"
        symbols "On"

    filter "configurations:Release" -- 프로젝트의 Release 설정을 수행합니다.
        defines { "NDEBUG", "RELEASE", }
        runtime "Release"
        optimize "On"
        symbols "On"

    filter "configurations:Shipping" -- 프로젝트의 Shipping 설정을 수행합니다.
        defines { "NDEBUG", "SHIPPING", }
        runtime "Release"
        optimize "Full"
        symbols "Off"

project "miniaudio"     -- miniaudio 프로젝트입니다.
    kind "StaticLib"    -- 프로젝트의 종류를 설정합니다.
    language "C++"      -- 프로젝트의 프로그래밍 언어를 설정합니다.
    cppdialect "C++17"  -- C++의 표준을 설정합니다.

    flags { 
        "MultiProcessorCompile",  -- 멀티 스레드 빌드를 활성화합니다.
    }

    includedirs {
        "%{thirdparty_directory}/miniaudio/include", -- include 경로를 추가합니다.
    }

    files {
        "%{thirdparty_directory}/miniaudio/include/**", -- include 경로 하위의 파일들을 추가합니다.
        "%{thirdparty_directory}/miniaudio/src/**",     -- src 경로 하위의 파일들을 추가합니다.
    }

    disablewarnings { 
        "4996", -- C4996 경고를 비활성화합니다.
    }

    filter "configurations:Debug" -- 프로젝트의 Debug 모드 설정을 수행합니다.
        defines { "DEBUG", }
        runtime  "Debug"
        optimize "Off"
        symbols "On"

    filter "configurations:Release" -- 프로젝트의 Release 설정을 수행합니다.
        defines { "NDEBUG", "RELEASE", }
        runtime "Release"
        optimize "On"
        symbols "On"

    filter "configurations:Shipping" -- 프로젝트의 Shipping 설정을 수행합니다.
        defines { "NDEBUG", "SHIPPING", }
        runtime "Release"
        optimize "Full"
        symbols "Off"
    
project "stb"           -- stb 프로젝트입니다.
    kind "StaticLib"    -- 프로젝트의 종류를 설정합니다.
    language "C++"      -- 프로젝트의 프로그래밍 언어를 설정합니다.
    cppdialect "C++17"  -- C++의 표준을 설정합니다.

    flags { 
        "MultiProcessorCompile",  -- 멀티 스레드 빌드를 활성화합니다.
    }

    includedirs {
        "%{thirdparty_directory}/stb/include", -- include 경로를 추가합니다.
    }

    files {
        "%{thirdparty_directory}/stb/include/**", -- include 경로 하위의 파일들을 추가합니다.
        "%{thirdparty_directory}/stb/src/**", -- src 경로 하위의 파일들을 추가합니다.
    }

    disablewarnings { 
        "4996", -- C4996 경고를 비활성화합니다.
    }
    
    filter "configurations:Debug" -- 프로젝트의 Debug 모드 설정을 수행합니다.
        defines { "DEBUG", }
        runtime  "Debug"
        optimize "Off"
        symbols "On"

    filter "configurations:Release" -- 프로젝트의 Release 모드 설정을 수행합니다.
        defines { "NDEBUG", "RELEASE", }
        runtime "Release"
        optimize "On"
        symbols "On"

    filter "configurations:Shipping" -- 프로젝트의 Shipping 모드 설정을 수행합니다.
        defines { "NDEBUG", "SHIPPING", }
        runtime "Release"
        optimize "Full"
        symbols "Off"