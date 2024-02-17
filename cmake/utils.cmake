function(install_projects)
    install(TARGETS ${ARGN}
            EXPORT OpenAI_export
            COMPONENT "${PROJECT_NAME}"
            RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
            ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
            LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}")
endfunction()