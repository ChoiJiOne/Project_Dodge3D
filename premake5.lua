if _ARGS[1] then -- 프로젝트 이름이 인자로 전달되었는지 확인합니다.
    game_project = _ARGS[1]
    print(string.format("Setting '%s' visual studio solution name...", game_project))
else
    print("Missing visual studio solution name...")
    os.exit()
end

root_directory = _MAIN_SCRIPT_DIR                                         -- 프로젝트 루트 디렉토리입니다.
engine_directory = "%{root_directory}/GameEngine"                         -- 게임 엔진 디렉토리입니다.
game_directory = "%{root_directory}/%{game_project}"                      -- 게임 프로젝트 디렉토리입니다.
thirdparty_directory = "%{engine_directory}/ThirdParty"                   -- 서드 파티 라이브러리 디렉토리입니다.

glad_path = "%{thirdparty_directory}/glad/include"                        -- glad 라이브러리 헤더 경로입니다.
jsoncpp_include_path = "%{thirdparty_directory}/jsoncpp/include"          -- jsoncpp 라이브러리 헤더 경로입니다.
lua_include_path = "%{thirdparty_directory}/Lua/include"                  -- Lua 라이브러리 헤더 경로입니다.
miniaudio_include_path = "%{thirdparty_directory}/miniaudio/include"      -- miniaudio 라이브러리 헤더 경로입니다.
stb_include_path = "%{thirdparty_directory}/stb/include"                  -- stb 라이브러리 헤더 경로입니다.

shader_path = "%{wks.location}..\\GameEngine\\Shader\\"                   -- 셰이더 파일 경로입니다.
resource_path = "%{wks.location}..\\%{game_project}\\Resource\\"          -- 프로젝트 리소스 파일 경로입니다.

workspace "%{game_project}" -- 게임 개발 작업 영역입니다.

    configurations {    -- 빌드 구성 요소입니다.
        "Debug",        -- Debug 요소입니다. 빌드 시 최적화를 수행하지 않고, 디버그 정보(.pdb) 파일을 생성합니다.
        "Release",      -- Release 요소입니다. 빌드 시 최적화를 수행하지만, 디버그 정보(.pdb) 파일을 생성합니다.
        "Shipping"      -- Shipping 요소입니다. 빌드 시 최적화를 수행하고, 디버그 정보(.pdb) 파일을 생성하지 않습니다.
    }

    platforms { 
        "Win64" -- 플랫폼을 설정합니다.
    }

    location "%{root_directory}/Solution" -- 솔루션 경로를 설정합니다.
    startproject "%{game_project}" -- 시작 프로젝트를 설정합니다.

    include "GameEngine/ThirdParty/thirdparty_config.lua"   -- 서드 파티 라이브러리 프로젝트 설정을 추가합니다.
    include "GameEngine/project_config.lua"                 -- 게임 엔진 프로젝트 설정을 추가합니다.
    include "Breakout3D/project_config.lua"                 -- 시작 프로젝트 설정을 추가합니다.