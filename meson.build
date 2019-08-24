project('rtld', 
        ['c', 'cpp'],
        license: ['MIT'],
        default_options: ['c_std=c11', 'cpp_std=c++17', 'b_asneeded=false', 'b_lundef=false'],
        version: '0.0.0'
    )

# Check we are using clang
cc = meson.get_compiler('cpp')
assert(cc.get_id() == 'clang', 'This project only support the Clang compiler.')
assert(meson.is_cross_build(), 'This project is supposed to be cross compiled.')

common_sources = [
    'source/init.cpp',
    'source/main.cpp',
]

extra_c_flags = ['-fuse-ld=lld',  '-fno-stack-protector', '-ffreestanding', '-nostdlib', '-nodefaultlibs', '-Wno-unused-command-line-argument', '-Wno-gcc-compat', '-Wall', '-Wextra']
extra_cpp_flags = extra_c_flags + ['-fno-rtti' , '-fomit-frame-pointer',  '-fno-exceptions', '-fno-asynchronous-unwind-tables', '-fno-unwind-tables']
target_cpu_familly = target_machine.cpu_family()

link_args = meson.get_cross_property('link_args')
mapfile = 'exported.txt'
vflag = '-Wl,--version-script,@0@/@1@'.format(meson.current_source_dir(), mapfile)
tflags = '-Wl,-T,@0@/share/linker-scripts/@1@/module.ld'.format(get_option('prefix'), meson.get_cross_property('arch'))
hydrosphere_standalone_link_args = meson.get_cross_property('hydrosphere_standalone_link_args')
extra_ld_flags = hydrosphere_standalone_link_args + [vflag, tflags, '-fuse-ld=lld', '-Wl,-init=__rtld_init', '-Wl,-fini=__rtld_fini', '-Wl,-z,text', '-Wl,--build-id=sha1', '-Wl,--hash-style=sysv']

librtld_project = subproject('librtld')
librtld_static_library = librtld_project.get_variable('librtld_static_library')
include_directories = librtld_project.get_variable('include_directories')

rtld_shared_library = shared_library(
    'rtld',
    common_sources,
    name_prefix: '',
    include_directories: [include_directories, include_directories('include')],
    c_args: extra_c_flags,
    cpp_args: extra_cpp_flags,
    link_args: link_args + extra_ld_flags,
    link_with: [librtld_static_library],
    install: true
)

# NSO generation part
linkle_tool = find_program('linkle')

custom_target('rtld.nso',
    build_by_default: true,
    install: true,
    input: rtld_shared_library,
    output: 'rtld.nso',
    command: [linkle_tool, 'nso', '@INPUT@', '@OUTPUT@'],
    install_dir: get_option('libdir')
)
