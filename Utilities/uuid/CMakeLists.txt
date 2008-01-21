SET(UUID_SRCS
compare.c
gen_uuid.c
pack.c
parse.c
unpack.c
unparse.c
uuid_time.c
)

ADD_LIBRARY(uuid ${UUID_SRCS})
