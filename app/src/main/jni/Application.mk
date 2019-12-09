APP_STL := gnustl_static
APP_CFLAGS += -Wno-error=format-security
APP_CPPFLAGS := -frtti -fexceptions
APP_ABI := arm64-v8a
APP_PLATFORM := latest
APP_ALLOW_MISSING_DEPS := true


#APP_STL := c++_static
#APP_CFLAGS += -Wno-error=format-security
#APP_CPPFLAGS := $(MY_CPPFLAGS) -frtti -std=c++11 -fsigned-char
#APP_LDFLAGS := -L$(STL_PATH) -latomic
#APP_ABI := arm64-v8a
#APP_PLATFORM := android-29
#APP_ALLOW_MISSING_DEPS := true