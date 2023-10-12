UNAME_S=$(shell uname -s)
ARCH=$(shell arch)

#INSTALL_PATH=/usr/local/bin
#INCLUDE_PATH=../include
#BUILD_PATH=../build
#SOURCE_DIRS=objs lowlevel assets

#OBJ_FILES=main.o appearance.o bullet_t.o utils.o lowlevel/lowlevel_gl.o lowlevel/lowlevel_glut.o objs/bullet.o objs/enemy.o objs/gun.o objs/snowman.o
#OBJ_FILES=gen_models.o

CC=gcc
CFLAGS+=-I"${INCLUDE_PATH}" -c -O3 -Wall -Wno-pointer-sign
# get rid of -ffast-math at first time cuz I'm afraid of it :>
LFLAGS+=
STATIC_LIB_PATH+=
ifeq (${STATIC_LIB_PATH},)
	STATIC_LIB_PATH=/usr/lib/${ARCH}-linux-gnu
endif
#STATIC_LIB_PATH2=/usr/local/lib/sns-libs
STATIC_LIBS+=libGLU.a libglut.a libXi.a libXext.a libXxf86vm.a

TARGET=${BUILD_PATH}/${TARGET_N}

ifeq (${UNAME_S},Darwin)
	LIBS+=-framework OpenGL -framework GLUT -framework Cocoa
	CFLAGS+=-Wno-deprecated-declarations
else
	ifeq (${STATIC_BUILD},true)
#		LIBS+=-lGL -lm -lX11 -lGLU -lXi -lXxf86vm
		LIBS+=$(addprefix ${STATIC_LIB_PATH}/,${STATIC_LIBS}) -lGL -lm -lX11
	else
		LIBS+=-lGL -lGLU -lglut -lm
	endif
endif

all: ${TARGET}

OBJ_FILES_IN_BUILD_PATH=$(addprefix ${BUILD_PATH}/,${OBJ_FILES})

${TARGET}: ${OBJ_FILES_IN_BUILD_PATH} ${DEPENDENCIES}
	$(CC) $(LFLAGS) ${OBJ_FILES_IN_BUILD_PATH} -o $@ $(LIBS)

${BUILD_PATH}/%.o: %.c | $(addprefix ${BUILD_PATH}/,${SOURCE_DIRS})
	$(CC) $(CFLAGS) $< -o $@

$(addprefix ${BUILD_PATH}/,${SOURCE_DIRS}): ${BUILD_PATH}/%:
	mkdir -p $@

run: ${TARGET}
	${TARGET}

clean:
	rm -rf ${BUILD_PATH} *.mdl.c

install:
	mv -f ${TARGET} ${INSTALL_PATH}

uninstall:
	rm -f ${INSTALL_PATH}/$(notdir ${TARGET})

.PHONY: all clean install run
