# MiniLibX (macOS / Metal / Swift) build.
# Patched from the original (Makefile.orig) so it builds on modern Swift
# toolchains (Swift 6.x). The original rule emitted both an object and a
# module to the SAME output path, which newer swiftc rejects with
# "multiple producers for output". Here each Swift unit emits its object
# via -o and its module via -emit-module-path (distinct paths), and the
# module dependency order (image -> window -> init -> interface) is
# enforced through object-file prerequisites.

NAME = libmlx.dylib

INC = -I.
OPTI = -O

C_SRC = mlx_xpm.c mlx_png.c mlx_string_put.c
C_OBJ = $(C_SRC:.c=.o)
CFLAGS = -O3

SWIFT_OBJ = mlx_image.o mlx_window.o mlx_init.o interface.o

all: $(NAME)

$(NAME): $(SWIFT_OBJ) $(C_OBJ)
	swiftc $(OPTI) $(INC) -o $(NAME) -emit-library $(SWIFT_OBJ) $(C_OBJ) -lz

mlx_image.o: mlx_image.swift
	swiftc $(OPTI) $(INC) -parse-as-library -emit-object -emit-module \
		-emit-module-path mlx_image.swiftmodule -module-name mlx_image \
		mlx_image.swift -o mlx_image.o

mlx_window.o: mlx_window.swift mlx_image.o
	swiftc $(OPTI) $(INC) -parse-as-library -emit-object -emit-module \
		-emit-module-path mlx_window.swiftmodule -module-name mlx_window \
		mlx_window.swift -o mlx_window.o

mlx_init.o: mlx_init.swift mlx_window.o mlx_image.o
	swiftc $(OPTI) $(INC) -parse-as-library -emit-object -emit-module \
		-emit-module-path mlx_init.swiftmodule -module-name mlx_init \
		mlx_init.swift -o mlx_init.o

interface.o: interface.swift mlx_init.o mlx_window.o mlx_image.o
	swiftc $(OPTI) $(INC) -parse-as-library -emit-object \
		interface.swift -o interface.o

%.o: %.c
	cc $(CFLAGS) $(INC) -c $< -o $@

clean:
	rm -f $(NAME) $(SWIFT_OBJ) $(C_OBJ) *.swiftmodule *.swiftdoc *~

re: clean all

.PHONY: all clean re
