CC      := gcc
STD     := -std=c23
WARN    := -Wall -Wextra
LDFLAGS :=
LDLIBS  :=
PLATFORM ?= host
IS_MINGW := $(if $(filter mingw,$(PLATFORM)),1,$(if $(filter Windows_NT,$(OS)),1,))

ifeq ($(OS),Windows_NT)
ifneq ($(MSYSTEM),UCRT64)
$(error Utilize o Ambiente UCRT64 para compilar no MSYS2)
endif
endif

SRC_DIR := src

# release (padrao): otimizado | debug (usado por `make run`): -g -O0
MODE ?= release
ifeq ($(MODE),debug)
  OPT    := -g -O0
  SUFFIX := _debug
else
  OPT    := -O2
  SUFFIX :=
endif

# Plataforma: os valores padrao sao Linux; apenas Windows muda nome e extensao
NOME  := jogo_linux
EXE   :=
ifeq ($(IS_MINGW),1)
NOME  := jogo_win64
EXE   := .exe
endif

ifeq ($(PLATFORM),mingw)
CC := x86_64-w64-mingw32ucrt-gcc
endif

# Objetos separados por modo, para nao misturar flags de release e debug

ifeq ($(IS_MINGW),1)
BUILD := build/mingw/$(MODE)
else
BUILD := build/linux/$(MODE)
endif
TARGET := saida/$(NOME)$(SUFFIX)$(EXE)

# Wildcard recursivo: $(call rwildcard,<dir>,<padrao>)
rwildcard = $(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))

SRCS     := $(call rwildcard,$(SRC_DIR),*.c)
OBJS     := $(SRCS:$(SRC_DIR)/%.c=$(BUILD)/%.o)
INCS     := $(addprefix -I,$(SRC_DIR) $(sort $(dir $(call rwildcard,$(SRC_DIR),*.h))))
CPPFLAGS := $(INCS) -MMD -MP
CFLAGS   := $(STD) $(WARN) $(OPT)

ifeq ($(IS_MINGW),1)
ifeq ($(PLATFORM),mingw)
CPPFLAGS += -I/usr/x86_64-w64-mingw32ucrt/include
LDFLAGS += -L/usr/x86_64-w64-mingw32ucrt/lib
endif
LDLIBS += -lraylib -lopengl32 -lgdi32 -lwinmm
else
LDLIBS += -lraylib -lm -lpthread -ldl
endif

.PHONY: all run clean

all: $(TARGET)

# Compila a versao de debug e executa
run:
	@$(MAKE) --no-print-directory MODE=debug
	./saida/$(NOME)_debug$(EXE)

$(TARGET): $(OBJS)
	@mkdir -p $(@D)
	$(CC) $(OBJS) -o $@ $(LDFLAGS) $(LDLIBS)

$(BUILD)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

clean:
	rm -rf build
	rm -rf saida

-include $(OBJS:.o=.d)