subdir('effects')




sources = files('window_renderer.cpp')

rendering_lib = static_library('rendering', sources,
    dependencies: global_deps,
    link_with: effects_lib
)