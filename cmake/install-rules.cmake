install(
    TARGETS test_lab5_exe
    RUNTIME COMPONENT test_lab5_Runtime
)

if(PROJECT_IS_TOP_LEVEL)
  include(CPack)
endif()
