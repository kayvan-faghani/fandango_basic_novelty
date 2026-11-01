# We set MFLAGS="" MAKEFLAGS="" below s.t. "-B" is not passed on to other `make` invocations
MAKEFLAGS += --always-make
PIP = pip
SUDO ?= sudo

# ------------------------------------------------------------
# LLVM detection (must be 18, 19, or 20)
# ------------------------------------------------------------
LLVM_CONFIG := $(shell \
	if command -v llvm-config-20 >/dev/null 2>&1; then echo llvm-config-20; \
	elif command -v llvm-config-19 >/dev/null 2>&1; then echo llvm-config-19; \
	elif command -v llvm-config-18 >/dev/null 2>&1; then echo llvm-config-18; \
	elif command -v llvm-config >/dev/null 2>&1; then \
		v=$$(llvm-config --version | cut -d. -f1); \
		if [ $$v -ge 18 ] && [ $$v -le 20 ]; then echo llvm-config; fi; \
	fi)

ifeq ($(LLVM_CONFIG),)
$(error LLVM 18, 19, or 20 is required but was not found in PATH)
endif

$(info Using $(LLVM_CONFIG))

LLVM_CMAKE_DIR := $(shell $(LLVM_CONFIG) --cmakedir)

# ------------------------------------------------------------
# Build targets
# ------------------------------------------------------------

all: llvm

wllvm:
	rm -rf wllvm
	git clone https://github.com/travitch/whole-program-llvm.git wllvm
	rm -fr wllvm/test
	$(PIP) install -e wllvm

llvm: wllvm
	(mkdir -p llvm/build && cd llvm/build && \
	 cmake -DCMAKE_PREFIX_PATH=$(LLVM_CMAKE_DIR) .. && \
	 make -j32)

install-local: llvm
	@echo "fcc/fcc++/fan are installed in llvm/build/compiler..."

install: install-local
	@echo "Installing fcc/fcc++/fan to /usr/local/bin..."
	@$(SUDO) cp llvm/build/compiler/fcc /usr/local/bin/
	@$(SUDO) cp llvm/build/compiler/fcc++ /usr/local/bin/
	@$(SUDO) cp llvm/build/compiler/fan /usr/local/bin/

clean:
	rm -rf llvm/build
