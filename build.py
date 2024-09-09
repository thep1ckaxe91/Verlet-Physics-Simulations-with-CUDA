# TODO: auto build with python
# multithread build object
import os
from threading import Thread

path = os.path.dirname(os.path.abspath(__file__)) + "\\"
cpp_build_args = " -Iinclude -Imingw\\include"
obj_dir = path + "obj\\"


def build_cpp_to_obj(file: str):
    os.system(f"mingw\\bin\\g++ {cpp_build_args} -c {file}")
    name = file.split("\\")[-1]
    name = name[: len(name) - 4]
    try:
        os.remove(obj_dir + name + ".o")
    except:
        pass
    try:
        os.rename(path + name + ".o", obj_dir + name + ".o")
    except:
        print()
        print("+--------------+")
        print("| Build failed |")
        print("+--------------+")
        print()


def build_cu_to_obj(file: str):
    os.system(f"nvcc {cpp_build_args} -c {file}")
    name = file.split("\\")[-1]
    name = name[: len(name) - 3]
    try:
        os.remove(obj_dir + name + ".o")
    except:
        pass
    try:
        os.rename(path + name + ".o", obj_dir + name + ".o")
    except:
        print()
        print("+--------------+")
        print("| Build failed | -----> Check error message")
        print("+--------------+")
        print()


# build all .cpp to .o
threads: list[Thread] = []
for root, dirs, files in os.walk("./"):
    if root == "./src":
        for file in files:
            file_path = path + "src\\" + file
            if file.endswith(".cpp"):
                threads.append(Thread(target=build_cpp_to_obj, args=[file_path]))
            else:
                threads.append(Thread(target=build_cu_to_obj, args=[file_path]))
    elif root == "./include\\engine":
        threads: list[Thread] = []
        for file in files:
            file_path = path + "include\\engine\\" + file
            if file.endswith(".cpp"):
                threads.append(Thread(target=build_cpp_to_obj, args=[file_path]))
            elif file.endswith(".cu"):
                threads.append(Thread(target=build_cu_to_obj, args=[file_path]))

for t in threads:
    t.start()
for t in threads:
    t.join()

print()
print("+--------------------+")
print("| Compile phase done |")
print("+--------------------+")
print()
def all_object_file():
    res = " "
    for root, dirs, files in os.walk("./"):
        if root == "./obj":
            for file in files:
                res += obj_dir + file + " "
    return res


exe_build_command = (
    f"mingw\\bin\\g++ -O3 -Iinclude {all_object_file()} -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -o ./build/VPWC"
)

os.system(exe_build_command)

import subprocess
try:
    sim = subprocess.Popen("build/VPWC.exe")
    sim.wait()
except:
    print()
    print("+--------------+")
    print("| Build failed | -----> Check error message")
    print("+--------------+")
    print()