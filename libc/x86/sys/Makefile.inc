# $FreeBSD$

.PATH:	${LIBC_SRCTOP}/x86/sys

SRCS+= \
	__vdso_gettc.c \
	pkru.c

MAN+=	\
	pkru.3

.if ${MACHINE_CPUARCH} == "amd64" && ${MK_HYPERV} != "no"
CFLAGS+=	-DWANT_HYPERV
.endif
# We can't use sanitizer instrumentation on ifuncs called during sanitizer
# runtime startup.
.if ${MK_ASAN} != "no"
CFLAGS.__vdso_gettc.c+=-fno-sanitize=address
.endif
.if ${MK_UBSAN} != "no"
CFLAGS.__vdso_gettc.c+=-fno-sanitize=undefined
.endif
