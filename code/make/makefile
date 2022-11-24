CXX = g++
CXXFLAGS = -g
EXEC = output
# source file directory
SRC = ../src
#header file directory
HDR = ../include

OBJS = main.o functions.o
${EXEC}: ${OBJS}
	${CXX} ${CXXFLAGS} -o ${EXEC} ${OBJS}
functions.o: $(SRC)/client/functions.C $(HDR)/classes.h
	${CXX} ${CXXFLAGS} -c $(SRC)/client/functions.C
main.o: $(SRC)/client/main.C $(HDR)/classes.h $(HDR)/Logger.h
	${CXX} ${CXXFLAGS} -c $(SRC)/client/main.C
clean: 
	rm *.o output



































# #compiler
# GCC = gcc
# #output file
# LFLAGS = -o
# #binary file directory
# BIN = ../bin
# #source file directory
# SRC = ../src
# #object file directory
# OBJ = ../obj
# #header file directory
# HDR = ../include

# #compile all source file
# all: buildserver buildclient 

# buildserver: $(OBJ)/smain.o
# 	$(GCC) $(LFLAGS) $(BIN)/server $(OBJ)/smain.o  $(HDR)/sheader.h
  
# # buildclient: $(OBJ)/client/cmain.o
# # 	$(GCC) $(LFLAGS) $(BIN)/client $(OBJ)/cmain.o $(HDR)/cheader.h

# $(OBJ)/smain.o: $(SRC)/server/server.C
# 	$(GCC) -c $(LFLAGS) $(OBJ)/smain.o $(SRC)/server/server.C

# # $(OBJ)/cmain.o: $(SRC)/client/main.C
# # 	$(GCC) -c $(LFLAGS) $(OBJ)/cmain.o  $(SRC)/client/main.C



# clean: 
# 	rm $(BIN)/server
# 	rm $(BIN)/client
# 	rm $(OBJ)/smain.o
# 	rm $(OBJ)/cmain.o