# Register the standard build
set(SOURCE_FILES
  "${CMAKE_CURRENT_LIST_DIR}/controller_comp.fpp"
  "${CMAKE_CURRENT_LIST_DIR}/controller_comp.cpp"

  "${CMAKE_CURRENT_LIST_DIR}/../../../examples/spring_mass_dumper/src/controller.cpp"
)

register_fprime_module()