# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at https://mozilla.org/MPL/2.0/.

if(NOT TARGET @ALIAS_TARGET_NAME@::@PROJECT_NAME@)

  get_filename_component(@PROJECT_NAME@_PATH ${CMAKE_CURRENT_LIST_FILE} PATH)

  set(@PROJECT_NAME@_INCLUDE_DIR ${@PROJECT_NAME@_PATH}/../include)

  include(FindPackageHandleStandardArgs)
  find_package_handle_standard_args(@PROJECT_NAME@ DEFAULT_MSG
                                    @PROJECT_NAME@_INCLUDE_DIR)

  mark_as_advanced(@PROJECT_NAME@_INCLUDE_DIR)

  add_library(@ALIAS_TARGET_NAME@::@PROJECT_NAME@ IMPORTED INTERFACE GLOBAL)
  set_target_properties(@ALIAS_TARGET_NAME@::@PROJECT_NAME@
    PROPERTIES
      INTERFACE_INCLUDE_DIRECTORIES     "${@PROJECT_NAME@_INCLUDE_DIR}"
      IMPORTED_LINK_INTERFACE_LIBRARIES ""
      DEPLOYMENT_PATH                   "${@PROJECT_NAME@_PATH}/.."
      VERSION                           "@PROJECT_VERSION@")

endif()
