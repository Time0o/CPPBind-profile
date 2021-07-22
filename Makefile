LLVM_ROOT    := ~/prog/clang+llvm-12.0.1-rc3-x86_64-linux-gnu-ubuntu-21.04/bin
LLVM_CLANG   := $(LLVM_ROOT)/clang
LLVM_CLANGXX := $(LLVM_ROOT)/clang++
LLVM_AR      := $(LLVM_ROOT)/llvm-ar

all: bin/gcc/profile_cc \
     bin/clang/profile_cc \
     bin/gcc/profile_c \
     bin/clang/profile_c \
     bin/gcc/profile_c_handwritten \
     bin/clang/profile_c_handwritten \
     bin/gcc/profile_rust \
     bin/clang/profile_rust \
     bin/gcc/profile_rust_handwritten \
     bin/clang/profile_rust_handwritten \
     bin/gcc/profile_lua \
     bin/clang/profile_lua \
     bin/gcc/profile_lua_handwritten \
     bin/clang/profile_lua_handwritten

GCCFLAGS = -flto -fno-rtti -fno-ipa-sra -fno-stack-protector -O3
CLANGFLAGS = -flto=thin -fno-stack-protector -O3

bin/gcc/profile_cc: api.h profile_cc.cc
	g++ $(GCCFLAGS) profile_cc.cc -o bin/gcc/profile_cc

bin/clang/profile_cc: api.h profile_cc.cc
	clang++ $(CLANGFLAGS) profile_cc.cc -o bin/clang/profile_cc

bin/gcc/profile_c: api.h profile_c.c bind/api_c.h bind/api_c.cc
	gcc $(GCCFLAGS) -c profile_c.c -o out/profile_c.o -I bind -I ~/github/projects/cppbind/generate
	g++ $(GCCFLAGS) -c bind/api_c.cc -o out/api_c.o -I bind -I ~/github/projects/cppbind/generate
	g++ $(GCCFLAGS) out/profile_c.o out/api_c.o -o bin/gcc/profile_c

bin/clang/profile_c: api.h profile_c.c bind/api_c.h bind/api_c.cc
	clang $(CLANGFLAGS) -c profile_c.c -o out/profile_c.o -I bind -I ~/github/projects/cppbind/generate
	clang++ $(CLANGFLAGS) -c bind/api_c.cc -o out/api_c.o -I bind -I ~/github/projects/cppbind/generate
	clang++ $(CLANGFLAGS) out/profile_c.o out/api_c.o -o bin/clang/profile_c

bin/gcc/profile_c_handwritten: api.h profile_c.c api.h handwritten/api_c.cc
	gcc $(GCCFLAGS) -c profile_c.c -o out/profile_c.o -I . -I handwritten -DHANDWRITTEN
	g++ $(GCCFLAGS) -c handwritten/api_c.cc -o out/api_c_handwritten.o -I . -I handwritten
	g++ $(GCCFLAGS) out/profile_c.o out/api_c_handwritten.o -o bin/gcc/profile_c_handwritten

bin/clang/profile_c_handwritten: api.h profile_c.c api.h handwritten/api_c.h handwritten/api_c.cc
	clang $(CLANGFLAGS) -c profile_c.c -o out/profile_c.o -I . -I handwritten -DHANDWRITTEN
	clang++ $(CLANGFLAGS) -c handwritten/api_c.cc -o out/api_c_handwritten.o -I . -I handwritten
	clang++ $(CLANGFLAGS) out/profile_c.o out/api_c_handwritten.o -o bin/clang/profile_c_handwritten

bin/gcc/profile_rust: api.h profile_rust.rs bind/api_c.h bind/api_c.cc bind/api_rust.rs
	g++ $(GCCFLAGS) -c bind/api_c.cc -o out/api_c.o -I ~/github/projects/cppbind/generate/
	ar rcs out/libapi_c.a out/api_c.o
	rustc -C opt-level=3 profile_rust.rs -L out/ -o bin/gcc/profile_rust

