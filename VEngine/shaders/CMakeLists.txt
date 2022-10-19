project(shaders)

add_custom_target (${PROJECT_NAME})

file(GLOB vs "${CMAKE_CURRENT_SOURCE_DIR}/*.vs.hlsl")
file(GLOB ps "${CMAKE_CURRENT_SOURCE_DIR}/*.ps.hlsl")

set_source_files_properties(${vs} PROPERTIES ShaderType "vs")
set_source_files_properties(${ps} PROPERTIES ShaderType "ps")
    
foreach(FILE ${vs} ${ps})
    get_filename_component(FILE_WE ${FILE} NAME_WE)
    get_source_file_property(shadertype ${FILE} ShaderType)
    add_custom_command(TARGET shaders
        COMMAND dxc.exe /nologo /Emain /T${shadertype}_6_0 $<IF:$<CONFIG:DEBUG>,/Od,/O3> /Zi /Fo ${CMAKE_CURRENT_BINARY_DIR}/${FILE_WE}.cso /Fd ${CMAKE_CURRENT_BINARY_DIR}/${FILE_WE}.pdb ${FILE}
    MAIN_DEPENDENCY ${FILE}
    COMMENT "HLSL ${FILE}"
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    VERBATIM)
endforeach(FILE)

