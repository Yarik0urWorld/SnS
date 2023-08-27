INSTALL_PATH=/usr/local/bin
INCLUDE_PATH=../include
BUILD_PATH=../build
SOURCE_DIRS=objs lowlevel assets

GEN_MODELS=${BUILD_PATH}/gen_models

MDL_OBJ_FILES=snowman.mdl.o gas.mdl.o
OBJ_FILES=main.o appearance.o bullet_t.o utils.o lowlevel/lowlevel_gl.o lowlevel/lowlevel_glut.o objs/bullet.o objs/enemy.o objs/gun.o objs/snowman.o assets/obj_loader.o models.o logs.o ${MDL_OBJ_FILES}
DEPENDENCIES=${GEN_MODELS}

TARGET_N=sns

include glut-project.mk

${GEN_MODELS}: ${BUILD_PATH}/gen_models.o
	make -f gen_models.mk

${BUILD_PATH}/%.mdl.c: ${GEN_MODELS}
	${GEN_MODELS}

${BUILD_PATH}/%.mdl.o: ${BUILD_PATH}/%.mdl.c
	${CC} ${CFLAGS} $^ -o $@

.PRECIOUS: ${BUILD_PATH}/%.mdl.c
