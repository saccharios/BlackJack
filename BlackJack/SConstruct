#!python
import os


env = Environment(ENV = os.environ, tools = ['mingw'])
path = ['C:\\MinGW_63\\bin']
env.PrependENVPath('PATH', path)
env.Append(CXXFLAGS='--std=c++17') 

build_dir = 'build'
SConscript('src/SConscript', variant_dir=build_dir, duplicate=0, exports = 'env')