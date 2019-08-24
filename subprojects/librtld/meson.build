project('librtld', 
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
    'source/exception_handler.cpp',
    'source/header.s',
    'source/ld.cpp',
    'source/ModuleObject.cpp',
    'source/relocation.cpp',
    'source/utils.cpp',
]

extra_c_flags = ['-fuse-ld=lld',  '-fno-stack-protector', '-ffreestanding', '-nostdlib', '-nodefaultlibs', '-Wno-unused-command-line-argument', '-Wno-gcc-compat', '-Wall', '-Wextra']
extra_cpp_flags = extra_c_flags + ['-fno-rtti' , '-fomit-frame-pointer',  '-fno-exceptions', '-fno-asynchronous-unwind-tables', '-fno-unwind-tables']
target_cpu_familly = target_machine.cpu_family()
arch = meson.get_cross_property('arch')

if target_cpu_familly == 'aarch64'
    arch_sources = ['source/aarch64/crt0.s', 'source/aarch64/dl_trampoline.s', 'source/aarch64/svc.s']
elif target_cpu_familly == 'arm'
    arch_sources = ['source/aarch32/crt0.s', 'source/aarch32/dl_trampoline.s', 'source/aarch32/svc.s']
else
    error('Unsuported target cpu_familly')
endif

library_directory = '@0@/@1@'.format(get_option('prefix'), get_option('libdir'))
compiler_rt_builtins_dependency = cc.find_library('clang_rt.builtins', dirs: [library_directory], required: true)
include_directories = include_directories('include', 'misc/system/include', 'misc/@0@'.format(arch))

librtld_static_library = static_library(
    'rtld',
    common_sources + arch_sources,
    include_directories: include_directories,
    c_args: extra_c_flags,
    cpp_args: extra_cpp_flags,
    dependencies: [compiler_rt_builtins_dependency],
    pic: true,
    install: true
)
