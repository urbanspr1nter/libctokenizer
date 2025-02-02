tokenizer:
	gcc -g main.c c_tokenizer.c modules/libcstring/src/c_string.c -o tokenizer

tokenizer-debug:
	gcc -g -fsanitize=address -Wall -Wextra main.c c_tokenizer.c modules/libcstring/src/c_string.c -o tokenizer

clean:
	rm tokenizer