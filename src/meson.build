subdir('components')
subdir('rendering')




sources = files('spring.cpp', 'scene.cpp', 'texture_sample.cpp')

static_library('flustral', sources,
    dependencies: global_deps,
    link_with: [components_lib, rendering_lib]
)