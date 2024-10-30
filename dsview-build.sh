# mkdir DSView-1.3.0/build && cd DSView-1.3.0/build
# cmake -DCMAKE_INSTALL_PREFIX=`pwd`/../destdir ..
# edit CMakeLists.txt or cmake_install.cmake for the line 'install(FILES DSView/DSView.desktop'

log_d () {
  echo "[Debug] $*"
}

log_e () {
  echo "[ERROR] $*"
}

if [ -f "CMakeLists.txt" ]; then
  log_d "Assume CURDIR is repo, here use to ./build for building"
  mkdir -p build || { log_e "Failed create ./build"; exit 1; }
  cd build || { log_e "Failed enter ./build"; exit 1; }
elif [ ! -f "../CMakeLists.txt" ]; then
  log_e "Not subdirectory of repo"
  exit 1
fi

DESTDIR=$(realpath ../destdir)

cmake "-DCMAKE_INSTALL_PREFIX=${DESTDIR}" .. \
  || { log_e "Failed cmake"; exit 1; }
make -j8 || { log_e "Failed make"; exit 1; }
make install || { log_e "Failed make install"; exit 1; }

log_d "Installed to ${DESTDIR}"
