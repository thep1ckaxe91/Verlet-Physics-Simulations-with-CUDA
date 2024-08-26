#TODO: auto build with python
#multithread build object
import os
from threading import Thread

path = os.path.dirname(os.path.abspath(__file__))+'\\'
cpp_build_args = " -Iinclude -Imingw\\include"
obj_dir = path + "obj\\"

def build_cpp_to_obj(file : str):
    os.system(f"mingw\\bin\\g++ {cpp_build_args} -c {file}")
    name = file.split('\\')[-1]
    name = name[:len(name)-4]
    try:
        os.remove(obj_dir + name + ".o")
    except:
        pass
    os.rename(path + name+".o",obj_dir + name + ".o")

def build_cu_to_obj(file : str):
    os.system(f"nvcc {cpp_build_args} -c {file}")
    name = file.split('\\')[-1]
    name = name[:len(name)-3]
    try:
        os.remove(obj_dir + name + ".o")
    except:
        pass
    os.rename(path + name+".o",obj_dir + name + ".o")


#build all .cpp to .o
for root,dirs,files in os.walk("./"):
    if(root == "./src"):
        threads : list[Thread] = []
        for file in files:
            file_path = path + "src\\" + file
            if file.endswith(".cpp"):
                threads.append(Thread(target=build_cpp_to_obj,args=[file_path]))
            else:
                threads.append(Thread(target=build_cu_to_obj,args=[file_path]))
                
        for t in threads:
            t.start()
        for t in threads:
            t.join()

def all_object_file():
    res = " "
    for root,dirs,files in os.walk("./"):
        if root == "./obj":
            for file in files:
                res += obj_dir + file + " "
    return res

exe_build_command = f'mingw\\bin\\g++ -Iinclude {all_object_file()} -lmingw32 -lSDL2main -lSDL2 -o VPWC'

os.system(exe_build_command)

import subprocess

sim = subprocess.Popen("VPWC.exe")
sim.wait()