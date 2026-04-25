subdir('components')
subdir('rendering')




sources = files('main.cpp', 'spring.cpp', 'scene.cpp')

executable('flustral', sources,
    dependencies: global_deps,
    link_with: [components_lib, rendering_lib]
)