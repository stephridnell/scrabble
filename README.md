# scrabble

### To compile and run:
```
$ make
```

### To compile and run without Makefile:

```
$ gcc -Wall -pedantic -ansi board.c game.c helpers.c io.c player.c rules.c scrabble.c tile_list.c word_list.c -o scrabble
$ ./scrabble [wordfile] [tilefile]
$ ./scrabble words.len5 tiles.txt
```

### To zip project:
```
$ make archive
```
