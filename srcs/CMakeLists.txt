# Add executable called "helloDemo" that is built from the source files
# "demo.cxx" and "demo_b.cxx". The extensions are automatically found.
add_executable(lem-in main.c error.c acquisition.c parsing.c solving.c bfs.c paths.c parsing2.c)
# Link the executable to the Hello library. Since the Hello library has
# public include directories we will use those link directories when building
# helloDemo
target_link_libraries (lem-in LINK_PUBLIC libft)
