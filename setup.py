import os
import sys
import getopt
import shutil


def install(download):
    platform = sys.platform
    if platform == "win32":
        root = os.path.join(os.getcwd(), "Vega\\Vendor")
        if download:
            if os.path.exists(root) and os.path.isdir(root):
                shutil.rmtree(root)
            os.mkdir(root)
            os.chdir(root)
            os.system("git clone --single-branch --branch master https://github.com/Dav1dde/glad")
            os.system("git clone --single-branch --branch master https://github.com/glfw/glfw")
            os.system("git clone --single-branch --branch master https://github.com/g-truc/glm")
            os.system("git clone --single-branch --branch docking https://github.com/ocornut/imgui")
            os.system("git clone --single-branch --branch master https://github.com/assimp/assimp")
            os.system("git clone --single-branch --branch master https://github.com/jbeder/yaml-cpp")
            os.system("git clone --single-branch --branch v1.x https://github.com/gabime/spdlog")
            os.system("git clone --single-branch --branch v2.2.0 https://github.com/jarro2783/cxxopts")
        glad = os.path.join(root, "glad")
        os.chdir(glad)
        os.system("python -m glad --generator=c --out-path=gl")
    else:
        print(platform + " not supported")


try:
    opts, args = getopt.getopt(sys.argv[1:], ":", [
        "vendor",
        "download",
    ])
except getopt.GetoptError as err:
    print(err)
    sys.exit(2)

redownload = False

for opt, arg in opts:
    if opt in "--download":
        redownload = True

for opt, arg in opts:
    if opt in "--vendor":
        install(redownload)