bin/clang/profile_rust: api.h profile_rust.rs bind/api_c.h bind/api_c.cc bind/api_rust.rs
	$(LLVM_CLANGXX) $(CLANGFLAGS) -c bind/api_c.cc -o out/api_c.o -I ~/github/projects/cppbind/generate/
	$(LLVM_AR) rcs out/libapi_c.a out/api_c.o
	rustc -C linker-plugin-lto -C opt-level=3 -Clinker=clang -Clink-arg=-fuse-ld=lld profile_rust.rs -L out/ -o bin/clang/profile_rust

bin/gcc/profile_rust_handwritten: api.h profile_rust_handwritten.rs handwritten/api_c.h handwritten/api_c.cc handwritten/api_rust.rs
	g++ $(GCCFLAGS) -c handwritten/api_c.cc -o out/api_c.o -I . -I handwritten -I ~/github/projects/cppbind/generate/
	ar rcs out/libapi_c.a out/api_c.o
	rustc -C opt-level=3 profile_rust_handwritten.rs -L out/ -o bin/gcc/profile_rust_handwritten

bin/clang/profile_rust_handwritten: api.h profile_rust_handwritten.rs handwritten/api_c.h handwritten/api_c.cc handwritten/api_rust.rs
	$(LLVM_CLANGXX) $(CLANGFLAGS) -c handwritten/api_c.cc -o out/api_c.o -I . -I handwritten -I ~/github/projects/cppbind/generate/
	$(LLVM_AR) rcs out/libapi_c.a out/api_c.o
	rustc -C linker-plugin-lto -C opt-level=3 -Clinker=clang -Clink-arg=-fuse-ld=lld profile_rust_handwritten.rs -L out/ -o bin/clang/profile_rust_handwritten

bin/gcc/profile_lua: api.h profile_lua.cc profile_lua.lua bind/api_lua.cc
	g++ $(GCCFLAGS) -shared -fPIC bind/api_lua.cc -o out/api.so -I ~/github/projects/cppbind/generate/ -DJIT
	luajit -b profile_lua.lua out/profile_lua.o
	g++ -flto -fno-stack-protector -O3 -Wl,-E profile_lua.cc out/profile_lua.o -o bin/gcc/profile_lua -lluajit-5.1 -lm -ldl -DJIT

bin/clang/profile_lua: api.h profile_lua.cc profile_lua.lua bind/api_lua.cc
	clang++ $(CLANGFLAGS) -shared -fPIC bind/api_lua.cc -o out/api.so -I ~/github/projects/cppbind/generate/ -DJIT
	luajit -b profile_lua.lua out/profile_lua.o
	clang++ $(CLANGFLAGS) -W,-E profile_lua.cc out/profile_lua.o -o bin/clang/profile_lua -lluajit-5.1 -lm -ldl -DJIT

bin/gcc/profile_lua_handwritten: api.h profile_lua.cc profile_lua_handwritten.lua handwritten/api_lua.cc
	g++ $(GCCFLAGS) -shared -fPIC handwritten/api_lua.cc handwritten/api_c.cc -o out/api_handwritten.so -I . -I handwritten -I ~/github/projects/cppbind/generate/ -D JIT
	luajit -b profile_lua_handwritten.lua out/profile_lua_handwritten.o
	g++ $(GCCFLAGS) -Wl,-E profile_lua.cc out/profile_lua_handwritten.o -o bin/gcc/profile_lua_handwritten -lluajit-5.1 -lm -ldl -DJIT -DHANDWRITTEN

bin/clang/profile_lua_handwritten: api.h profile_lua.cc profile_lua_handwritten.lua handwritten/api_lua.cc
	clang++ $(CLANGFLAGS) -shared -fPIC handwritten/api_lua.cc handwritten/api_c.cc -o out/api_handwritten.so -llua -I . -I handwritten -I ~/github/projects/cppbind/generate/ -D JIT
	luajit -b profile_lua_handwritten.lua out/profile_lua_handwritten.o
	clang++ $(CLANGFLAGS) -Wl,-E profile_lua.cc out/profile_lua_handwritten.o -o bin/clang/profile_lua_handwritten -lluajit-5.1 -lm -ldl -DJIT -DHANDWRITTEN

.PHONY: clean

clean:
	rm -f bin/gcc/* bin/clang/* out/*
