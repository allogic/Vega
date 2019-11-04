$programFiles = $Env:Programfiles
$currentDir = get-location

# BOOST
if (test-path "$programFiles/Boost") {
    remove-item -Recurse -Force "$programFiles/Boost"
    new-item -ItemType 'directory' -Path "$programFiles/Boost"
    push-location -Path "$programFiles/Boost"
    git clone --single-branch --branch master --recursive https://github.com/boostorg/build .
    ./bootstrap.bat
    #./b2 --prefix="$programFiles/Boost/build" install
    #./b2 --toolset=msvc --build-type=complete --architecture=x86 --address-model=32 stage #--with-headers --with-filesystem
    ./b2 stage
}

# VENDOR
if (-NOT (test-path "$currentDir/Vendor")) {
    new-item -ItemType 'directory' -Path "$currentDir/Vendor"
    push-location -Path "$currentDir/Vendor"
    git clone --single-branch --branch master https://github.com/Dav1dde/glad
    git clone --single-branch --branch master https://github.com/glfw/glfw
    git clone --single-branch --branch master https://github.com/g-truc/glm
    git clone --single-branch --branch docking https://github.com/ocornut/imgui
    git clone --single-branch --branch master https://github.com/assimp/assimp
    git clone --single-branch --branch master https://github.com/jbeder/yaml-cpp yaml
    push-location -Path "$currentDir/Vendor/glad"
    python -m glad --generator=c --out-path=gl
}

push-location -Path $currentDir