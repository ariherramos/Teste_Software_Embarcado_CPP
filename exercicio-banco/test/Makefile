vpath %.c ../src

INCLUDE_DIRS = -I../src
INCLUDE_DIRS += -I$(CMOCKA_DIR)/include

CFLAGS	= $(INCLUDE_DIRS)

MOCKS = deposit
LDFLAGS	= -L$(CMOCKA_DIR)/build/src -Wl,-rpath=$(CMOCKA_DIR)/build/src 
LDFLAGS += $(foreach MOCK,$(MOCKS),-Wl,--wrap=$(MOCK))
LDFLAGS += -lcmocka

TARGET = test_banco

SRC = banco.c deposit.c
TEST_SRC = mock_deposit.c test_banco.c

SRC_OBJ = $(patsubst %.c,obj/%.o,$(SRC)) 
TEST_OBJ = $(patsubst %.c,obj/%.o,$(TEST_SRC)) 
OBJ_DIR = obj

CMOCKA_TAR = cmocka-1.1.5.tar.xz
CMOCKA_DIR = cmocka-1.1.5

all: $(CMOCKA_DIR) $(TARGET)
	./$(TARGET)

$(SRC_OBJ): | $(OBJ_DIR)

$(OBJ_DIR):
	@mkdir -p $@

$(OBJ_DIR)/%.o : %.c
	@echo $< 
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET):  $(SRC_OBJ) $(TEST_OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

$(CMOCKA_DIR):
	mkdir -p $@
	tar -xf $(CMOCKA_TAR) -C $@ --strip-components 1
	mkdir -p $@/build
	@(cd $@/build && cmake ../ && make -s)

clean:
	rm -rf $(TARGET) $(OBJ_DIR) $(CMOCKA_DIR)
