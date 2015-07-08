from distutils.core import setup, Extension
from os import path

directory = path.dirname(path.realpath(__file__))

setup(
    name='imgen',
    version='0.1',
    description='Procedurally generated image library',
    ext_modules=[
        Extension('imgen',
                  include_dirs=['src/'],
                  libraries=['png', 'boost_python3'],
                  sources=[path.join(directory, './bindings.cpp')])
    ]
)
