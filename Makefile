# all:  errors symbols directives opcodes main
all:  main

main: main.c headers.h errors.c symbols.c directives.c opcodes.c 
	gcc -o main main.c errors.c symbols.c directives.c opcodes.c

# symbols: symbols.c headers.h
# 	gcc -o symbols symbols.h

# opcodes:opcodes.c headers.h
# 	gcc -o opcodes opcodes.c

# directives: directives.c headers.h
# 	gcc -o directives directives.c

# errors: errors.c headers.h
# 	gcc -o errors errors.c

# test: main
# 	./main
