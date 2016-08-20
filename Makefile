ROOT_PATH=$(shell pwd)
SERVER=serverd
CLIENT=clientd
DATA_POLL=data_poll

CC=g++
INCLUDE=-I$(ROOT_PATH)/data_pool -I$(ROOT_PATH)/lib/include -I$(ROOT_PATH)/commfunction
FLAGS=(INCLUDE)
LDFLAGS=$(LIB) -lpthread -ljsoncpp
LIB=-L$(ROOT_PATH)/lib/lib

SERVER_PATH=$(ROOT_PATH)/server
CLIENT_PATH=$(ROOT_PATH)/client
DATA_POOL_PAYH=$(ROOT_PATH)/data_pool
COMMFUNCTION_PATH=$(ROOT_PATH)/commfunction

SERVER_SRC=$(shell ls $(SERVER_PATH) | egrep '*.cpp' )
SERVER_SRC+=$(shell ls $(DATA_POOL_PATH) | egrep '*.cpp' )
SERVER_SRC+=$(shell ls $(COMMFUNCTION_PATH)|egrep '*.cpp')

CLIENT_SRC=$(shell ls $(CLIENT_PATH) | egrep '*.cpp' )
CLIENT_SRC+=$(shell ls $(COMMFUNCTION_PATH)| egrep '*.cpp')

SERVER_OBJ=$(SERVER_SRC:.cpp=.o)
CLIENT_OBJ=$(CLIENT_SRC:.cpp=.o)

.PHONY:all
all:$(SERVER) $(CLIENT)
$(SERVER):$(SERVER_OBJ)
	@$(CC) -o $@ $^ $(LDFLAGS) 
$(CLIENT):$(CLIENT_OBJ)
	@$(CC) -o $@ $^ $(LDFLAGS)
%.o:$(SERVER_PATH)/%.cpp
	@echo "compling [ $< ] to [ $@ ]...done"
	@$(CC) -c $< $(FLAGS)
%.o:$(CLIENT_PATH)/%.cpp
	@echo "compling [ $< ] to [ $@ ]...done "
	@$(CC) -c $< $(FLAGS)
%.o:$(DATA_POOL_PATH)/%.cpp
	@echo "compling [ $< ] to [ $@ ]...done "
	@$(CC) -c $< $(FLAGS)
%.o:$(COMMMFUNTION_PATH)/%.cpp
	@echo "compling [ $< ] to [ $@ ]...done "
	@$(CC) -c $< $(FLAGS)
.PHONY:clean
clean:
	rm *.o $(SERVER) $(CLIENT) output
.PHONY:output
output:all
	mkdir -p output/server/log
	mkdir -p output/server/bin
	mkdir -p output/server/conf

	cp -rf serverd output/server/bin
	cp -rf conf/server.conf  output/server/conf
	cp -rf plugin/ctl_server.sh output/server
	mkdir -p output/client

.PHONY:debug
debug:
	@echo $(SERVER_SRC)
	@echo $(SERVER_OBJ)
	@echo $(CLIENT_SRC)
	@echo $(CLIENT_OBJ)
	@echo $(DATA_POOL_SRC)
	@echo $(DATA_POOL_OBJ)
