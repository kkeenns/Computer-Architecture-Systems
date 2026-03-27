SOURCE       := main.c pa1.c
SRC_DIR      := src
BUILD_DIR    := build
EXECUTABLE   := pa1
PA1_SO       := lib$(EXECUTABLE).so

CC           := gcc
CFLAGS       := -Og -g -Isrc -std=c11 -Wall -Werror

.PHONY: run clean grade
.SUFFIXES: # no default implicit rules in the way

run: | $(BUILD_DIR) $(EXECUTABLE)
	./$(EXECUTABLE)

clean:
	rm -f $(EXECUTABLE)
	rm -rf $(BUILD_DIR)
	rm -f $(PA1_SO)

grade: clean
	$(warning [WARN] This Makefile target is only for the autograder! It will not do anything useful for a student.)
	$(CC) $(CFLAGS) $(SRC_DIR)/pa1.c -fdiagnostics-color=always -fPIE -shared -o $(PA1_SO)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

-include $(SOURCE:%.c=$(BUILD_DIR)/%.d)

# C compilation (C source -> binary object file)
$(SOURCE:%.c=$(BUILD_DIR)/%.o): $(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -c $(CFLAGS) -MMD -MF $(@:%.o=%.d) $< -o $@

# Linking the object files ({all objects} -> executable binary)
$(EXECUTABLE): $(SOURCE:%.c=$(BUILD_DIR)/%.o)
	$(CC) $(CFLAGS) $^ -o $@