install VTK with DVTK_MODULE_ENABLE_GUISupportQtQuick=WANT (String)  
For some reason LD_LIBRARY_PATH="path/to/qt/lib" needs to be set on linux otherwise libQtOpenGLWidgets.so won't get found by the dynamic linker
