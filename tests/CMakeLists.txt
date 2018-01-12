cmake_minimum_required (VERSION 2.8)
FIND_PACKAGE ( Threads REQUIRED )

add_executable(rnt 
    tests_main.cpp
    tests_cell.cpp
)

target_link_libraries (rnt LINK_PUBLIC breaks)

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_BUILD_TYPE Debug)
add_definitions( -D_GLIBCXX_DEBUG )

target_compile_features(rnt PRIVATE 

    #cpp17
    cxx_aggregate_default_initializers
    cxx_alias_templates
    cxx_alignas
    cxx_alignof
    cxx_attributes
    #cpp17
    cxx_attribute_deprecated
    cxx_auto_type
    #cpp17
    cxx_binary_literals
    cxx_constexpr
    #cpp17
    cxx_contextual_conversions
    cxx_decltype_incomplete_return_types
    cxx_decltype
    #cpp17
    cxx_decltype_auto
    cxx_default_function_template_args
    cxx_defaulted_functions
    cxx_defaulted_move_initializers
    cxx_delegating_constructors
    cxx_deleted_functions
    #cpp17
    cxx_digit_separators
    cxx_enum_forward_declarations
    cxx_explicit_conversions
    cxx_extended_friend_declarations
    cxx_extern_templates
    cxx_final
    cxx_func_identifier
    cxx_generalized_initializers
    cxx_generic_lambdas
    cxx_inheriting_constructors
    cxx_inline_namespaces
    cxx_lambdas
    cxx_lambda_init_captures
    cxx_local_type_template_args
    cxx_long_long_type
    cxx_noexcept
    cxx_nonstatic_member_init
    cxx_nullptr
    cxx_override
    cxx_range_for
    cxx_raw_string_literals
    cxx_reference_qualified_functions
    #cpp17
    cxx_relaxed_constexpr
    #cpp17
    cxx_return_type_deduction
    cxx_right_angle_brackets
    cxx_rvalue_references
    cxx_sizeof_member
    cxx_static_assert
    cxx_strong_enums
    cxx_thread_local
    cxx_trailing_return_types
    cxx_unicode_literals
    cxx_uniform_initialization
    cxx_unrestricted_unions
    cxx_user_literals
    #cpp17
    cxx_variable_templates
    cxx_variadic_macros
    cxx_variadic_templates
    cxx_template_template_parameters )
