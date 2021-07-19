build: star_dust

star_dust: star_dust.c
	gcc -Wall -Wextra -std=c99 star_dust.c -o star_dust

clean:
	rm -f star_dust

