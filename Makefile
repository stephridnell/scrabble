###############################################################################
# Student Name    :
# RMIT Student ID :
# COURSE CODE     :
#
# Startup code provided by Paul Miller for use in "Programming in C",
# study period 2, 2018.
###############################################################################

###############################################################################
# I have provided an "archive" target that will zip up your files for 
# submission. You will need to create an "all" target and various other targets
# that will ensure your program compiles, with separate compilation and linking
# targets. You will also need to create a "clean" target that deletes all files
# created as part of compilation. 
##############################################################################
SOURCES=board.c game.c helpers.c io.c tile_list.c player.c rules.c scrabble.c \
	word_list.c
HEADERS=board.h game.h helpers.h io.h tile_list.h player.h rules.h scrabble.h \
	shared.h word_list.h
archive:
	zip ${USER} ${SOURCES} ${HEADERS} Makefile
