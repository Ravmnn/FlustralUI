subdir('native')




sources = files('effect_pass.cpp')

effects_lib = static_library('effects', sources,
    dependencies: global_deps,
    link_with: native_lib
)