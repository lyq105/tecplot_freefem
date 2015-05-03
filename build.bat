del fftecplot.o fftecplot3d.o fftecplot.dll
mingw32-g++ -c  -DNDEBUG -O3 -DBAMG_LONG_LONG -DNCHECKPTR -Iff_include -Itec_include  fftecplot.cpp

mingw32-g++ -shared -Wl,--enable-auto-import  -DNDEBUG -O3 -DBAMG_LONG_LONG -DNCHECKPTR fftecplot.o  -o fftecplot.dll libff.dll FreeFem++-api.dll tecio.lib

FreeFem++ teciotest.edp
pause
