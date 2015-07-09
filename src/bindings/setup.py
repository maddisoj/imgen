from distutils.core import setup, Extension
from os import path

bindings_dir = path.dirname(path.realpath(__file__))
imgen_dir = path.join(bindings_dir, "../imgen")

setup(
    name='imgen',
    version='0.1',
    description='Procedurally generated image library',
    ext_modules=[
        Extension(
            'imgen',
            include_dirs=['src/'],
            libraries=['png', 'boost_python3'],
            extra_compile_args=['-std=c++11'],
            sources=[
                path.join(bindings_dir, './bindings.cpp'),
                path.join(imgen_dir, './color.cpp')
            ]
        )
    ]
)
