subdir('native')




sources = files('effect_pass.cpp', 'effect.cpp')

effects_lib = static_library('effects', sources,
    dependencies: global_deps,
    link_whole: native_lib
)