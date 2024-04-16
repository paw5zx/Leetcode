# V1.4.1
# 1.添加了pkg-config的使用，可以自动获取三方库（以aravis为例）的头文件和库文件路径
# 2.添加对c++23的支持


#变量定义
CC := g++    #编译器
CXXFLAGS := -g -w #编译选项
PKGFLAGS := $(shell pkg-config --cflags aravis-0.8)

SRC_DIR := ./src
OBJ_DIR := ./obj
BIN_DIR := ./bin
ASM_DIR := ./asm
#include下可能有单独的.h文件
INCL_DIR := ./include
INCL_DIR += $(filter-out $(wildcard ./include/*.h),$(wildcard ./include/*))
#lib路径后续优化
LIB_DIR := ./lib
LIB_DIR += $(wildcard ./lib/*)

##所有cpp文件
cpp_src := $(shell find $(SRC_DIR) -name *.cpp)
##带有main函数的源文件
cpp_main := $(shell grep -l "int main" $(cpp_src))   
##类的实现文件 
cpp_class := $(filter-out $(cpp_main), $(cpp_src))    
##目标文件
cpp_obj_main := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(cpp_main))
cpp_obj_class := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(cpp_class))
##可执行文件
cpp_out_main := $(patsubst $(SRC_DIR)/%.cpp,$(BIN_DIR)/%.out,$(cpp_main))
##汇编文件
cpp_asm := $(patsubst $(SRC_DIR)/%.cpp,$(ASM_DIR)/%.s,$(cpp_src))

##头文件路径标志,为每个加上-I
i_flag :=$(foreach item,$(INCL_DIR),-I$(item))
##库文件路径标志，为每个加上-L
l_flag :=$(foreach item,$(LIB_DIR),-L$(item))

##链接的库
LIBS := $(shell pkg-config --libs aravis-0.8) -llog4cpp -lpthread

#操作
##汇编
$(cpp_asm) : $(ASM_DIR)/%.s : $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(call parse_cpp_standard,$<)
	@$(CC) $(CXXFLAGS) -S $^ -o $@

##编译
#类实现文件的编译规则
$(cpp_obj_class) : $(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(call parse_cpp_standard,$<)
	@$(CC) $(CXXFLAGS) $(i_flag) -c $^ -o $@
#主函数文件的编译规则
$(cpp_obj_main) : $(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(call parse_cpp_standard,$<)
	@$(CC) $(CXXFLAGS) $(i_flag) -c $^ -o $@

##链接
# 主函数文件应与自身及所有类实现函数链接 g++ filename1.o filename2.o ... -o outname
# $@是21
# $^是obj/21.o
$(cpp_out_main) : $(BIN_DIR)/%.out : $(OBJ_DIR)/%.o $(cpp_obj_class)
	@mkdir -p $(dir $@)
	@g++ $^ -o $@ $(l_flag) $(LIBS)


all : $(cpp_out_main)

asm : $(cpp_asm)

debug :
	@echo $(LIB_DIR)
clean :
	@rm -rf $(OBJ_DIR)/*.o
	@rm -rf $(BIN_DIR)/*.out

#伪目标
.PHONY : clean debug all asm


# 解析文件内容并设置C++标准
# 从文本中找出以"C++ Standard: "开头的字符串，并输出该字符串后的一个或多个非空白字符
define parse_cpp_standard
	$(eval FILE_CONTENT := $(shell cat $(1)))
	$(eval CPP_STANDARD := $(shell echo "$(FILE_CONTENT)" | grep -oP "(?<=C\+\+ Standard: )[^\s]+"))
	$(if $(CPP_STANDARD),$(info $(1) uses C++ standard: $(CPP_STANDARD)),$(info Failed to parse C++ standard for file $(1)))
	$(if $(filter $(CPP_STANDARD),C++11),$(eval CXXFLAGS += -std=c++11))
	$(if $(filter $(CPP_STANDARD),C++14),$(eval CXXFLAGS += -std=c++14))
	$(if $(filter $(CPP_STANDARD),C++17),$(eval CXXFLAGS += -std=c++17))
	$(if $(filter $(CPP_STANDARD),C++20),$(eval CXXFLAGS += -std=c++20))
	$(if $(filter $(CPP_STANDARD),C++23),$(eval CXXFLAGS += -std=c++23))
endef


