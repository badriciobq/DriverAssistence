JNI_PATH := $(call my-dir)
LOCAL_PATH := $(JNI_PATH)

TESSERACT_PATH := $(LOCAL_PATH)/com_googlecode_tesseract_android/src
LEPTONICA_PATH := $(LOCAL_PATH)/com_googlecode_leptonica_android/src
LIBPNG_PATH := $(LOCAL_PATH)/libpng
TRAFFICSIGN_PATH := $(LOCAL_PATH)/TrafficSign

# Just build the Android.mk files in the subdirs
include $(call all-subdir-makefiles)

LOCAL_PATH := $(JNI_PATH)
include $(CLEAR_VARS)

OPENCV_ROOT:=/home/badricio/Downloads/opencv-3.0.0/OpenCV-android-sdk
OPENCV_CAMERA_MODULES:=on
OPENCV_INSTALL_MODULES:=on
OPENCV_LIB_TYPE:=SHARED
include ${OPENCV_ROOT}/sdk/native/jni/OpenCV.mk


LOCAL_MODULE     := adas

LOCAL_SRC_FILES  += \
    adas.cpp \
    TrafficSign/Monitor.cpp \
    TrafficSign/Processor.cpp

LOCAL_C_INCLUDES += \
   $(LOCAL_PATH) \
   $(TESSERACT_PATH)/api \
   $(TESSERACT_PATH)/ccmain \
   $(TESSERACT_PATH)/ccstruct \
   $(TESSERACT_PATH)/ccutil \
   $(TESSERACT_PATH)/classify \
   $(TESSERACT_PATH)/cube \
   $(TESSERACT_PATH)/cutil \
   $(TESSERACT_PATH)/dict \
   $(TESSERACT_PATH)/opencl \
   $(TESSERACT_PATH)/neural_networks/runtime \
   $(TESSERACT_PATH)/textord \
   $(TESSERACT_PATH)/viewer \
   $(TESSERACT_PATH)/wordrec \
   $(LEPTONICA_PATH)/src \
   $(TRAFFICSIGN_PATH)


LOCAL_LDLIBS    += -landroid -llog -ldl
LOCAL_SHARED_LIBRARIES += libtess

LOCAL_STATIC_LIBRARIES := cpufeatures

LOCAL_ARM_MODE := arm

include $(BUILD_SHARED_LIBRARY)

$(call import-module,android/cpufeatures)
