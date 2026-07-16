NAME		= miniRT

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -O3
INCLUDES	= -I includes

UNAME		:= $(shell uname)

ifeq ($(UNAME), Darwin)
	MLX_DIR		= minilibx_mms_20200219
	MLX_LIB		= $(MLX_DIR)/libmlx.dylib
	MLX_FLAGS	= -L $(MLX_DIR) -lmlx -framework AppKit -framework Metal \
				  -framework MetalKit -Wl,-rpath,@executable_path/$(MLX_DIR)
	INCLUDES	+= -I $(MLX_DIR)
else
	MLX_DIR		= minilibx-linux
	MLX_LIB		= $(MLX_DIR)/libmlx.a
	MLX_FLAGS	= -L $(MLX_DIR) -lmlx -lXext -lX11
	INCLUDES	+= -I $(MLX_DIR)
endif

SRC_DIR		= src
OBJ_DIR		= obj

SRCS		= \
	main.c \
	math/vec3_basic.c \
	math/vec3_ops.c \
	math/vec3_util.c \
	math/color.c \
	window/window.c \
	window/hooks.c \
	window/platform.c \
	render/render.c \
	render/camera.c \
	render/trace.c \
	intersect/inter_sphere.c \
	intersect/inter_plane.c \
	intersect/inter_cylinder.c \
	intersect/inter_cyl_caps.c \
	light/lighting.c \
	light/shadow.c \
	parse/parser.c \
	parse/parse_element.c \
	parse/parse_object.c \
	parse/parse_atom.c \
	parse/parse_num.c \
	scene/scene.c \
	scene/validate.c \
	utils/error.c \
	utils/ft_string.c \
	utils/split_set.c \
	utils/read_file.c

OBJS		= $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

all: $(NAME)

$(NAME): $(MLX_LIB) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(MLX_FLAGS) -lm -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c includes/minirt.h
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(MLX_LIB):
ifeq ($(UNAME), Darwin)
	@$(MAKE) -C $(MLX_DIR)
	@install_name_tool -id @rpath/libmlx.dylib $(MLX_LIB) 2>/dev/null || true
else
	@$(MAKE) -C $(MLX_DIR)
endif

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

mlxclean:
	@$(MAKE) -C $(MLX_DIR) clean 2>/dev/null || true

re: fclean all

bonus: all

.PHONY: all clean fclean re bonus mlxclean
